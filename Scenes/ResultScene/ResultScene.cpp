#include "pch.h"
#include "ResultScene.h"
#include "Scenes/ResultScene/Camera/ResultCamera.h"
#include "Scenes/ResultScene/ResultDirection.h"

#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/SoundData.h"

#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/GameData/SpriteCutter.h"

#include "Scenes/PlayScene/UI/SelectionBox.h"
#include "Scenes/Commons/UIKeyControl.h"
#include "Scenes/Commons/DrawMachine.h"

#include "Scenes/TitleScene/TitleLogo/Veil.h"

#include "Scenes/DataManager.h"

//�@====================[�@�V���̏��@]
#define SKY_ROTATION	SimpleMath::Vector3{8.0f, 7.0f, 90.0f}
#define SKY_SCALE	1.5f
#define SKY_POS_Y	30.0f
#define SKY_LIGHT SimpleMath::Color(0.2f, 0.2f, 0.4f, 0.8f)

//�@====================[�@�e�N�X�`���̑傫���@]
#define TEX_W 128
#define TEX_H 28

ResultScene::ResultScene()
{
	UI_Data ui_data			= ShareJsonData::GetInstance().GetUIData("ResultNext");
	m_selectionBox_Next		= std::make_unique<SelectionBox>(ui_data.pos, ui_data.rage);

	ui_data					= ShareJsonData::GetInstance().GetUIData("ResultRetry");
	m_selectionBox_Retry	= std::make_unique<SelectionBox>(ui_data.pos, ui_data.rage);

	ui_data					= ShareJsonData::GetInstance().GetUIData("ResultSelect");
	m_selectionBox_Back		= std::make_unique<SelectionBox>(ui_data.pos, ui_data.rage);

	m_uiKeyControl			= std::make_unique<UIKeyControl>();

	m_uiKeyControl->AddUI(m_selectionBox_Next.get());
	m_uiKeyControl->AddUI(m_selectionBox_Retry.get());
	m_uiKeyControl->AddUI(m_selectionBox_Back.get());

	ShareJsonData::GetInstance().LoadingJsonFile_ClearData(DataManager::GetInstance()->GetStageNum());

	m_drawMachine = std::make_unique<DrawMachine>();
	m_drawMachine->Initialize(0);

	m_resultCamera = std::make_unique<ResultCamera>();
	m_resultCamera->Initialize();

	m_resultDirection = std::make_unique<ResultDirection>();

	ShareData& pSD = ShareData::GetInstance();

	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(pSD.GetDevice());
	fx->SetDirectory(L"Resources/Models");
	m_baseModel = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/Tower.cmo", *fx);
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	ShareData& pSD = ShareData::GetInstance();
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(pSD.GetDevice());
	fx->SetDirectory(L"Resources/Models");

	m_skySphere = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/SkySphere.cmo", *fx);

	m_skySphere->UpdateEffects([&](IEffect* effect)
		{
			auto lights = dynamic_cast<IEffectLights*>(effect);
			lights->SetAmbientLightColor(SKY_LIGHT);
		});

}

GAME_SCENE ResultScene::Update()
{

	ShareData& pSD = ShareData::GetInstance();
	SoundData& pSound = SoundData::GetInstance();
	DataManager& pDataM = *DataManager::GetInstance();
	pSound.PlayBGM(XACT_WAVEBANK_BGMS_BGM_RESULT, false);

	//�@====================[�@���o�X�V�����@]
	m_resultDirection->Update();
	m_resultCamera->Update();

	//�@====================[�@�J�����𓮂����@] 
	pSD.GetCamera()->SetViewMatrix(m_resultCamera->GetViewMatrix());
	pSD.GetCamera()->SetTargetPosition(m_resultCamera->GetTargetPosition());
	pSD.GetCamera()->SetEyePosition(m_resultCamera->GetEyePosition());

	//�@====================[�@UI�X�V�����@] 
	m_selectionBox_Next->HitMouse();
	m_selectionBox_Back->HitMouse();
	m_selectionBox_Retry->HitMouse();

	m_uiKeyControl->Update();

	//�@====================[�@�}�V���X�V�����@]
	m_drawMachine->Update();

	//�@====================[�@�V�[���J�ځ@]
	m_selectionBox_Next->SetActiveFlag(pDataM.GetStageNum() < ShareJsonData::GetInstance().GetGameParameter().stage_Max);
	//�@�@|=>�@���̃X�e�[�W
	if (m_selectionBox_Next->ClickMouse())
	{

		pDataM.SetStageNum(pDataM.GetStageNum() + 1);
		// ���̃X�e�[�W�̃f�[�^��ǂ݂Ƃ�
		ShareJsonData::GetInstance().LoadingJsonFile_Stage(pDataM.GetStageNum(),1);

		return GAME_SCENE::PLAY;
	}
	//�@�@|=>  �Ē���
	if (m_selectionBox_Retry->ClickMouse())
	{

		// ���̃X�e�[�W�̃f�[�^��ǂ݂Ƃ�
		ShareJsonData::GetInstance().LoadingJsonFile_Stage(DataManager::GetInstance()->GetStageNum(),1);

		return GAME_SCENE::PLAY;
	}
	//�@�@|=>�@�Z���N�g�V�[���@
	if (m_selectionBox_Back->ClickMouse()) return GAME_SCENE::SELECT;

	return GAME_SCENE();
}

void ResultScene::Draw()
{
	ShareData& pSD = ShareData::GetInstance();

	//�@====================[�@�V�����f���`��@]
	SimpleMath::Matrix modelData = SimpleMath::Matrix::Identity;
	modelData = SimpleMath::Matrix::CreateTranslation({ 0.0f,SKY_POS_Y,0.0f });
	modelData *= SimpleMath::Matrix::CreateScale(SKY_SCALE);
	modelData *= SimpleMath::Matrix::CreateFromYawPitchRoll(SKY_ROTATION);
	m_skySphere			->Draw(pSD.GetContext(), *pSD.GetCommonStates(), modelData, pSD.GetView(), pSD.GetProjection());

	m_resultDirection	->Render();

	m_drawMachine		->Render();
}

void ResultScene::DrawUI()
{
	SpriteLoder& pSL = SpriteLoder::GetInstance();

	//�@====================[�@UI�̕`��@]
	m_selectionBox_Next	->DrawUI(pSL.GetResultTextTexture().Get(), SpriteCutter(TEX_W, TEX_H, 0, 0), SimpleMath::Color(Colors::Black), 1.0f, TEX_W, TEX_H);
	m_selectionBox_Back	->DrawUI(pSL.GetResultTextTexture().Get(), SpriteCutter(TEX_W, TEX_H, 1, 0), SimpleMath::Color(Colors::Black), 1.0f, TEX_W, TEX_H);
	m_selectionBox_Retry->DrawUI(pSL.GetResultTextTexture().Get(), SpriteCutter(TEX_W, TEX_H, 2, 0), SimpleMath::Color(Colors::Black), 1.0f, TEX_W, TEX_H);
}

void ResultScene::Finalize()
{
	m_drawMachine->Finalize();
}
