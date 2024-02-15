#include "pch.h"
#include "PlayScene.h"

#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/InputSupport.h"
#include "NecromaLib/Singleton/SoundData.h"
#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/Singleton/ModelShader.h"

#include "NecromaLib/GameData/JsonLoder.h"

#include "Scenes/DataManager.h"

#define MAX_SPEED 4

#define SKYDORM_LIGHTCOLOR SimpleMath::Color(0.2f, 0.5f,3.3f, 1.0f)

PlayScene::PlayScene()
{
	m_stageNumber	= DataManager::GetInstance()->GetStageNum();
	m_maxWaveNum	= 0;

	ShareJsonData::GetInstance().LoadingJsonFile_Bullet();
	ShareJsonData::GetInstance().LoadingJsonFile_Machine();

	//�@====================[�@�ő�Wave�����擾����@]
	bool lastWaveCheck = false;
	while (!lastWaveCheck)
	{
		m_maxWaveNum++;
		ShareJsonData::GetInstance().LoadingJsonFile_Stage(m_stageNumber, m_maxWaveNum);
		lastWaveCheck = ShareJsonData::GetInstance().GetStageData().lastWave;

	}

	//�@�X�e�[�W�i���o�[��Wave1��ǂݍ���
	ShareJsonData::GetInstance().LoadingJsonFile_Stage(m_stageNumber, 1);

	// ���{���ɐݒ�
	m_doubleSpeedNum = 1;

	m_uiTransparentTime = 0.0f;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//�@====================[�@�|�X�g�v���Z�X�̐����@]
	m_postProcess		= std::make_unique<MyPostProcess>();
	m_postProcess		->CreateShader();

	//�@====================[�@�t�B�[���h�}�l�[�W���[�N���X�̐����@]
	m_fieldManager		= std::make_unique<FieldObjectManager>();
	m_fieldManager		->Initialize();

	//�@====================[�@�}�E�X�|�C���^�[�N���X�̐����@] 
	m_mousePointer		= std::make_unique<MousePointer>();
	m_mousePointer		->Initialize();

	//�@====================[�@���j�b�g(�}�V��)�}�l�[�W���[�N���X�̐����@] 
	m_AM_Manager		= std::make_unique<AlchemicalMachineManager>();
	m_AM_Manager		->Initialize();

	//�@====================[�@�J�����𓮂����N���X�̐����@]
	m_moveCamera		= std::make_unique<MoveCamera>();
	m_moveCamera		->Initialize();

	//�@====================[�@�G�l�~�[�}�l�[�W���[�N���X�̐����@]
	m_enemyManager		= std::make_unique<EnemyManager>();
	m_enemyManager		->Initialize();

	//�@====================[�@���\�[�X�������Q�[�W�N���X�̐����@]
	m_resourceGauge		= std::make_unique<Gauge>();
	m_resourceGauge		->Initialize();

	//�@====================[�@�~�b�V�����}�l�[�W���[�N���X�̐����@]
	m_missionManager	= std::make_unique<MissionManager>();
	m_missionManager	->Initialize(m_maxWaveNum);

	//�@====================[�@������@�N���X�̐����@]
	m_explanation		= std::make_unique<Explanation>();

	//�@====================[�@�{���{�^���̐����@]
	UI_Data uiData = ShareJsonData::GetInstance().GetUIData("OptionDouble");
	m_doubleSpeedButton = std::make_unique<SelectionBox>(uiData.pos, uiData.rage);

	UI_Data uiData_offset = ShareJsonData::GetInstance().GetUIData("OptionOffset");

	//�@====================[�@�}�E�X�����ӂɈʒu���邩�̔��菈�����擾�@]
	m_collider = std::make_unique<SelectionBox>(uiData.pos, SimpleMath::Vector2(uiData_offset.option["COLLIDER_X"], uiData_offset.option["COLLIDER_Y"]));
	m_collider->Initialize();
	m_collider->SetRect(RECT{ 0,0,1,1 });
	m_collider->SetWorldInfluenceFlag(false);

	//�@====================[�@�V�����f���̓ǂݍ��݁@]
	ShareData& pSD = ShareData::GetInstance();
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(pSD.GetDevice());
	fx->SetDirectory(L"Resources/Models");
	m_skySphere = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/SkyDome.cmo", *fx);

	m_skySphere->UpdateEffects([&](IEffect* effect)
		{
			// ���C�g�̎擾
			auto lights = dynamic_cast<IEffectLights*>(effect);

			// ��������̐F��ύX
			lights->SetAmbientLightColor(SKYDORM_LIGHTCOLOR);
		});

	//�@====================[�@�p������N���X�̐����@]
	m_operationInstructions = std::make_unique<OperationInstructions>();
	m_operationInstructions->Initialize(ShareJsonData::GetInstance().GetStageData().tutorial, this);

	//�@====================[�@�`���[�g���A���N���X�̐����@]
	m_tutorialManager = std::make_unique<TutorialManager>(this);
	m_tutorialManager->ChangeWave(1);

	//�@====================[�@�����_�[�e�N�X�`���̍쐬�@]
	m_offscreenRT	= std::make_unique<DX::RenderTexture>(DXGI_FORMAT_B8G8R8A8_UNORM);
	m_offscreenRT	->SetDevice(pSD.GetDevice());
	RECT rect		= pSD.GetDeviceResources()->GetOutputSize();
	m_offscreenRT	->SetWindow(rect);
	m_offscreenRT	->GetShaderResourceView();

}

GAME_SCENE PlayScene::Update()
{
	ShareData& pSD = ShareData::GetInstance();
	SoundData& pSound = SoundData::GetInstance();
	DeltaTime& pDelta = DeltaTime::GetInstance();

	bool operationNow = m_operationInstructions->GetExplanationFlag();

	pSound.PlayBGM(XACT_WAVEBANK_BGMS_BGM_PLAY, false);

	//�@====================[�@�{���{�^���̍X�V�@]
	m_doubleSpeedButton		->HitMouse();
	m_doubleSpeedNum		+= m_doubleSpeedButton->ClickMouse();
	//�@�@|=>�@����𒴂����瓙������
	if (m_doubleSpeedNum > MAX_SPEED) m_doubleSpeedNum = 1;
	//�@�@|=>�@�{���ɂ���
	pDelta.SetDoubleSpeed((float)m_doubleSpeedNum);

	//�@====================[�@�p������N���X�̍X�V�@]
	m_operationInstructions	->Update(this, m_moveCamera->GetStopCameraFlag());

	//�@====================[�@�~�b�V�����N���X�̍X�V�@]
	m_missionManager		->Update(m_AM_Manager.get(), m_enemyManager.get(), m_fieldManager.get());

	//�@====================[�@�`���[�g���A���N���X�̍X�V�@]
	m_tutorialManager		->Update(m_missionManager->NextWaveFlag());

	//�@====================[�@�}�E�X����N���X�̍X�V�@]
	m_explanation			->Update();

	//�@====================[�@���̃E�F�[�u�ɐi�񂾍ۂ̃����[�h�����@]
	if (m_missionManager->NextWaveFlag())
	{
		DataManager* pDM = DataManager::GetInstance();
		ShareJsonData& pSJD = ShareJsonData::GetInstance();
		Stage_Data stageData = pSJD.GetStageData();

		//�@�@|=>�@�E�F�[�u�����ēx�擾����
		m_AM_Manager		->ReloadResource();
		m_enemyManager		->ReloadEnemyData();
		m_missionManager	->ReloadWave();
		m_tutorialManager	->ChangeWave(m_missionManager->GetWave());

		//�@�@|=>�@���\�[�X�Q��ǉ�����
		pDM->SetNowBaseHP	(pDM->GetNowBaseHP()	+ stageData.resource.hp);
		pDM->SetNowCrystal	(pDM->GetNowCrystal()	+ stageData.resource.crystal);
		pDM->SetNowMP		(pDM->GetNowMP()		+ stageData.resource.mp);
		m_fieldManager->GetPlayerBase()->SetExp(m_fieldManager->GetPlayerBase()->GetExp() + stageData.resource.exp);

	}

	//�@====================[�@�V�[���J�ځ@]
	//�@�@|=>�@�^�C�g��
	if (m_operationInstructions->GetTitleSceneButton()->ClickMouse())	return GAME_SCENE::TITLE;
	//�@�@|=>�@�X�e�[�W�Z���N�g
	if (m_operationInstructions->GetSelectSceneButton()->ClickMouse())	return GAME_SCENE::SELECT;

	//�@====================[�@�`���[�g���A�����Ȃ�Έȉ��̏������s��Ȃ��@]
	if (operationNow) 		return GAME_SCENE();

	//�@====================[�@�J�����N���X�̍X�V�@]
	m_moveCamera		->Update(!m_AM_Manager->GetMachineSelect()->get()->GetHitMouseToSelectBoxEven(), true);

	//�@====================[�@�t�B�[���h�}�l�[�W���[�N���X�̍X�V�@]
	m_fieldManager		->Update(m_enemyManager.get());
	
	//�@====================[�@�}�E�X�|�C���^�[�N���X�̍X�V�@]
	m_mousePointer		->Update();

	//�@====================[�@���j�b�g�}�l�[�W���[�̍X�V�@]
	m_AM_Manager		->Update(m_fieldManager.get(),
								 m_mousePointer.get(),
								 m_enemyManager.get(),
								 m_moveCamera.get());

	//�@====================[�@�~�b�V�����̎��ԍX�V�@]
	m_missionManager	->TimerUpdate();

	//�@====================[�@�G�l�~�[�}�l�[�W���[�N���X�̍X�V�@]
	m_enemyManager		->Update(m_fieldManager->GetPlayerBase()->GetPos());

	//�@====================[�@���\�[�X�Q�[�W�`��N���X�̍X�V�@]
	m_resourceGauge		->Update();

	//�@====================[�@�G�l�~�[���{�E�F�[�u��ɑ��݂��邩�`�F�b�N�@]
	bool enemyActivs = !m_enemyManager->GetEnemyData()->empty();

	//�@====================[�@�G�l�~�[To�o���b�g�@]
	if (!m_AM_Manager->GetBullet()->empty() && enemyActivs) EnemyToBullet();

	//�@====================[�@�G�l�~�[To���_�@]
	if (enemyActivs)	  EnemyToPlayerBase();

	//�@====================[�@�J�����N���X�����ɃJ�����𓮂����@]
	pSD.GetCamera()->SetViewMatrix(m_moveCamera->GetViewMatrix());
	pSD.GetCamera()->SetTargetPosition(m_moveCamera->GetTargetPosition());
	pSD.GetCamera()->SetEyePosition(m_moveCamera->GetEyePosition());

	//�@====================[�@�s�k���@]
	if (m_missionManager->MissionFailure())		return GAME_SCENE::RESULT;

	//�@====================[�@�X�e�[�W�N���A���@]
	if (m_missionManager->MissionComplete())
	{
		// �X�e�[�W�U�����𓾂�
		Json::WritingJsonFile_ClearData(m_stageNumber,
			m_AM_Manager->GetAlchemicalMachineObject(),
			m_missionManager->GetStartTimer());

		return GAME_SCENE::RESULT;
	}

	//�@====================[�@�}�V���̃f�[�^�ēǂݍ��݁@]
	InputSupport* pINP = &InputSupport::GetInstance();
	if (pINP->GetKeybordState().IsKeyReleased(Keyboard::M))
	{
		ModelShader::GetInstance().CreateModelShader();
		ShareJsonData::GetInstance().LoadingJsonFile_Machine();
	}

	return GAME_SCENE();
}

void PlayScene::Draw()
{
	ShareData& pSD = ShareData::GetInstance();
	auto context = pSD.GetContext();

	ModelShader& pMS = ModelShader::GetInstance();

	// �[�x�}�b�v����
	auto srv = pMS.GetShadowMap()->GetShaderResourceView();

	// �[�x�}�b�v�ɏ�������
	DrawShadow();

	//�@====================[�@���ɖ߂����߂̃����_�[�^�[�Q�b�g�@]
	auto renderTarget = pSD.GetDeviceResources()->GetRenderTargetView();
	auto depthStencil = pSD.GetDeviceResources()->GetDepthStencilView();

	//�@====================[�@�V�K�����_�[�^�[�Q�b�g�@]
	auto offscreenRTV = m_offscreenRT->GetRenderTargetView();
	auto offscreenSRV = m_offscreenRT->GetShaderResourceView();

	// -------------------------------------------------------------------------- //
	// �����_�[�^�[�Q�b�g��ύX�isceneRT�j
	// -------------------------------------------------------------------------- //
	context->ClearRenderTargetView(m_offscreenRT->GetRenderTargetView(), Colors::White);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &offscreenRTV, depthStencil);
	// -------------------------------------------------------------------------- //

	pSD.GetSpriteBatch()->Begin(SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	SimpleMath::Matrix modelData = SimpleMath::Matrix::Identity;
	modelData = SimpleMath::Matrix::CreateScale({ 1.0f,1.0f,1.0f });
	modelData *= SimpleMath::Matrix::CreateTranslation({ 0.0f,10.0f,0.0f });

	// �V���`��
	m_skySphere->Draw(pSD.GetContext(), *pSD.GetCommonStates(), modelData, pSD.GetView(), pSD.GetProjection(), false, [&]()
		{
		});

	//�@====================[�@�t�B�[���h�I�u�W�F�N�g�`��@] 
	m_fieldManager->Draw();

	//�@====================[�@�G�l�~�[�`��@]
	m_enemyManager->Render();

	//�@====================[�@�}�V���̕`��@]
	m_AM_Manager->Render();

	pSD.GetSpriteBatch()->End();

	// -------------------------------------------------------------------------- //
	// �����_�[�^�[�Q�b�g�ƃr���[�|�[�g�����ɖ߂�
	// -------------------------------------------------------------------------- //
	context->ClearRenderTargetView(renderTarget, Colors::White);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);
	auto const viewport = pSD.GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &viewport);
	// -------------------------------------------------------------------------- //

	// ���\�[�X�̊��蓖�Ă���������
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	context->PSSetShaderResources(1, 1, nullsrv);

	// �|�X�g�v���Z�X��K��������
	m_postProcess->Render(&offscreenSRV, &srv);

	// ==== 1�p�X�ڂ�`�悷��
	//pSD.GetSpriteBatch()->Begin();
	//pSD.GetSpriteBatch()->Draw(srv, SimpleMath::Vector2::Zero);
	//pSD.GetSpriteBatch()->End();

	// �}�E�X�|�C���^�[���f�����o��
	m_mousePointer->Draw();
	m_mousePointer->ModelDraw(m_AM_Manager->GetSelectModel());
}

void PlayScene::DrawShadow()
{
	ShareData& pSD		= ShareData::GetInstance();
	ModelShader& pMS	= ModelShader::GetInstance();
	auto device = ShareData::GetInstance().GetDeviceResources();
	auto context		= pSD.GetContext();

	//�@====================[�@�V���������_�[�^�[�Q�b�g�@]
	auto rtv = pMS.GetShadowMap()->GetRenderTargetView();
	auto dsv = pMS.GetDepthStencilView().Get();

	//�@====================[�@���ɖ߂����߂̃����_�[�^�[�Q�b�g�@]
	auto renderTarget = device->GetRenderTargetView();
	auto depthStencil = device->GetDepthStencilView();

	//�@====================[�@�����_�[�^�[�Q�b�g��ύX�@]
	context->ClearRenderTargetView(pMS.GetShadowMap()->GetRenderTargetView(), Colors::Black);
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, dsv);

	//�@====================[�@�r���[�|�[�g��ݒ�@]
	int width	= device->GetOutputSize().right;
	int height	= device->GetOutputSize().bottom;

	D3D11_VIEWPORT vp = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f };
	context->RSSetViewports(1, &vp);

	//�@====================[�@���f���`��@]
	SimpleMath::Matrix modelData = SimpleMath::Matrix::Identity;
	modelData = SimpleMath::Matrix::CreateScale({ 1.0f,1.0f,1.0f });
	modelData *= SimpleMath::Matrix::CreateTranslation({ 0.0f,10.0f,0.0f });

	m_skySphere->Draw(pSD.GetContext(), *pSD.GetCommonStates(), modelData, pSD.GetView(), pSD.GetProjection(), false, [&]()
		{
			ModelShader::GetInstance().ShadowModelDraw(false);
		});

	m_fieldManager	->WriteDepath();

	m_AM_Manager	->WriteDepath();

	// -------------------------------------------------------------------------- //
	// �����_�[�^�[�Q�b�g�ƃr���[�|�[�g�����ɖ߂�
	// -------------------------------------------------------------------------- //
	context->ClearRenderTargetView(renderTarget, Colors::White);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);
	auto const viewport = device->GetScreenViewport();
	context->RSSetViewports(1, &viewport);
	// -------------------------------------------------------------------------- //
}

void PlayScene::DrawUI()
{
	ShareData& pSD	= ShareData::GetInstance();
	auto device		= ShareData::GetInstance().GetDeviceResources();
	float width		= static_cast<float>(device->GetOutputSize().right);
	float height	= static_cast<float>(device->GetOutputSize().bottom);

	SpriteLoder::TextureData bottomTexture = SpriteLoder::GetInstance().GetBottomLabel();

	pSD.GetSpriteBatch()->Begin();
	RECT rect = {0,0,bottomTexture.width,bottomTexture.height};
	pSD.GetSpriteBatch()->Draw(bottomTexture.tex.Get(),
		SimpleMath::Vector2(width / 2.0f, height),
		&rect,
		Colors::White,
		0.0f,
		SimpleMath::Vector2(bottomTexture.width / 2.0f, static_cast<float>(bottomTexture.height)));

	pSD.GetSpriteBatch()->End();

	//�@====================[�@UI�̕`�揈���@]
	m_enemyManager			->RenderUI();
	m_AM_Manager			->DrawUI();

	m_fieldManager			->DrawBillboardUI();

	m_operationInstructions	->Render();

	m_tutorialManager		->Render();

	m_resourceGauge			->Render();

	//�@�@|=>�@�{���A�C�R������`����s��
	m_doubleSpeedButton		->DrawUI(SpriteLoder::UIICON_TYPE::DISMATIONG + m_doubleSpeedNum);

	m_explanation			->Render(m_AM_Manager->GetMachineSelect()->get()->GetHitMouseToSelectBoxEven(), m_AM_Manager->GetRotateStopFlag());

	//�@�@|=>�@�`�揇�̊֌W�ɂ��A�Ō�ɕ`����s��
	m_operationInstructions	->Render_Layer2();
	m_tutorialManager		->Render_Layer2();

	m_missionManager->Render(m_maxWaveNum);
}

void PlayScene::Finalize()
{
	m_fieldManager->Finalize();
	m_fieldManager.reset();

	m_mousePointer->Finalize();
	m_mousePointer.reset();

	m_AM_Manager->Finalize();
	m_AM_Manager.reset();

	m_enemyManager->Finalize();
	m_enemyManager.reset();

	m_moveCamera.reset();

}

void PlayScene::EnemyToAMMachine()
{
}

void PlayScene::EnemyToPlayerBase()
{
	PlayerBase* playerBase = m_fieldManager->GetPlayerBase();

	for (std::list<EnemyObject>::iterator enemyIt = m_enemyManager->GetEnemyData()->begin(); enemyIt != m_enemyManager->GetEnemyData()->end(); enemyIt++)
	{
		// �_�E���L���X�g���s���AGameObject3D�^�ɕϊ�������̏����𓾂�
		bool hitEnemy = CircleCollider(playerBase->GetObject3D(), enemyIt->GetObject3D());

		// �����蔻�菈��
		if (hitEnemy)
		{

			playerBase->Damage(enemyIt->GetPower());
			enemyIt->HitMachine(hitEnemy);
			enemyIt->SetStopFlag(hitEnemy);
			// ����������
			enemyIt->SetAccele(-enemyIt->GetAccele());

		}
	}
}

void PlayScene::EnemyToBullet()
{

	for (std::list<std::unique_ptr<Bullet>>::iterator bulletIt = m_AM_Manager->GetBullet()->begin(); bulletIt != m_AM_Manager->GetBullet()->end(); bulletIt++)
	{
		for (std::list<EnemyObject>::iterator enemyIt = m_enemyManager->GetEnemyData()->begin(); enemyIt != m_enemyManager->GetEnemyData()->end(); enemyIt++)
		{

			// �����蔻�����邩�ۂ�
			if (!enemyIt->GetColliderActive()) continue;

			// �����蔻�菈��
			if (CircleCollider(bulletIt->get()->GetObject3D(), enemyIt->GetObject3D()))
			{

				SimpleMath::Vector3 hitVectol = bulletIt->get()->GetPos() - enemyIt->GetPos();

				bulletIt->get()->SetEnemyHit(true);
				bulletIt->get()->SetLife(0);

				enemyIt->HitBullet(hitVectol, (int)bulletIt->get()->GetDamage());

			}
		}
	}
}

void PlayScene::TransparentUI(float transparentVal)
{
	m_doubleSpeedButton->SetColor(SimpleMath::Color(m_doubleSpeedButton->GetColorRGB(), transparentVal));

	SelectionBox* explanationButton = m_operationInstructions->GetExplanationButton();
	explanationButton->SetColor(SimpleMath::Color(explanationButton->GetColorRGB(), transparentVal));

}
