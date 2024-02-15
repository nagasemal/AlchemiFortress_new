#include "pch.h"
#include "AlchemicalMachineManager.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/InputSupport.h"
#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/Singleton/SoundData.h"

#include "Scenes/Commons/DrawVariableNum.h"

#include "DirectXHelpers.h"

#include "Scenes/PlayScene/Camera/MoveCamera.h"
#include "AM_None.h"
#include "AM_Attacker.h"
#include "AM_Defenser.h"
#include "AM_Mining.h"
#include "AM_Recovery.h"
#include "AM_Upper.h"

#define SPEED 0.0025f

// ���͂��񕜂���Ԋu
#define MPPLUSTIME 2.0f
// ���͂̉񕜗�
#define MPPLUSNUM  1.0f
// ���͂�������͂��߂�Œ�}�V����
#define MPPUSLMACHINE 8

// �~���̈�ԏ������ꍇ�ɂ�����}�V���̍ő吔
#define CIRCLE_MAX_MIN  4

// �~���̍ő僉�C��
#define CIRCLE_MAX_LINE 9

// ���C�����m�̊Ԋu
#define CIRCLE_LINE_DISTANCE 5.5f

// ���@�w�o���̍���(��)
#define MAGICCIRCLE_HEIGHT	0.3f 

// �o���b�g�̑傫��
#define BULLET_RAGE 0.75f

// ���[���h��Ԃɏo��UI�̑傫������
#define WORLD_UI_SIZE 0.01f

// ���[���h��Ԃɏo��UI�̈ʒu����
#define WORLD_UI_POSY 4.5f
// �N���b�N�U�������[���h��Ԃɏo��UI�̈ʒu����
#define CLICKPROMPT_POS SimpleMath::Vector3(1.0f,-1.0f,0.0f)

AlchemicalMachineManager::AlchemicalMachineManager() :
	m_allHitObjectToMouse(),
	m_selectNumber(-1),
	m_prevSelectMachinePos(0, 0, 0),
	m_mpPulsTimer(),
	m_AMnums{ 0,0,0,0,0,0 },
	m_saveWheelValue(0),
	m_scrollValue(),
	m_rotationStop(),
	m_crystalPulsVal(),
	m_mpPulsVal(),
	m_spawnMachine		(MACHINE_TYPE::NONE),
	m_lvUpMachine		(MACHINE_TYPE::NONE)
{
}

AlchemicalMachineManager::~AlchemicalMachineManager()
{
}

void AlchemicalMachineManager::Initialize()
{
	ShareData& pSD = ShareData::GetInstance();

	//�@====================[�@�N���X�擾�@]

	//�@�@|=>�@�}�V��UI�̕`��N���X
	m_selectManager		= std::make_unique<MachineSelectManager>();
	m_selectManager		->TextuerLoader();
	m_selectManager		->Initialize();

	//�@�@|=>�@�}�V���̃��f���p�b�N�N���X
	m_AMFilter = std::make_unique<AlchemicalMachineFilter>();

	//�@�@|=>�@�o���b�g�Ɏg�p���郂�f��
	m_testBox = GeometricPrimitive::CreateSphere(pSD.GetContext(),0.75f);

	//�@�@|=>�@�ۉe�`��N���X
	m_dorpShadow		= std::make_unique<DorpShadow>();
	m_dorpShadow		->Initialize();

	//�@�@|=>�@[�p�[�e�B�N��] �o���b�gTo�G�l�~�[
	m_particle_hit		= std::make_unique<Particle>(Particle::HIT_BULLET);
	m_particle_hit		->Initialize();

	//�@�@|=>�@[�p�[�e�B�N��] �}�V���ݒu��
	m_particle_Put		= std::make_unique<Particle>(Particle::MACHINE_SPAWN);
	m_particle_Put		->Initialize();

	//�@�@|=>�@[�p�[�e�B�N��] �f�B�t�F���T�[�U����
	m_particle_Gurd		= std::make_unique<Particle>(Particle::DEFENSE_EFFECT);
	m_particle_Gurd		->Initialize();

	//�@�@|=>�@[�p�[�e�B�N��] �N���X�^�������
	m_particle_Mining	= std::make_unique<Particle>(Particle::MINING_EFFECT);
	m_particle_Mining	->Initialize(L"Crystal");
	m_particle_Mining	->SetParticleSpawnTime(1.0f);

	//�@�@|=>�@[�p�[�e�B�N��] ���͉����
	m_particle_Recovery = std::make_unique<Particle>(Particle::RECOVERY_EFFECT);
	m_particle_Recovery	->Initialize(L"MP");
	m_particle_Recovery	->SetParticleSpawnTime(1.0f);

	//�@�@|=>�@[�p�[�e�B�N��] �o���b�g�̋O��
	m_particle_Bullet	= std::make_unique<Particle>(Particle::BULLET_LINE);
	m_particle_Bullet	->Initialize();

	//�@�@|=>�@�}�V���p���@�w�`��N���X
	m_magicCircle		= std::make_unique<MagicCircle>();
	m_magicCircle		->Initialize();

	//�@�@|=>�@���_�p���@�w�`��N���X
	m_magicCircle_Field = std::make_unique<MagicCircle>();
	m_magicCircle_Field	->Initialize();


	//�@====================[�@�}�V���̐����@]
	CreateAMMachine();
	
	//�@====================[�@���ݏ�ɏo����}�V���̐ݒ�@]
	LvToObjectActives(1);
	
	//�@====================[�@Json���烊�\�[�X���擾����@]
	JsonLoadResources();

	//�@====================[�@�r���{�[�h�`��Ɏg�p�@]
	//�@�@|=> �G�t�F�N�g���쐬
	m_effect = std::make_unique<BasicEffect>(ShareData::GetInstance().GetDevice());
	m_effect->SetTextureEnabled(true);
	m_effect->SetVertexColorEnabled(true);
	m_effect->SetLightingEnabled(false);

	//�@�@|=> ���̓��C�A�E�g���쐬
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect(
			ShareData::GetInstance().GetDevice(),
			m_effect.get(),
			VertexPositionColorTexture::InputElements,
			VertexPositionColorTexture::InputElementCount,
			m_inputLayout.ReleaseAndGetAddressOf())
	);

}

void AlchemicalMachineManager::Update(
	FieldObjectManager* fieldManager,
	MousePointer* pMP,
	EnemyManager* enemys,
	MoveCamera* moveCamera)
{
	InputSupport& pINP = InputSupport::GetInstance();
	DataManager& pDM = *DataManager::GetInstance();
	PlayerBase* pPlayerBase = fieldManager->GetPlayerBase();

	//�@====================[�@���͊֌W�@]
	auto mouse			= pINP.GetMouseState();
	auto keyboard		= pINP.GetKeybordState();
	bool leftRelease	= pINP.LeftButton_Release();

	//�@====================[�@��]�̒�~/�ĊJ�@]
	if (pINP.RightButton_Press())
	{
		m_rotationStop = !m_rotationStop;
	}

	//�@====================[�@�ݒu���̐ݒ�@]
	LvToObjectActives(pPlayerBase->GetBaseLv());

	//�@====================[�@�}�V���̐����J�E���g����ϐ��@]
	//�@�@|=>�@�S�Ẵ}�V��
	int amNum			= 0;
	//�@�@|=>�@None�}�V��
	int amNum_Nomal		= 0;

	//�@====================[�@���\�[�X�̎擾�ʂ̃��Z�b�g�@]
	m_mpPulsVal			= 0;
	m_crystalPulsVal	= 0;

	//�@====================[�@�}�V��To�}�E�X�̔��胊�Z�b�g�@]
	m_allHitObjectToMouse = false;

	//�@====================[�@�ʒm�n�ϐ��̃��Z�b�g�@]
	m_spawnMachine = m_lvUpMachine = MACHINE_TYPE::NONE;

	//�@====================[�@���͉񕜎����@]
	m_mpPulsTimer += DeltaTime::GetInstance().GetDeltaTime();

	//�@====================[�@�p�[�e�B�N���̍X�V�@]
	Update_Particle();

	//�@====================[�@�I����Ԃ̉����@]
	if (leftRelease)
	{
		// �J�����ړ��p�̎��ԕϐ����\�Ȃ�΃��Z�b�g����
		moveCamera->ResetTargetChangeTimer();

		// �I�����ꂽ�I�u�W�F�N�g���Ȃ��ꍇ�̏���
		if (m_selectNumber != -1)
		{
			m_prevSelectMachinePos = m_AMObject[m_selectNumber]->GetPos();
		}
		else
		{
			m_prevSelectMachinePos = SimpleMath::Vector3();
		}

		// �I����Ԃ̉���
		if (!pINP.GetHitUI())
		{
			m_selectNumber = -1;
		}
	}

	//�@====================[�@�Z���N�g�}�l�[�W���[�̍X�V�����@]
	m_selectManager->Update(fieldManager);

	//�@====================[�@�I�𒆂̃I�u�W�F�N�g������ꍇ�̏����@]
	if (m_selectNumber != -1)
	{
		//�@�����_�ړ�
		moveCamera->TargetChange(m_AMObject[m_selectNumber]->GetData().pos);

		//�@�I���ς݂̃I�u�W�F�N�g�̑I�����A�b�v�f�[�g����
		m_AMObject[m_selectNumber]->SelectUpdate();
		m_AMObject[m_selectNumber]->SelectUpdate_Common();

		//�@�I���I�u�W�F�N�g�ɖ��@�w�W�J
		m_magicCircle->CreateMagicCircle(
			m_AMObject[m_selectNumber]->GetPos(),
			m_AMObject[m_selectNumber]->GetMagicCircle().r,
			m_AMObject[m_selectNumber]->GetColor());

	}
	//�@====================[�@�I�𒆂̃I�u�W�F�N�g���Ȃ��ꍇ�̏����@]
	else
	{
		m_magicCircle		->DeleteMagicCircle();

		//�@�����_�ړ�
		moveCamera->TargetChange({ 0,0,0 });
	}

	//�@====================[�@�o�^�����e���������@]
	m_dorpShadow->DeleteShadow();

	//�@====================[�@�S�}�V���̍X�V�����@]
	for (int i = 0; i < m_AMObject.size(); i++)
	{
		//�@================[�@�}�V���𓮂����@]
		MovingMachine(i);
		m_AMObject[i]->Update_Common();

		//�@================[�@�}�V��To�}�E�X�@]
		if (m_AMObject[i]->GetHitMouse() && m_AMObject[i]->GetActive())
		{

			m_allHitObjectToMouse = true;

			// �N���b�N�őI����ԂɈڍs
			if (leftRelease && m_selectNumber != i)
			{
				// �I������Ă���}�V���̃C���f�b�N�X�ԍ���n��
				m_selectNumber = i;
			}
		}

		m_AMObject[i]->SetSelectModeFlag(m_selectNumber == i);

		//�@���݂��Ă���Ώ����𑱂���
		if (!m_AMObject[i]->GetActive()) continue;

		// �A���P�~�J���}�V���̍X�V����
		m_AMObject[i]->Update();
		m_AMObject[i]->HitToMouse(pMP);

		if (m_AMObject[i]->GetModelID() == MACHINE_TYPE::NONE)
		{
			// �����ɑ��݂��Ă���}�V���̑����𒲂ׂ� (None)
			amNum_Nomal++;

			// ������0�Ȃ�Ε\�����s��Ȃ�
			if (m_AMnums[m_selectManager->GetSelectMachineType()] <= 0)
			{
				m_AMObject[i]->SetActive(false);
			}
			else
			{
				m_AMObject[i]->SetActive(true);
			}

		}
		
		// �S�̐�
		amNum++;

		if (m_AMObject[i]->GetActive())
		{
			m_dorpShadow->CreateShadow(m_AMObject[i]->GetData().pos);
		}

		// MP�ǉ����� (�C���f�b�N�X�����J�o���[���w���A���͉񕜎������������A��]���~�߂Ă���Ζ��͂��񕜂�����)
		if (m_mpPulsTimer >= MPPLUSTIME && !m_rotationStop && m_AMObject[i]->GetModelID() == MACHINE_TYPE::RECOVERY)
		{
			// ���J�o���[�}�V���������Ă�������Z���s��
			m_mpPulsVal += (int)m_AMObject[i]->GetHP() > 0 ? (int)m_AMObject[i]->GetMachineEffectValue() * m_AMObject[i]->GetLv() : 0;
		}

		// �}�V���̑ϋv�l��0�ɂȂ���
		if (m_AMObject[i]->GetDethFlag())
		{
			Dismantling(i);
		}

	}

	for (int i = 0; i < m_AMObject.size(); i++)
	{
		// �A���P�~�J���}�V���̌ʍX�V����
		Update_Upper(i, enemys);
		Update_Attacker(i, enemys);
		Update_Defenser(i, enemys);
		Update_Mining(i, fieldManager, enemys);
		Update_Recovery(i, enemys);
	}

	//�@====================[�@�}�V�����������鏈���@]
	SpawnAMMachine((leftRelease && !pINP.GetHitUI() && m_allHitObjectToMouse));

	//�@====================[�@���̓��\�[�X�̑����@]
	//�@�@|=>�@����������@��]���~�܂��Ă��Ȃ�
	if (m_mpPulsTimer >= MPPLUSTIME && !m_rotationStop)
	{
		m_mpPulsTimer	= 0;
		m_mpPulsVal		+= ((int)MPPLUSNUM * ((amNum - amNum_Nomal) / MPPUSLMACHINE));
		pDM.SetNowMP(pDM.GetNowMP() + m_mpPulsVal);
	}

	//�@====================[�@�N���X�^�����\�[�X�̑����@]
	pDM.SetNowCrystal(pDM.GetNowCrystal() + m_crystalPulsVal);


	//�@====================[�@�������̑����@]
	if (m_selectManager->GetManufacturingFlag())
	{
		m_AMnums[m_selectManager->GetSelectMachineType()]++;
	}

	//�@====================[�@�}�E�X�̓����蔻���߂��@]
	if(leftRelease)  pMP->ReleaseLeftButtom();

	//�@====================[�@�o���b�g�X�V�����@]
	for (std::list<std::unique_ptr<Bullet>>::iterator it = m_bullets.begin(); it != m_bullets.end(); it++)
	{
		it->get()->Update();
		m_particle_Bullet->Update(it->get()->GetPos(),true,it->get()->GetColor());

		// �q�N���X����false�ŏ���
		if ((it)->get()->deleteRequest())
		{
			m_particle_hit->OnShot(it->get()->GetPos(),true,it->get()->GetColor());
			it = m_bullets.erase(it);
			if (it == m_bullets.end()) break;
		}
	}

	//�@====================[�@���@�w�̈ʒu���߂�@]
	m_magicCircle_Field->CreateMagicCircle(
		SimpleMath::Vector3{ 0,MAGICCIRCLE_HEIGHT,0 },
		pPlayerBase->GetBaseLv() * CIRCLE_LINE_DISTANCE);

	if(!m_rotationStop) m_magicCircle_Field->CreateWorld();
}

void AlchemicalMachineManager::Render()
{

	//�@====================[�@�u�����ۂɏo���p�[�e�B�N���@]
	//�@�@|=>�@�`�揇�̉e���Ő�ɕ`��
	m_particle_Put->Render();

	//�@====================[�@�V���G�b�g�`��p�h���[�R�[���@]
	for (int i = 0; i < m_AMObject.size(); i++)
	{
		// ���݂��Ă��邩�`�F�b�N
		if (m_AMObject[i]->GetActive())
		{

			// ���f���̕`��			�I�u�W�F�N�g�Ɋ��蓖�Ă�ꂽID�����ƂɃ��f���z�񂩂�f�[�^�����o��
			m_AMObject[i]->ModelRender(m_AMFilter->HandOverAMModel(m_AMObject[i]->GetModelID()),
									   m_AMFilter->GetRingModel(m_AMObject[i]->GetModelID()),true);

		}
	}

	//�@====================[�@�ʏ�`��p�h���[�R�[���@]
	for (int i = 0; i < m_AMObject.size(); i++)
	{
		// ���݂��Ă��邩�`�F�b�N
		if (m_AMObject[i]->GetActive())
		{
			// ���f���̕`��			�I�u�W�F�N�g�Ɋ��蓖�Ă�ꂽID�����ƂɃ��f���z�񂩂�f�[�^�����o��
			m_AMObject[i]->ModelRender(m_AMFilter->HandOverAMModel(m_AMObject[i]->GetModelID()),
									   m_AMFilter->GetRingModel(m_AMObject[i]->GetModelID()), false);
		
			m_AMObject[i]->Draw();
		
		}
	}

	//�@====================[�@�}�V�����I������Ă���@]
	if (m_selectNumber != -1)
	{
		//�@�@|=>�@�}�V���̖��@�w�`�揈��
		m_magicCircle->CreateWorld();
		m_magicCircle->Render(m_AMObject[m_selectNumber]->GetModelID());
	}

	
	//�@====================[�@�ۉe�̕`�揈���@]
	m_dorpShadow->CreateWorld();
	m_dorpShadow->Render();

	//�@====================[�@�p�[�e�B�N���̕`�揈���@]
	m_particle_hit		->Render();
	m_particle_Gurd		->Render();
	m_particle_Mining	->Render();
	m_particle_Recovery	->Render();
	m_particle_Bullet	->Render();

	//�@====================[�@�o���b�g�̕`�揈���@]
	for (std::list<std::unique_ptr<Bullet>>::iterator it = m_bullets.begin(); it != m_bullets.end(); it++)
	{
		it->get()->Render(m_testBox.get());
	}

	//�@====================[�@���_�̖��@�w�`�揈���@]
	m_magicCircle_Field->Render(0);

}

void AlchemicalMachineManager::WriteDepath()
{
	//�@====================[�@�e�`��p�h���[�R�[���@]
	for (int i = 0; i < m_AMObject.size(); i++)
	{
		// ���݂��Ă��邩�`�F�b�N
		if (m_AMObject[i]->GetActive())
		{
			m_AMObject[i]->WriteDepathRender(m_AMFilter->HandOverAMModel(m_AMObject[i]->GetModelID()),
											 m_AMFilter->GetRingModel(m_AMObject[i]->GetModelID()));
		}
	}
}


void AlchemicalMachineManager::DrawUI()
{
	//�@====================[�@�}�V��UI�̎w�����UI�̕`��@]
	m_selectManager->Render();

	//�@====================[�@UI�̃r���{�[�h�`��@]
	for (int i = 0; i < m_AMObject.size(); i++)
	{
		// ���݂��Ȃ���΂���ȍ~�����݂��Ȃ����߁A�������I������
		if (!m_AMObject[i]->GetActive()) break;
		// �I��ԍ��ƈ�v���Ă���ꍇ�͓��h���[�R�[��������K�v�͂Ȃ��ׁA��΂�
		if (m_selectNumber == i) continue;

		// �}�E�X�̎��ӂɂ���}�V���̏��J�� 
		Circle mouseCircle = Circle(InputSupport::GetInstance().GetMousePosWolrd(),5.0f);

		// �\������ : �}�E�X�J�[�\���͈͓̔��@�o���������Ԃ�0����(UI���\������Ă���)
		// �\�����e : �}�V���̑ϋv�l
		if (PointerToCircle(mouseCircle, m_AMObject[i]->GetPos()) ||
			m_AMObject[i]->GetPopTextTime() > 0.0f)
		{
			//========  �J�n�@========//
			BillboardRenderUI_Start(i, SimpleMath::Vector3(0.0f, WORLD_UI_POSY, 0.0f));

			m_AMObject[i]->RenderHP();

			//========  �I���@========//
			BillboardRenderUI_End();

		}

		// �\������ : �}�V�����I��U����ԂɂȂ��Ă���
		if (m_AMObject[i]->GetClickPromptFlag())
		{
			//========  �J�n�@========//
			BillboardRenderUI_Start(i, CLICKPROMPT_POS);

			m_AMObject[i]->RenderClickPrompt();

			//========  �I���@========//
			BillboardRenderUI_End();
		}
	}

	//�@====================[�@�}�V��UI�Ɋ֘A����`��@]
	//�@�@|=>�@�B���{�^��UI
	//�@�@|=>�@�}�V���̖��O
	//�@�@|=>�@�K�v���\�[�X��
	m_selectManager->RenderUI(m_AMnums);

	//�@====================[�@UI�̕\���@]
	if (m_selectNumber != -1)
	{
		//========  �J�n�@========//
		BillboardRenderUI_Start(m_selectNumber, SimpleMath::Vector3(0.0f, WORLD_UI_POSY, 0.0f));

		m_AMObject[m_selectNumber]->RenderHP();
		//========  �I���@========//
		BillboardRenderUI_End();

		// �I���������f����ID��None�Ȃ�\�����Ȃ�
		if (m_AMObject[m_selectNumber]->GetModelID() == MACHINE_TYPE::NONE) return;

		m_AMObject[m_selectNumber]->RenderUI();
		m_AMObject[m_selectNumber]->SelectRenderUI_Common();

	}
}

void AlchemicalMachineManager::Finalize()
{

	//�@====================[�@�S�}�V���̏I�������@]
	for (int i = 0; i < m_AMObject.size(); i++)
	{
		m_AMObject[i]->Finalize();
		m_AMObject[i].reset();
	}

	m_AMObject.clear();
	m_AMObject.shrink_to_fit();

	//�@====================[�@�S�o���b�g�̏I�������@]
	for (std::list<std::unique_ptr<Bullet>>::iterator it = m_bullets.begin(); it != m_bullets.end(); it++)
	{
		it->get()->Finalize();
	}

	m_bullets.clear();

	//�@====================[�@UI�`��N���X�̏I�������@]
	m_selectManager->Finalize();
	m_selectManager.reset();

	m_AMFilter.reset();
	m_testBox.reset();

}

void AlchemicalMachineManager::BillboardRenderUI_End()
{

	ShareData& pSD = ShareData::GetInstance();
	pSD.GetSpriteBatch()->End();
}

void AlchemicalMachineManager::BillboardRenderUI_Start(int index, SimpleMath::Vector3 position)
{
	ShareData& pSD = ShareData::GetInstance();
	auto status = pSD.GetCommonStates();
	auto camera = ShareData::GetInstance().GetCamera();
	auto context = pSD.GetContext();

	//�@====================[�@�r���{�[�h�s�񐶐��@]
	//�@�@|=>�@�X�N���[�����W��Y�����{�|�t�Ȃ̂�-1��������
	SimpleMath::Matrix invertY = SimpleMath::Matrix::CreateScale(1.0f, -1.0f, 1.0f);

	//�@�@|=> �r���[�s��̉�]��ł������s����쐬����
	SimpleMath::Matrix invView = camera->GetViewMatrix().Invert();
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	//�@�@|=> �G�t�F�N�g�Ƀr���[�s��Ǝˉe�s���ݒ肷��
	m_effect->SetView(camera->GetViewMatrix());
	m_effect->SetProjection(camera->GetProjectionMatrix());


	//�@====================[�@UI�����[���h��Ԃɏo��]
	pSD.GetSpriteBatch()->Begin(SpriteSortMode_Deferred, status->NonPremultiplied(), nullptr, status->DepthNone(), status->CullCounterClockwise(), [=]
	{	
		// ���[���h�s��쐬
		SimpleMath::Matrix world =
			SimpleMath::Matrix::CreateScale(WORLD_UI_SIZE) *
			invertY *
			invView *
			SimpleMath::Matrix::CreateTranslation(m_AMObject[index]->GetPos() + position);

		// �G�t�F�N�g��K������
		m_effect->SetWorld(world);
		m_effect->Apply(context);

		// ���̓��C�A�E�g��ݒ肷��
		context->IASetInputLayout(m_inputLayout.Get());
	});

}

Model* AlchemicalMachineManager::GetSelectModel()
{
	return m_AMFilter->HandOverAMModel(m_selectManager->GetSelectMachineType());
}

void AlchemicalMachineManager::ReloadResource()
{

	auto pSJD = &ShareJsonData::GetInstance();
	Stage_Resource resource = pSJD->GetStageData().resource;

	//�@====================[�@�}�V����������ǉ��@]
	m_AMnums[MACHINE_TYPE::ATTACKER]	+= resource.attacker;
	m_AMnums[MACHINE_TYPE::DEFENSER]	+= resource.deffencer;
	m_AMnums[MACHINE_TYPE::UPPER]		+= resource.upper;
	m_AMnums[MACHINE_TYPE::RECOVERY]	+= resource.recovery;
	m_AMnums[MACHINE_TYPE::MINING]		+= resource.mining;

}

void AlchemicalMachineManager::Update_Particle()
{

	//�@====================[�@�p�[�e�B�N���Q�̍X�V�����@]
	m_particle_hit			->UpdateParticle();
	m_particle_Put			->UpdateParticle();
	m_particle_Gurd			->UpdateParticle();
	m_particle_Mining		->UpdateParticle();
	m_particle_Recovery		->UpdateParticle();
	m_particle_Bullet		->UpdateParticle();
}

void AlchemicalMachineManager::Update_Attacker(int index, EnemyManager* enemys)
{
	if (m_AMObject[index]->GetHP() <= 0) return;
	if (m_AMObject[index]->GetModelID() != MACHINE_TYPE::ATTACKER) return;


	AM_Attacker* attacker = dynamic_cast<AM_Attacker*>(m_AMObject[index].get());

	//�@====================[�@�o���b�g�̔��˃��N�G�X�g�@]
	if (attacker->BulletRequest(enemys->GetEnemyData()))
	{
		m_bullets.push_back(std::make_unique<Bullet>(attacker->GetBulletData()));
	}
}

void AlchemicalMachineManager::Update_Defenser(int index, EnemyManager* enemys)
{
	if (m_AMObject[index]->GetHP() <= 0) return;
	if (m_AMObject[index]->GetModelID() != MACHINE_TYPE::DEFENSER) return;

	AM_Defenser* defenser = dynamic_cast<AM_Defenser*>(m_AMObject[index].get());

	//�@====================[�@�G�l�~�[�Ƃ̏Փˎ��@]
	defenser->EnemyHit(enemys->GetEnemyData());

	//�@�@|=>�@��p�̃p�[�e�B�N�����o��
	m_particle_Gurd->Update(defenser->GetPos(), defenser->CounterAttack(), defenser->GetColor());

}

void AlchemicalMachineManager::Update_Mining(int index, FieldObjectManager* fieldManager, EnemyManager* enemys)
{
	if (m_AMObject[index]->GetHP() <= 0) return;
	if (m_AMObject[index]->GetModelID() != MACHINE_TYPE::MINING) return;

	AM_Mining* mining = dynamic_cast<AM_Mining*>(m_AMObject[index].get());

	//�@====================[�@�G�l�~�[�Ƃ̏Փˎ��@]
	mining->HitEnemy(enemys->GetEnemyData());

	//�@====================[�@�N���X�^�����\�[�X�̉���@]
	m_crystalPulsVal += mining->AllFieldObject(fieldManager);

	//�@�@|=>�@��p�̃p�[�e�B�N�����o��
	m_particle_Mining->Update(mining->GetPos(), !mining->GetCrystalFlag(),mining->GetColor());

}

void AlchemicalMachineManager::Update_Recovery(int index,EnemyManager* enemys)
{

	if (m_AMObject[index]->GetHP() <= 0) return;
	if (m_AMObject[index]->GetModelID() != MACHINE_TYPE::RECOVERY) return;

	AM_Recovery* recovery = dynamic_cast<AM_Recovery*>(m_AMObject[index].get());

	//�@====================[�@�G�l�~�[�Ƃ̏Փˎ��@]
	recovery->HitEnemy(enemys->GetEnemyData());

	//�@====================[�@�����ԂȂ�΃p�[�e�B�N�����o���@]
	m_particle_Recovery->OnShot(recovery->GetPos(), m_mpPulsTimer >= MPPLUSTIME && !m_rotationStop, recovery->GetColor());
}

void AlchemicalMachineManager::Update_Upper(int index,EnemyManager* enemyManager)
{

	if (m_AMObject[index]->GetHP() <= 0) return;
	if (m_AMObject[index]->GetModelID() != MACHINE_TYPE::UPPER) return;

	AM_Upper* upper = dynamic_cast<AM_Upper*>(m_AMObject[index].get());

	//�@====================[�@�G�l�~�[�Ƃ̏Փˎ��@]
	upper->HitEnemy(enemyManager->GetEnemyData());

	//�@====================[�@�}�V���̔z���n���@]
	upper->MachinePowerUP(m_AMObject);

}

void AlchemicalMachineManager::MovingMachine(int number)
{
	//�@====================[�@�������^�[���@]
	//�@�@|=>�@��]����~���Ă���
	if (m_rotationStop) return;

	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	//�@====================[�@��]���x�擾�@]
	int rotateSpeed = (int)ShareJsonData::GetInstance().GetGameParameter().rotateSpeed;

	//�@====================[�@���_�𒆐S�ɉ�]�ړ��@]
	SimpleMath::Matrix matrix = SimpleMath::Matrix::Identity;
	matrix *= SimpleMath::Matrix::CreateRotationY(XMConvertToRadians(rotateSpeed * deltaTime));
	//�@�@|=>  ��]��̍��W���}�V���ɑ��
	m_AMObject[number]->SetPos(SimpleMath::Vector3::Transform(m_AMObject[number]->GetPos(), matrix));

}

// Lv�ɉ����Ēu����ꏊ��������ׁA�ݒ������
void AlchemicalMachineManager::CreateAMMachine()
{
	int counter = 0;

	//�@====================[�@�e�̔z������Z�b�g����@]
	m_dorpShadow->DeleteShadow();

	int circle_max_line = ShareJsonData::GetInstance().GetGameParameter().baseLV_MAX;

	//�@====================[�@�z�u�ӏ������߂�@]
	for (int i = 1; i < circle_max_line; i++)
	{
		for (int j = 0; j < CIRCLE_MAX_MIN * i; j++)
		{

			// None�}�V����ǉ�
			m_AMObject.push_back(m_AMFilter->HandOverAMClass(MACHINE_TYPE::NONE));

			// ����������
			m_AMObject[counter]->Initialize();

			// ���݂��郉�C������
			m_AMObject[counter]->SetLine(i);
			m_AMObject[counter]->SummonAM(SetVelocityCircle(j, CIRCLE_MAX_MIN * i, i * CIRCLE_LINE_DISTANCE));
			m_AMObject[counter]->SetActive(false);

			m_dorpShadow->CreateShadow(m_AMObject[counter]->GetData().pos);

			counter++;

		}
	}

}

void AlchemicalMachineManager::LvToObjectActives(int lineNumber)
{
	for (int i = 0; i < m_AMObject.size(); i++)
	{
		if (m_AMObject[i]->GetModelID() != MACHINE_TYPE::NONE) continue;

		if (m_AMObject[i]->GetLine() <= lineNumber)
		{
			m_AMObject[i]->SetActive(true);
		}
		else
		{
			m_AMObject[i]->SetActive(false);
		}
	}
}

void AlchemicalMachineManager::SpawnAMMachine(bool leftButtom)
{

	//�@====================[�@�}�V���̏��������@]
	//�@�@|=>�@ �I���{�b�N�XUI�ɐG��Ă��Ȃ�
	//�@�@|=>�@ �ΏۃI�u�W�F�N�g�ɐG��Ă���
	//�@�@|=>�@ ����UI�ɐG��Ă��Ȃ�
	//�@�@|=>�@ ���{�^���𗣂��ƃI�u�W�F�N�g�����ւ���
	if (leftButtom)
	{
		// MachineType::None��I�����Ă���ꍇ�Ɍ��菈����ʂ�
		if (m_AMObject[m_selectNumber]->GetModelID() != MACHINE_TYPE::NONE) return;

		// �����ł���I�u�W�F�N�g�̐�������Ȃ��ꍇ�͏������Ȃ�
		if (m_AMnums[m_selectManager->GetSelectMachineType()] <= 0) return;

		// �ʒu�����擾
		SimpleMath::Vector3 savePos = m_AMObject[m_selectNumber]->GetData().pos;

		// ���C�������擾
		int saveLine = m_AMObject[m_selectNumber]->GetLine();

		// �{�擾
		m_AMObject[m_selectNumber] = m_AMFilter->HandOverAMClass(m_selectManager->GetSelectMachineType());

		// ������
		m_AMObject[m_selectNumber]->Initialize();

		// None�ƑΏۂ̃I�u�W�F�N�g�����ւ���
		m_AMObject[m_selectNumber]->SummonAM(savePos);

		// ���C�����������p��
		m_AMObject[m_selectNumber]->SetLine(saveLine);

		// ���������I�u�W�F�N�g�ۗ̕L��������炷
		m_AMnums[m_selectManager->GetSelectMachineType()]--;
		
		// ���������}�V����ID���擾
		m_spawnMachine = m_AMObject[m_selectNumber]->GetModelID();

		// �����p�̃p�[�e�B�N�����o��������
		m_particle_Put->OnShot(m_AMObject[m_selectNumber]->GetPos(),true, m_AMObject[m_selectNumber]->GetColor());
		m_particle_Put->OnShot(m_AMObject[m_selectNumber]->GetPos(), true, SimpleMath::Color(Colors::Cyan));

		// �����p�̉�����炷
		SoundData::GetInstance().PlaySE(XACT_WAVEBANK_SES_WATERMACHINEATTACK);
	}
}

void AlchemicalMachineManager::Dismantling(int index)
{

	// �ʒu�����擾
	SimpleMath::Vector3 savePos = m_AMObject[index]->GetData().pos;

	// ���C�������擾
	int saveLine		= m_AMObject[index]->GetLine();

	// ���S�p�̃p�[�e�B�N�����o��������
	m_particle_Put		->OnShot(savePos, true,	SimpleMath::Color(Colors::Black));
	m_particle_Put		->OnShot(savePos, true, SimpleMath::Color(Colors::IndianRed));

	// �{�擾
	m_AMObject[index]	= m_AMFilter->HandOverAMClass(MACHINE_TYPE::NONE);

	// ������
	m_AMObject[index]	->Initialize();

	// None�ƑΏۂ̃I�u�W�F�N�g�����ւ���
	m_AMObject[index]	->SummonAM(savePos);

	// ���C�����������p��
	m_AMObject[index]	->SetLine(saveLine);

	// �j��p�̉�����炷
	SoundData::GetInstance().PlaySE(XACT_WAVEBANK_SES_FIREMACHINEATTACK);

}

void AlchemicalMachineManager::JsonLoadResources()
{
	auto pSJD = &ShareJsonData::GetInstance();

	Stage_Resource resource = pSJD->GetStageData().resource;

	m_AMnums[MACHINE_TYPE::ATTACKER]	= resource.attacker;
	m_AMnums[MACHINE_TYPE::DEFENSER]	= resource.deffencer;
	m_AMnums[MACHINE_TYPE::UPPER]		= resource.upper;
	m_AMnums[MACHINE_TYPE::RECOVERY]	= resource.recovery;
	m_AMnums[MACHINE_TYPE::MINING]		= resource.mining;

	for (int i = 0; i < pSJD->GetStageData().machine.size(); i++)
	{
		// �ʒu�����擾
		SimpleMath::Vector3 savePos = m_AMObject[i]->GetData().pos;

		// ���C�������擾
		int saveLine = m_AMObject[i]->GetLine();

		// �{�擾
		m_AMObject[i] = m_AMFilter->HandOverAMClass(pSJD->GetStageData().machine[i].type);

		// ������
		m_AMObject[i]->Initialize();

		// �����ݒ�
		m_AMObject[i]->SetElement(pSJD->GetStageData().machine[i].element);
		m_AMObject[i]->SetColor(ChangeData::ChangeColor(pSJD->GetStageData().machine[i].element));

		// �����ݒ�
		m_AMObject[i]->SetLv(pSJD->GetStageData().machine[i].lv);

		// None�ƑΏۂ̃I�u�W�F�N�g�����ւ���
		m_AMObject[i]->SummonAM(savePos);

		// ���C�����������p��
		m_AMObject[i]->SetLine(saveLine);

	}
}
