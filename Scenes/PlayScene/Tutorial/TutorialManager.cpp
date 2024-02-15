#include "pch.h"
#include "TutorialManager.h"
#include <WICTextureLoader.h>

#include "NecromaLib/GameData/SpriteCutter.h"
#include "NecromaLib/GameData/Easing.h"

#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/Singleton/InputSupport.h"

#include "Scenes/Commons/DrawArrow.h"
#include "Scenes/Commons/DrawBox.h"

#include "Scenes/PlayScene/PlayScene.h"
#include "Scenes/PlayScene/UI/SelectionBox.h"

#include "Scenes/PlayScene/Tutorial/CommandPattern/TutorialCommands.h"
#include "Scenes/PlayScene/Tutorial/CommandPattern/Commander_Tutorial.h"

#include "Scenes/PlayScene/Shadow/Particle.h"
#include "NecromaLib/GameData/Particle_2D.h"

#define TEXTPOS SimpleMath::Vector2(300,500)
#define ARROWPOS SimpleMath::Vector2(200,-15)

#define TEX_W 500.0f
#define TEX_H 200.0f

#define OFFSET_Y 10 

TutorialManager::TutorialManager(PlayScene* pPlayScene)
{
	m_texHeight = m_texWidth = 0;
	m_nowCutting = m_maxCutting = 0;
	m_PlayScene = pPlayScene;

	m_transitionTime = 0.0f;

	m_tutorialNum = 0;

	m_machineSelectParticle = std::make_unique<Particle>(Particle::MACHINE_SPAWN);
	m_machineSelectParticle->Initialize();
	m_machineSelectParticle->SetParticleSpawnTime(1.0f);

	m_leftArrow = std::make_unique<DrawArrow>(SimpleMath::Vector2(TEXTPOS.x - ARROWPOS.x, TEXTPOS.y - ARROWPOS.y),	SimpleMath::Vector2(0.5, 0.5), 4);
	m_leftArrow->Initialize();

	m_rightArrow = std::make_unique<DrawArrow>(SimpleMath::Vector2(TEXTPOS.x + ARROWPOS.x, TEXTPOS.y - ARROWPOS.y), SimpleMath::Vector2(0.5, 0.5), 2);
	m_rightArrow->Initialize();

	m_tutorialCommander = std::make_unique<TutorialCommander>();

	m_displayBox = std::make_unique<DrawBox>(SimpleMath::Vector2(),SimpleMath::Vector2(50.0f,50.0f),5.25f);
	m_displayBox->Initialize();
	m_displayBox->SetColor(SimpleMath::Color(1.0f,0.0f,0.0f,1.0f));

	m_selectNextWaveBox = std::make_unique<SelectionBox>(SimpleMath::Vector2(TEXTPOS.x + ARROWPOS.x, TEXTPOS.y - ARROWPOS.y), SimpleMath::Vector2(1.0f, 1.0f));
	m_selectNextWaveBox->Initialize();

	// 2D�p�[�e�B�N���̐���
	m_arrowParticle		= std::make_unique<Particle_2D>();
	m_alchemiParticle	= std::make_unique<Particle_2D>();

	auto device = ShareData::GetInstance().GetDevice();

	// �e�N�X�`��(�e�L�X�g�{�b�N�X)�̃��[�h
	DirectX::CreateWICTextureFromFile(
		device,
		L"Resources/Textures/TutorialText/TextBox.png",
		nullptr,
		m_tutorialTextBox.ReleaseAndGetAddressOf()
	);

	m_selectNextWave = false;

}

TutorialManager::~TutorialManager()
{
	m_tutorialCommander->Reset();
}

void TutorialManager::Update(bool clearMission)
{
	clearMission;

	// �X�e�[�W�ԍ���1�ӊO�Ȃ�Ώ������s��Ȃ�
	if (DataManager::GetInstance()->GetStageNum() != 1) return;

	m_machineSelectParticle->UpdateParticle();

	// �A�N�e�B�u�łȂ�����(�`���؂�)
	m_displayBox->SetActiveFlag(false);
	// �G��Ă��Ȃ��Ƃ��A�j���[�V�����͍s��
	m_displayBox->SetAnimationFlag(true);
	m_tutorialCommander->Execute_One();

	m_transitionTime += DeltaTime::GetInstance().GetNomalDeltaTime();

	m_leftArrow		->HitMouse();
	m_leftArrow		->SetActiveFlag(m_nowCutting > 0);

	m_rightArrow	->HitMouse();
	m_rightArrow	->SetActiveFlag(m_nowCutting < m_maxCutting);

	m_arrowParticle		->UpdateParticle();
	m_alchemiParticle	->UpdateParticle();

	// �����������ꂽ�ۂ̏���
	if (m_leftArrow	->ClickMouse())
	{
		m_transitionTime = 0.0f;

		m_nowCutting--;
	}

	// �E���������ꂽ�ۂ̏���
	if (m_rightArrow->ClickMouse())
	{
		m_transitionTime = 0.0f;

		m_nowCutting++;
	}

}

// �`����s��
void TutorialManager::Render()
{
	// �X�e�[�W�ԍ���1�ӊO�Ȃ�Ώ������s��Ȃ�
	if (DataManager::GetInstance()->GetStageNum() != 1) return;

	auto& pSD	= ShareData::GetInstance();
	auto  pSB	= pSD.GetSpriteBatch();

	pSB->Begin(SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());
	{

		RECT rect = SpriteCutter((int)TEX_W, (int)TEX_H, 0, 0);

		// �e�L�X�g�{�b�N�X�`��
		pSB->Draw(m_tutorialTextBox.Get(),
			TEXTPOS,
			&rect, SimpleMath::Color(0.4f, 0.4f, 0.4f, 0.6f), 0.0f,
			SimpleMath::Vector2((float)m_texWidth / 2.0f, TEX_H), 0.8f);

		rect = SpriteCutter(m_texWidth, (int)TEX_H, 0, m_nowCutting);
		float transparent = Easing::EaseInOutSine(0.0f, 1.0f, m_transitionTime);

		// �����`��
		pSB->Draw(m_tutorialTextTex.Get(),
			SimpleMath::Vector2(TEXTPOS.x, TEXTPOS.y + OFFSET_Y - transparent * OFFSET_Y),
			&rect, SimpleMath::Color(1.0f, 1.0f, 1.0f, transparent), 0.0f,
			SimpleMath::Vector2((float)m_texWidth / 2.0f, TEX_H), 0.7f);
	}
	pSB->End();

	// ���`��
	if (m_leftArrow ->GetActiveFlag()) m_leftArrow	->Draw();
	if (m_rightArrow->GetActiveFlag()) m_rightArrow	->Draw();

	m_machineSelectParticle->Render();
}

void TutorialManager::Render_Layer2()
{
	// �X�e�[�W�ԍ���1�ȊO�Ȃ�Ώ������s��Ȃ�
	if (DataManager::GetInstance()->GetStageNum() != 1) return;

	m_alchemiParticle->Render();
	m_arrowParticle->Render();

	if (m_displayBox->GetActiveFlag()) m_displayBox->Draw();
}

void TutorialManager::ChangeWave(int wave)
{

	// �X�e�[�W�ԍ���1�ӊO�Ȃ�Ώ������s��Ȃ�
	if (DataManager::GetInstance()->GetStageNum() != 1) return;

	std::vector<Tutorial_Status> tutorials = ShareJsonData::GetInstance().GetStageData().tutorial;

	// �擪�̐��l��ǂݎ��
	m_tutorialNum = wave;

	// �`���[�g���A���̃e�L�X�g�𕪊�����
	m_nowCutting = 0;

	m_transitionFlag = true;
	m_transitionTime = 0.0f;

	auto& pSD = ShareData::GetInstance();

	// �t�@�C���p�X�𐶐�����
	std::wstring fileName = L"Resources/Textures/TutorialText/Tutorial_";

	std::wostringstream oss;

	oss << m_tutorialNum << L".png";

	fileName += oss.str();

	DirectX::CreateWICTextureFromFile(pSD.GetDevice(), fileName.c_str(), m_res.ReleaseAndGetAddressOf(), m_tutorialTextTex.ReleaseAndGetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	m_texWidth	= desc.Width;
	m_texHeight = desc.Height;

	m_maxCutting = m_texHeight / 400;

	m_tutorialCommander->Reset();

	// �R�}���_�[�Ƀ`���[�g���A���R�}���h��o�^����
	for (int type = 0; type < tutorials.size(); type++)
	{

		m_tutorialCommander->AddCommand(GenerateCommand(tutorials[type]),this);
	}
}

ICommand_Tutorial* TutorialManager::GenerateCommand(Tutorial_Status type)
{
	// �`���[�g���A���̃R�}���h�𐶐�����
	switch (type.type)
	{
	// �������Ȃ��R�}���h
	case TutorialCommander::NONE:

		return new Tutorial_None();

	// �}�V��UI�p�̃R�}���h
	case TutorialCommander::ATTACKER_UI:
	case TutorialCommander::DEFENSER_UI:
	case TutorialCommander::UPPER_UI:
	case TutorialCommander::RECOVERY_UI:
	case TutorialCommander::MINING_UI:

		return new Tutorial_MachineUI((MACHINE_TYPE)type.type, type.val);

	// 
	case TutorialCommander::ALCHEMI_UI:

		return new Tutorial_AlchemiUI((MACHINE_TYPE)type.val,1);

	case TutorialCommander::LR_BUTTON_LOCK:

		return new Tutorial_LockMachineUI((bool)type.val);

	case TutorialCommander::NONE_MACHINE_SELECT:

		return new Tutorial_NoneSelect(type.val);

	// �A�b�p�[�}�V���̓K�؂Ȕz�u�ӏ��������R�}���h
	case TutorialCommander::PROPHERAL_ATTACKER_MACHINE:

		return new Tutorial_UppperSelect(type.val);

	// �����_���G�l�~�[�̈ʒu�ɂ���R�}���h
	case TutorialCommander::ENEMY_ATTENTION:

		return new Tutorial_EnemySpawn((float)type.val);
	
	// �}�V����j�󂷂�R�}���h
	case TutorialCommander::BREAK_MACHINE:

		return new Tutorial_MachineBreak((MACHINE_TYPE)type.val);
	
	// �}�V�����C�U����R�}���h
	case TutorialCommander::REPAIR_MACHINE:

		return new Tutorial_MachineRepia((MACHINE_TYPE)type.val);

	case TutorialCommander::TEXT_ARROW:

		return new Tutorial_TextArrow((MACHINE_TYPE)type.val);

	case TutorialCommander::ALCHEMI_LOCK:

		return new Tutorial_LockAlchemi((bool)type.val);
	default:
		break;
	}

	return nullptr;
}