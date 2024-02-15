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

//�@====================[�@����,���̓A�C�R���Ɏg���e�N�X�`���̑傫���@]
#define ICON_TEX_RAGE 64

//�@====================[�@�}�V��UI�̃T�C�Y�@]
#define MACHINE_UI_SIZE 0.3f

//�@====================[�@�}�V���̐����e�L�X�g�̃T�C�Y�@]
#define MACHINE_TEXT_SIZE 0.5f

//�@====================[�@�}�V���̐����e�L�X�g�̃A�j���[�V�����l�@]
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

	//�@====================[�@�}�V��UI�̏����擾�@]
	UI_Data uiData = pSJD.GetUIData("AlchemiMachineIcon");

	SimpleMath::Vector2 spacePos = SimpleMath::Vector2(uiData.option["SPACE"], 0.0f);

	// None���Ȃ����߂�1�X�^�[�g
	for (int i = 0; i < MACHINE_TYPE::NUM; i++)
	{

		m_machineSelect[i] = std::make_unique<MachineSelect>();

		m_machineSelect[i]->SetMachineType((MACHINE_TYPE)i);
		
		m_machineSelect[i]->SetPosition(uiData.pos - (spacePos * (MACHINE_TYPE::NUM / 2.0f)) + (spacePos * i));

		m_machineSelect[i]->Initialize();

		m_machineSelect[i]->GetMachineBox()->SetSavePos(m_machineSelect[i]->GetPos());

		m_machineSelect[i]->GetMachineBox()->SetKey(uiData.key);

	}

	//�@====================[�@�����o�ϐ��̃��Z�b�g�@]
	m_selectBoxAll		= false;
	m_manufacturingFlag = false;

	m_alchemiActiveFlag = true;

	//�@====================[�@�B���{�^���I���������o�閂�@�w�̎擾�@]
	m_displayMagicCircle = std::make_unique<DisplayMagicCircle>();

	//�@====================[�@�}�V���̖��O�̏����擾�@]
	m_machineName		= std::make_unique<SelectionBox>(SimpleMath::Vector2(), SimpleMath::Vector2(1.0f, 1.0f));
	m_machineName		->Initialize();

	//�@====================[�@�}�E�X�����ӂɈʒu���邩���擾�@]
	m_collider			= std::make_unique<SelectionBox>(uiData.pos,SimpleMath::Vector2(uiData.option["COLLIDER"], uiData.option["COLLIDER"]));
	m_collider			->Initialize();
	m_collider			->SetRect(RECT{ 0,0,1,1});
	m_collider			->SetWorldInfluenceFlag(false);

	//�@====================[�@�}�V��UI�ړ�(��)�̏����擾�@]
	uiData = pSJD.GetUIData("AlchemiLeft");
	m_selectionLeft		= std::make_unique<SelectionBox>(uiData.pos, uiData.rage);
	m_selectionLeft		->Initialize();
	m_selectionLeft		->SetLayer((int)uiData.option["LAYER"]);
	m_selectionLeft		->SetKey(uiData.key);

	//�@====================[�@�}�V��UI�ړ�(�E)�̏����擾�@]
	uiData = pSJD.GetUIData("AlchemiRight");
	m_selectionRight	= std::make_unique<SelectionBox>(uiData.pos, uiData.rage);
	m_selectionRight	->Initialize();
	m_selectionRight	->SetLayer((int)uiData.option["LAYER"]);
	m_selectionRight	->SetKey(uiData.key);

	//�@====================[�@�B���{�^�����̏������`����擾�@]
	uiData = pSJD.GetUIData("AlchemiNum");
	m_machineNumRender	= std::make_unique<Number>(uiData.pos, uiData.rage);

	//�@====================[�@�B���{�^�����̕K�v���͗ʕ`����擾�@]
	uiData = pSJD.GetUIData("AlchemiMP");
	m_mpNumRender		= std::make_unique<Number>(uiData.pos, uiData.rage);

	//�@====================[�@�B���{�^�����̕K�v�N���X�^���`����擾�@]
	uiData = pSJD.GetUIData("AlchemiCrystal");
	m_crystalRender		= std::make_unique<Number>(uiData.pos, uiData.rage);

	//�@====================[�@�p�[�e�B�N���̐����@]
	m_alchemiCircle = std::make_unique<Particle_2D>();
	m_particle		= std::make_unique<Particle_2D>();

}

void MachineSelectManager::Update(FieldObjectManager* fieldObjectManager)
{

	auto datas = DataManager::GetInstance();
	auto pSJD = &ShareJsonData::GetInstance();
	auto pINP = &InputSupport::GetInstance();

	float deltaTime = DeltaTime::GetInstance().GetNomalDeltaTime();

	// �}�V��UI���I������Ă���Ȃ�ΑΏۂ�ID�����
	// �I������Ă��Ȃ���ԂȂ�΋K��ʒu�ɑ��݂���}�V��UI��ID�����
	MACHINE_TYPE machineType = (MACHINE_TYPE)m_selectNumber;

	TransparentUI(1.0f);

	//�@====================[�@�����o�ϐ��̃��Z�b�g�@]
	m_selectBoxAll		= false;
	m_manufacturingFlag = false;

	////�@====================[�@UI�̍X�V�@]
	//m_selectionLeft		->HitMouse(true);
	//m_selectionRight	->HitMouse(true);

	//�@====================[�@�p�[�e�B�N���̍X�V�@]
	m_alchemiCircle->UpdateParticle();
	m_particle		->UpdateParticle();

	//�@====================[�@�e�}�V��UI�̍X�V�@]
	for (int i = 1; i < MACHINE_TYPE::NUM; i++)
	{
		m_machineSelect[i]->Update();

		// �v�f���琻���{�^���������ꂽ������󂯎�� ���\�[�X������Ȃ��ꍇ�͒e��
		m_machineSelect[i]->GetMachineBox()->SetActiveFlag(
			(datas->GetNowMP() - pSJD->GetMachineData(m_machineSelect[i]->GetMachineType()).alchemi_mp >= 0 &&
				datas->GetNowCrystal() - pSJD->GetMachineData(m_machineSelect[i]->GetMachineType()).alchemi_crystal >= 0) && m_alchemiActiveFlag);

		if (m_machineSelect[i]->GetMachineBox()->HitMouse())
		{
			m_selectNumber = (int)m_machineSelect[i]->GetMachineType();
		}

	}

	//�@====================[�@�}�V��UI�ɐG�ꂽ�ۂ̏����@]
	if (m_machineSelect[m_selectNumber]->GetHitMouseFlag()) 	m_textAnim += deltaTime;
	else 	m_textAnim -= deltaTime;

	////�@====================[�@�B���{�^���ɐG�ꂽ�ۂ̏����@]
	//if (m_selectionAlchemi->HitMouse(true)) 					m_magicCircleAnim += deltaTime;
	//else 	m_magicCircleAnim -= deltaTime;

	//�@====================[�@�t�B�[���h�̃N���X�^���I�����@]
	//�@�@|=>�@�G�N�X�J�x�[�^�[UI�̐F��ς���
	m_machineSelect[MACHINE_TYPE::MINING]->SetChangeColorFlag(fieldObjectManager->GetCrystalToMouse());
	//�@�@|=>�@�X�V
	m_displayMagicCircle->Update();
	m_displayMagicCircle->TransparentUpdate(m_selectBoxAll);

	//�@====================[�@�}�E�X���ӂɑI�𒆂̃}�V���̖��O�`��@]
	m_machineName->SetSavePos(pINP->GetMousePosScreen() - MACHINE_NAME_POS_SHIFT);

	RotationMachineList();

	////�@====================[�@���̃}�V��UI��\���@]
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
	////�@====================[�@�O�̃}�V��UI��\���@]
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

	// �B���{�^���������ꂽ
	if (m_machineSelect[machineType]->GetMachineBox()->ClickMouse())
	{

		// �B�����ꂽ�u�Ԃ��擾
		m_manufacturingFlag = true;

		// �B�����ꂽ�u�Ԃ̃}�V���^�C�v���擾����
		m_selectMachineType = m_machineSelect[machineType]->GetMachineType();

		// �}�V���^�C�v���擾�����\�[�X�Q�����炷
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

	//�@====================[�@�摜�؂���ϐ��̒�`�@]
	RECT rect = RECT();

	////�@====================[�@UI�ړ��{�^���̕`��@]
	//SpriteLoder::TextureData alchemiArrowTexture = pSL.GetAlchemiArrowTexture();
	//m_selectionLeft->DrawUI(alchemiArrowTexture.tex.Get(), 0.0f);
	//m_selectionLeft->SetRect(RECT{ 0,0,alchemiArrowTexture.width,alchemiArrowTexture.height });
	//
	//m_selectionRight->DrawUI(alchemiArrowTexture.tex.Get(), XMConvertToRadians(180.0f));
	//m_selectionRight->SetRect(RECT{ 0,0,alchemiArrowTexture.width,alchemiArrowTexture.height });

	//�@====================[�@�}�V���A�C�R��UI�̕`��@]

	for (int i = 1; i < MACHINE_TYPE::NUM; i++)
	{

		m_machineSelect[i]->DisplayObject();

	}

	pSB->Begin(DirectX::SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	//�@====================[�@�}�E�X���ӂɕ`��@]
	//�@�@|=>�@���݃}�E�X��UI�ɐG��Ă��Ȃ�
	if (!pINP->GetHitUI())
	{
		//�@�@|=>�@�F��ݒ�
		SimpleMath::Color name_color = SimpleMath::Color(0.9f, 0.9f, 0.9f, 0.95f);

		//�@�@|=>�@��������0�Ȃ�ΐF��ύX����
		if (machineNum[m_selectNumber] <= 0) name_color = Colors::Red;

		//�@====================[�@�}�V���̖��O��`��@]
		SpriteLoder::TextureData texData = pSL.GetMachineNameTexture();
		rect = SpriteCutter(texData.width / MACHINE_TYPE::NUM, texData.height, m_selectNumber, 0);
		pSB->Draw(texData.tex.Get(), pINP->GetMousePosScreen() - MACHINE_NAME_POS_SHIFT,
			&rect, name_color, 0.0f, SimpleMath::Vector2((texData.width / MACHINE_TYPE::NUM) / 2.0f, texData.height / 2.0f));

		//�@====================[�@�}�V��UI��`��@]
		texData = pSL.GetMachineIconTexture();
		rect = SpriteCutter(texData.width / (MACHINE_TYPE::NUM - 1), texData.height, m_selectNumber - 1, 0);

		pSB->Draw(texData.tex.Get(), pINP->GetMousePosScreen() - MACHINE_UI_POS_SHIFT,
			&rect, name_color, 0.0f,
			DirectX::XMFLOAT2(static_cast<float>((texData.width / (MACHINE_TYPE::NUM - 1)) / 2),
				static_cast<float>(texData.height / 2)), MACHINE_UI_SIZE);

		// �����x�t��
		SimpleMath::Color alphaColor = SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);

		////�@====================[�@���̓A�C�R����`��@]
		//uiData = pSJD.GetUIData("AlchemiMP");
		//rect = SpriteCutter(ICON_TEX_RAGE, ICON_TEX_RAGE, 0, 0);
		//pSB->Draw(pSL.GetElementTexture().Get(), uiData.pos - SimpleMath::Vector2(uiData.option["ICON_SHIFT"], 0.0f),
		//	&rect, alphaColor,
		//	0.0f, SimpleMath::Vector2(ICON_TEX_RAGE / 2.0f, ICON_TEX_RAGE / 2.0f), uiData.option["ICON_RAGE"]);
		//
		////�@====================[�@�����A�C�R����`��@]
		//uiData = pSJD.GetUIData("AlchemiCrystal");
		//rect = SpriteCutter(ICON_TEX_RAGE, ICON_TEX_RAGE, 1, 0);
		//pSB->Draw(pSL.GetElementTexture().Get(), uiData.pos - SimpleMath::Vector2(uiData.option["ICON_SHIFT"], 0.0f),
		//	&rect, alphaColor, 0.0f, SimpleMath::Vector2(ICON_TEX_RAGE / 2.0f, ICON_TEX_RAGE / 2.0f), uiData.option["ICON_RAGE"]);
	}

	pSB->End();

	//�@====================[�@�������̕`��(�B���{�^������)�@]
	m_machineNumRender->SetNumber(machineNum[m_selectNumber]);
	m_machineNumRender->SetPosition(m_machineSelect[m_selectNumber]->GetPos());
	m_machineNumRender->Render();

	//�@====================[�@�K�v���\�[�X�ʂ̕`��@]
	// m_mpNumRender->	Render();
	// m_crystalRender->	Render();

	//�@====================[�@�p�[�e�B�N���̕`��@]
	SpriteLoder::TextureData particleTex = pSL.GetMachineMagicCircleTexture(m_selectNumber);
	m_alchemiCircle->Render(particleTex.tex, RECT{ 0,0, particleTex.width, particleTex.height});

	particleTex = pSL.GetNormalParticle();
	m_particle		->Render(particleTex.tex, RECT{ 0,0, particleTex.width, particleTex.height });

}

// �Ăяo�����ŗv�f���񂵂Ă���
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
	// �K��l�Ȃ�Ώ������s��Ȃ�
	if (m_rotateTime >= 1.0f)
	{
		m_rotateTime = 1.0f;
		return;
	}

	// ��]���s��
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

	// �}�V��UI���I������Ă���Ȃ�ΑΏۂ�ID�����
	// �I������Ă��Ȃ���ԂȂ�΋K��ʒu�ɑ��݂���}�V��UI��ID�����
	MACHINE_TYPE machineType = (MACHINE_TYPE)m_selectNumber;

	//�@====================[�@��������0�ȉ��ł���ꍇ�A������Ԃ�����@] 
	//�@�@|=>�@�}�V��
	if (m_machineNumRender->GetNumber() <= 0)
	{
		m_machineNumRender->SetColor(SimpleMath::Color(Colors::Red));
	}
	else
	{
		m_machineNumRender->SetColor(SimpleMath::Color(Colors::Black));
	}
	//�@�@|=>�@����
	if (pSJD->GetMachineData(machineType).alchemi_mp > datas->GetNowMP())
	{
		m_mpNumRender->SetColor(SimpleMath::Color(Colors::Red));
	}
	else
	{
		m_mpNumRender->SetColor(SimpleMath::Color(Colors::Black));
	}
	//�@�@|=>�@����
	if (pSJD->GetMachineData(machineType).alchemi_crystal > datas->GetNowCrystal())
	{
		m_crystalRender->SetColor(SimpleMath::Color(Colors::Red));
	}
	else
	{
		m_crystalRender->SetColor(SimpleMath::Color(Colors::Black));
	}

	//�@====================[�@���������s���@]
	m_selectionLeft		->SetColor(SimpleMath::Color(m_selectionLeft	->GetColorRGB(), transparentVal));
	m_selectionRight	->SetColor(SimpleMath::Color(m_selectionRight	->GetColorRGB(), transparentVal));

	m_machineNumRender	->SetColor(SimpleMath::Color(m_machineNumRender	->GetColorRGB(), transparentVal));
	m_mpNumRender		->SetColor(SimpleMath::Color(m_mpNumRender		->GetColorRGB(), transparentVal));
	m_crystalRender		->SetColor(SimpleMath::Color(m_crystalRender	->GetColorRGB(), transparentVal));

	// None���Ȃ����߂�1�X�^�[�g
	for (int i = 1; i < MACHINE_TYPE::NUM; i++)
	{
		m_machineSelect[i]->GetMachineBox()->SetColor(SimpleMath::Color(m_machineSelect[i]->GetMachineBox()->GetColorRGB(), transparentVal));
	}
}
