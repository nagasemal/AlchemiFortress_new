#include "pch.h"
#include "MachineSelectManager.h"
#include "Scenes/DataManager.h"

#include "Scenes/Commons/UIKeyControl.h"
#include "Scenes/PlayScene/UI/Number.h"

#include "Scenes/PlayScene/UI/DisplayMagicCircle.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/GameData/JsonLoder.h"
#include "NecromaLib/Singleton/InputSupport.h"
#include "NecromaLib/Singleton/DeltaTime.h"

#include "NecromaLib/GameData/SpriteCutter.h"

#include "NecromaLib/GameData/Particle_2D.h"

#define DIRECTION	120.0f

#define MACHINE_NAME_POS_SHIFT SimpleMath::Vector2(20, 60)

#define MACHINE_UI_POS_SHIFT SimpleMath::Vector2(100, 60)

//　====================[　結晶,魔力アイコンに使うテクスチャの大きさ　]
#define ICON_TEX_RAGE 64

//　====================[　マシンUIのサイズ　]
#define MACHINE_UI_SIZE 0.3f

//　====================[　マシンの説明テキストのサイズ　]
#define MACHINE_TEXT_SIZE 0.5f

//　====================[　マシンの説明テキストのアニメーション値　]
#define MACHINE_TEXT_ANIMVAL 30.0f

MachineSelectManager::MachineSelectManager() :
	m_selectMachineType(MACHINE_TYPE::NONE),
	m_selectBoxAll(false),
	m_manufacturingFlag(false),
	m_selectNoneFlag(false),
	m_forwardOrderFlag(false),
	m_rotateTime(),
	m_selectNumber(1),
	m_cursorMachineNumber(),
	m_prevSelectNumber(),
	m_uiTransparentTime(),
	m_alchemiActiveFlag()
{
}

MachineSelectManager::~MachineSelectManager()
{
}

void MachineSelectManager::TextuerLoader()
{
}

void MachineSelectManager::Initialize()
{
	ShareJsonData& pSJD = ShareJsonData::GetInstance();

	//　====================[　マシンUIの情報を取得　]
	UI_Data uiData = pSJD.GetUIData("AlchemiMachineIcon");

	SimpleMath::Vector2 spacePos = SimpleMath::Vector2(uiData.option["SPACE"], 0.0f);

	// Noneを省くために1スタート
	for (int i = 0; i < MACHINE_TYPE::NUM; i++)
	{

		m_machineSelect[i] = std::make_unique<MachineSelect>();

		m_machineSelect[i]->SetMachineType((MACHINE_TYPE)i);
		
		m_machineSelect[i]->SetPosition(uiData.pos - (spacePos * (MACHINE_TYPE::NUM / 2.0f)) + (spacePos * i));

		m_machineSelect[i]->Initialize();

		m_machineSelect[i]->GetMachineBox()->SetSavePos(m_machineSelect[i]->GetPos());

		m_machineSelect[i]->GetMachineBox()->SetKey(uiData.key);

	}

	//　====================[　メンバ変数のリセット　]
	m_selectBoxAll		= false;
	m_manufacturingFlag = false;

	m_alchemiActiveFlag = true;

	//　====================[　錬金ボタン選択時浮き出る魔法陣の取得　]
	m_displayMagicCircle = std::make_unique<DisplayMagicCircle>();

	//　====================[　マシンの名前の情報を取得　]
	m_machineName		= std::make_unique<SelectionBox>(SimpleMath::Vector2(), SimpleMath::Vector2(1.0f, 1.0f));
	m_machineName		->Initialize();

	//　====================[　マウスが周辺に位置するかを取得　]
	m_collider			= std::make_unique<SelectionBox>(uiData.pos,SimpleMath::Vector2(uiData.option["COLLIDER"], uiData.option["COLLIDER"]));
	m_collider			->Initialize();
	m_collider			->SetRect(RECT{ 0,0,1,1});
	m_collider			->SetWorldInfluenceFlag(false);

	//　====================[　マシンUI移動(左)の情報を取得　]
	uiData = pSJD.GetUIData("AlchemiLeft");
	m_selectionLeft		= std::make_unique<SelectionBox>(uiData.pos, uiData.rage);
	m_selectionLeft		->Initialize();
	m_selectionLeft		->SetLayer((int)uiData.option["LAYER"]);
	m_selectionLeft		->SetKey(uiData.key);

	//　====================[　マシンUI移動(右)の情報を取得　]
	uiData = pSJD.GetUIData("AlchemiRight");
	m_selectionRight	= std::make_unique<SelectionBox>(uiData.pos, uiData.rage);
	m_selectionRight	->Initialize();
	m_selectionRight	->SetLayer((int)uiData.option["LAYER"]);
	m_selectionRight	->SetKey(uiData.key);

	//　====================[　錬金ボタン内の所持数描画を取得　]
	uiData = pSJD.GetUIData("AlchemiNum");
	m_machineNumRender	= std::make_unique<Number>(uiData.pos, uiData.rage);

	//　====================[　錬金ボタン内の必要魔力量描画を取得　]
	uiData = pSJD.GetUIData("AlchemiMP");
	m_mpNumRender		= std::make_unique<Number>(uiData.pos, uiData.rage);

	//　====================[　錬金ボタン内の必要クリスタル描画を取得　]
	uiData = pSJD.GetUIData("AlchemiCrystal");
	m_crystalRender		= std::make_unique<Number>(uiData.pos, uiData.rage);

	//　====================[　パーティクルの生成　]
	m_alchemiCircle = std::make_unique<Particle_2D>();
	m_particle		= std::make_unique<Particle_2D>();

}

void MachineSelectManager::Update(FieldObjectManager* fieldObjectManager)
{

	auto datas = DataManager::GetInstance();
	auto pSJD = &ShareJsonData::GetInstance();
	auto pINP = &InputSupport::GetInstance();

	float deltaTime = DeltaTime::GetInstance().GetNomalDeltaTime();

	// マシンUIが選択されているならば対象のIDを入力
	// 選択されていない状態ならば規定位置に存在するマシンUIのIDを入力
	MACHINE_TYPE machineType = (MACHINE_TYPE)m_selectNumber;

	TransparentUI(1.0f);

	//　====================[　メンバ変数のリセット　]
	m_selectBoxAll		= false;
	m_manufacturingFlag = false;

	////　====================[　UIの更新　]
	//m_selectionLeft		->HitMouse(true);
	//m_selectionRight	->HitMouse(true);

	//　====================[　パーティクルの更新　]
	m_alchemiCircle->UpdateParticle();
	m_particle		->UpdateParticle();

	//　====================[　各マシンUIの更新　]
	for (int i = 1; i < MACHINE_TYPE::NUM; i++)
	{
		m_machineSelect[i]->Update();

		// 要素から製造ボタンが押された判定を受け取る リソースが足りない場合は弾く
		m_machineSelect[i]->GetMachineBox()->SetActiveFlag(
			(datas->GetNowMP() - pSJD->GetMachineData(m_machineSelect[i]->GetMachineType()).alchemi_mp >= 0 &&
				datas->GetNowCrystal() - pSJD->GetMachineData(m_machineSelect[i]->GetMachineType()).alchemi_crystal >= 0) && m_alchemiActiveFlag);

		if (m_machineSelect[i]->GetMachineBox()->HitMouse())
		{
			m_selectNumber = (int)m_machineSelect[i]->GetMachineType();
		}

	}

	//　====================[　マシンUIに触れた際の処理　]
	if (m_machineSelect[m_selectNumber]->GetHitMouseFlag()) 	m_textAnim += deltaTime;
	else 	m_textAnim -= deltaTime;

	////　====================[　錬金ボタンに触れた際の処理　]
	//if (m_selectionAlchemi->HitMouse(true)) 					m_magicCircleAnim += deltaTime;
	//else 	m_magicCircleAnim -= deltaTime;

	//　====================[　フィールドのクリスタル選択時　]
	//　　|=>　エクスカベーターUIの色を変える
	m_machineSelect[MACHINE_TYPE::MINING]->SetChangeColorFlag(fieldObjectManager->GetCrystalToMouse());
	//　　|=>　更新
	m_displayMagicCircle->Update();
	m_displayMagicCircle->TransparentUpdate(m_selectBoxAll);

	//　====================[　マウス周辺に選択中のマシンの名前描画　]
	m_machineName->SetSavePos(pINP->GetMousePosScreen() - MACHINE_NAME_POS_SHIFT);

	RotationMachineList();

	////　====================[　次のマシンUIを表示　]
	//if (m_selectionRight	->ClickMouse() && m_rotateTime >= 1.0f)
	//{
	//	m_rotateTime = 0.0f;
	//
	//	m_prevSelectNumber = m_selectNumber;
	//	m_selectNumber++;
	//
	//	m_forwardOrderFlag = true;
	//
	//	if (m_selectNumber >= MACHINE_TYPE::NUM) m_selectNumber = 1;
	//}
	//
	////　====================[　前のマシンUIを表示　]
	//if (m_selectionLeft		->ClickMouse() && m_rotateTime >= 1.0f)
	//{
	//	m_rotateTime = 0.0f;
	//
	//	m_prevSelectNumber = m_selectNumber;
	//	m_selectNumber--;
	//
	//	m_forwardOrderFlag = false;
	//
	//	if (m_selectNumber <= 0) m_selectNumber = 5;
	//}

	//m_mpNumRender	->	SetNumber(pSJD->GetMachineData(machineType).alchemi_mp);
	//m_crystalRender	->	SetNumber(pSJD->GetMachineData(machineType).alchemi_crystal);

	// 錬金ボタンが押された
	if (m_machineSelect[machineType]->GetMachineBox()->ClickMouse())
	{

		// 錬金された瞬間を取得
		m_manufacturingFlag = true;

		// 錬金された瞬間のマシンタイプを取得する
		m_selectMachineType = m_machineSelect[machineType]->GetMachineType();

		// マシンタイプを取得しリソース群を減らす
		ReduceResource(machineType);

		m_alchemiCircle	->OnShot("AlchemiCircle", m_machineSelect[machineType]->GetMachineBox()->GetPos(),true);
		m_particle		->OnShot("AlchemiParticle", m_machineSelect[machineType]->GetMachineBox()->GetPos(), true);

	}
}

void MachineSelectManager::Render()
{
	auto pSB = ShareData::GetInstance().GetSpriteBatch();
	ShareData& pSD = ShareData::GetInstance();


	pSB->Begin(DirectX::SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());
	pSB->End();

}

void MachineSelectManager::RenderUI(int machineNum[])
{

	SpriteLoder& pSL	= SpriteLoder::GetInstance();
	auto pSB			= ShareData::GetInstance().GetSpriteBatch();
	ShareData& pSD		= ShareData::GetInstance();
	auto pINP			= &InputSupport::GetInstance();
	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	UI_Data uiData		= UI_Data();

	//　====================[　画像切り取り変数の定義　]
	RECT rect = RECT();

	////　====================[　UI移動ボタンの描画　]
	//SpriteLoder::TextureData alchemiArrowTexture = pSL.GetAlchemiArrowTexture();
	//m_selectionLeft->DrawUI(alchemiArrowTexture.tex.Get(), 0.0f);
	//m_selectionLeft->SetRect(RECT{ 0,0,alchemiArrowTexture.width,alchemiArrowTexture.height });
	//
	//m_selectionRight->DrawUI(alchemiArrowTexture.tex.Get(), XMConvertToRadians(180.0f));
	//m_selectionRight->SetRect(RECT{ 0,0,alchemiArrowTexture.width,alchemiArrowTexture.height });

	//　====================[　マシンアイコンUIの描画　]

	for (int i = 1; i < MACHINE_TYPE::NUM; i++)
	{

		m_machineSelect[i]->DisplayObject();

	}

	pSB->Begin(DirectX::SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	//　====================[　マウス周辺に描画　]
	//　　|=>　現在マウスがUIに触れていない
	if (!pINP->GetHitUI())
	{
		//　　|=>　色を設定
		SimpleMath::Color name_color = SimpleMath::Color(0.9f, 0.9f, 0.9f, 0.95f);

		//　　|=>　所持数が0ならば色を変更する
		if (machineNum[m_selectNumber] <= 0) name_color = Colors::Red;

		//　====================[　マシンの名前を描画　]
		SpriteLoder::TextureData texData = pSL.GetMachineNameTexture();
		rect = SpriteCutter(texData.width / MACHINE_TYPE::NUM, texData.height, m_selectNumber, 0);
		pSB->Draw(texData.tex.Get(), pINP->GetMousePosScreen() - MACHINE_NAME_POS_SHIFT,
			&rect, name_color, 0.0f, SimpleMath::Vector2((texData.width / MACHINE_TYPE::NUM) / 2.0f, texData.height / 2.0f));

		//　====================[　マシンUIを描画　]
		texData = pSL.GetMachineIconTexture();
		rect = SpriteCutter(texData.width / (MACHINE_TYPE::NUM - 1), texData.height, m_selectNumber - 1, 0);

		pSB->Draw(texData.tex.Get(), pINP->GetMousePosScreen() - MACHINE_UI_POS_SHIFT,
			&rect, name_color, 0.0f,
			DirectX::XMFLOAT2(static_cast<float>((texData.width / (MACHINE_TYPE::NUM - 1)) / 2),
				static_cast<float>(texData.height / 2)), MACHINE_UI_SIZE);

		// 透明度付加
		SimpleMath::Color alphaColor = SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);

		////　====================[　魔力アイコンを描画　]
		//uiData = pSJD.GetUIData("AlchemiMP");
		//rect = SpriteCutter(ICON_TEX_RAGE, ICON_TEX_RAGE, 0, 0);
		//pSB->Draw(pSL.GetElementTexture().Get(), uiData.pos - SimpleMath::Vector2(uiData.option["ICON_SHIFT"], 0.0f),
		//	&rect, alphaColor,
		//	0.0f, SimpleMath::Vector2(ICON_TEX_RAGE / 2.0f, ICON_TEX_RAGE / 2.0f), uiData.option["ICON_RAGE"]);
		//
		////　====================[　結晶アイコンを描画　]
		//uiData = pSJD.GetUIData("AlchemiCrystal");
		//rect = SpriteCutter(ICON_TEX_RAGE, ICON_TEX_RAGE, 1, 0);
		//pSB->Draw(pSL.GetElementTexture().Get(), uiData.pos - SimpleMath::Vector2(uiData.option["ICON_SHIFT"], 0.0f),
		//	&rect, alphaColor, 0.0f, SimpleMath::Vector2(ICON_TEX_RAGE / 2.0f, ICON_TEX_RAGE / 2.0f), uiData.option["ICON_RAGE"]);
	}

	pSB->End();

	//　====================[　所持数の描画(錬金ボタン内部)　]
	m_machineNumRender->SetNumber(machineNum[m_selectNumber]);
	m_machineNumRender->SetPosition(m_machineSelect[m_selectNumber]->GetPos());
	m_machineNumRender->Render();

	//　====================[　必要リソース量の描画　]
	// m_mpNumRender->	Render();
	// m_crystalRender->	Render();

	//　====================[　パーティクルの描画　]
	SpriteLoder::TextureData particleTex = pSL.GetMachineMagicCircleTexture(m_selectNumber);
	m_alchemiCircle->Render(particleTex.tex, RECT{ 0,0, particleTex.width, particleTex.height});

	particleTex = pSL.GetNormalParticle();
	m_particle		->Render(particleTex.tex, RECT{ 0,0, particleTex.width, particleTex.height });

}

// 呼び出し元で要素分回している
void MachineSelectManager::ModelRender(int index)
{
	m_machineSelect[index]->DisplayObject();
}

void MachineSelectManager::MagicCircleRender()
{
	m_displayMagicCircle->SpritebatchRender();
}

void MachineSelectManager::Finalize()
{

	for (int i = 1; i < MACHINE_TYPE::NUM; i++)
	{
		m_machineSelect[i]->Finalize();
	}

}

void MachineSelectManager::ReduceResource(MACHINE_TYPE type)
{
	auto datas = DataManager::GetInstance();
	auto pSJD = &ShareJsonData::GetInstance();

	datas->SetNowMP(datas->GetNowMP() - pSJD->GetMachineData(type).alchemi_mp);

	datas->SetNowCrystal(datas->GetNowCrystal() - pSJD->GetMachineData(type).alchemi_crystal);

}

void MachineSelectManager::RotationMachineList()
{
	// 規定値ならば処理を行わない
	if (m_rotateTime >= 1.0f)
	{
		m_rotateTime = 1.0f;
		return;
	}

	// 回転を行う
	m_rotateTime += DeltaTime::GetInstance().GetNomalDeltaTime() * 6.0f;
}

void MachineSelectManager::LRButtonLock(bool flag)
{
	//m_selectionLeft->SetActiveFlag(flag);
	//m_selectionRight->SetActiveFlag(flag);
}

void MachineSelectManager::AlchemiButtonLock(bool flag)
{
	m_alchemiActiveFlag = flag;
}

void MachineSelectManager::TransparentUI(float transparentVal)
{
	auto datas = DataManager::GetInstance();
	auto pSJD = &ShareJsonData::GetInstance();

	// マシンUIが選択されているならば対象のIDを入力
	// 選択されていない状態ならば規定位置に存在するマシンUIのIDを入力
	MACHINE_TYPE machineType = (MACHINE_TYPE)m_selectNumber;

	//　====================[　所持数が0以下である場合、数字を赤くする　] 
	//　　|=>　マシン
	if (m_machineNumRender->GetNumber() <= 0)
	{
		m_machineNumRender->SetColor(SimpleMath::Color(Colors::Red));
	}
	else
	{
		m_machineNumRender->SetColor(SimpleMath::Color(Colors::Black));
	}
	//　　|=>　魔力
	if (pSJD->GetMachineData(machineType).alchemi_mp > datas->GetNowMP())
	{
		m_mpNumRender->SetColor(SimpleMath::Color(Colors::Red));
	}
	else
	{
		m_mpNumRender->SetColor(SimpleMath::Color(Colors::Black));
	}
	//　　|=>　結晶
	if (pSJD->GetMachineData(machineType).alchemi_crystal > datas->GetNowCrystal())
	{
		m_crystalRender->SetColor(SimpleMath::Color(Colors::Red));
	}
	else
	{
		m_crystalRender->SetColor(SimpleMath::Color(Colors::Black));
	}

	//　====================[　透明化を行う　]
	m_selectionLeft		->SetColor(SimpleMath::Color(m_selectionLeft	->GetColorRGB(), transparentVal));
	m_selectionRight	->SetColor(SimpleMath::Color(m_selectionRight	->GetColorRGB(), transparentVal));

	m_machineNumRender	->SetColor(SimpleMath::Color(m_machineNumRender	->GetColorRGB(), transparentVal));
	m_mpNumRender		->SetColor(SimpleMath::Color(m_mpNumRender		->GetColorRGB(), transparentVal));
	m_crystalRender		->SetColor(SimpleMath::Color(m_crystalRender	->GetColorRGB(), transparentVal));

	// Noneを省くために1スタート
	for (int i = 1; i < MACHINE_TYPE::NUM; i++)
	{
		m_machineSelect[i]->GetMachineBox()->SetColor(SimpleMath::Color(m_machineSelect[i]->GetMachineBox()->GetColorRGB(), transparentVal));
	}
}
