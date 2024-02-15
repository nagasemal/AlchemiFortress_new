#include "pch.h"
#include "ClearVeil.h"

#include "NecromaLib/GameData/UserInterfase.h"

#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/ShareData.h"

#define ANIMATION_SPEED_1 1.25f		// ���E����o�����開�̃A�j���[�V�����X�s�[�h
#define ANIMATION_SPEED_2 1.5f		// �㉺�Ɉړ����開�̃A�j���[�V�����X�s�[�h
#define ANIMATION_SPEED_3 2.0f		// Wave����\��,�P�ނ�����A�j���[�V�����X�s�[�h

#define VEIL_SIZE_Y 32.0f			// �㉺���猻��開�̃T�C�Y
#define WAVE_SIZE 0.06f				// Wave���\���摜�̃T�C�Y
#define WAVE_UP_VAL 10.0f			// ���o�I����,����֓P�ނ���ۂ̑傫��

#define WAVE_ANIM_MIDDLE 0.2f

ClearVeil::ClearVeil(int waveNum)
{
	//�@====================[�@�f�o�C�X�Ɖ�ʃT�C�Y�̊m�ہ@]
	auto device = ShareData::GetInstance().GetDeviceResources();
	float width = static_cast<float>(device->GetOutputSize().right);
	float height = static_cast<float>(device->GetOutputSize().bottom);

	//�@====================[�@Wave�N���A�����o�N���X�̐ݒ�@]
	//�@�@|=>�@�㕔
	m_nextWave_Top = std::make_unique<UserInterface>();
	m_nextWave_Top->Create(device,
		L"Resources/Textures/WaveClear_Top.png",
		SimpleMath::Vector2(width / 2.0f, 0.0f),
		SimpleMath::Vector2(1.0f, 0.5f),
		UserInterface::ANCHOR::MIDDLE_CENTER);
	m_nextWave_Top->SetColor(Colors::Aqua);
	//�@�@|=>�@����
	m_nextWave_Bottom = std::make_unique<UserInterface>();
	m_nextWave_Bottom->Create(device,
		L"Resources/Textures/WaveClear_Bottom.png",
		SimpleMath::Vector2(width / 2.0f, height),
		SimpleMath::Vector2(1.0f, 0.5f),
		UserInterface::ANCHOR::MIDDLE_CENTER);
	m_nextWave_Bottom->SetColor(Colors::Aqua);
	m_nextWave_Bottom->SetSharpenW(true);

	// �A�j���[�V�����f�[�^�̐ݒ�
	m_waveAnimation_first	= 0.0f;
	m_waveAnimation_second	= 0.0f;
	for (int i = 0; i < waveNum; i++)
	{
		AnimationData animData = 0.0f;
		animData.middle = WAVE_ANIM_MIDDLE;
		m_waveAnimation_waves.push_back(animData);
	}


}

ClearVeil::~ClearVeil()
{
}

void ClearVeil::Update(bool startFlag)
{
	//�@====================[�@�f�o�C�X�Ɖ�ʃT�C�Y�̊m�ہ@]
	auto device = ShareData::GetInstance().GetDeviceResources();
	float width = static_cast<float>(device->GetOutputSize().right);
	float height = static_cast<float>(device->GetOutputSize().bottom);

	//�@====================[�@�A�j���[�V����.1�@]
	//�@�@|=>�@�㉺�̃��x����\��
	if (startFlag)
	{
		m_waveAnimation_first += DeltaTime::GetInstance().GetDeltaTime() * ANIMATION_SPEED_1;

		m_nextWave_Top->SetSharpenW(true);
		m_nextWave_Bottom->SetSharpenW(false);

	}
	else
	{
		m_waveAnimation_first -= DeltaTime::GetInstance().GetDeltaTime() * ANIMATION_SPEED_1;

		m_nextWave_Top->SetSharpenW(false);
		m_nextWave_Bottom->SetSharpenW(true);
	}

	//�@====================[�@�A�j���[�V����.2�@]
	//�@�@|=>�@�\�������𑽂�������
	if (m_waveAnimation_first.MaxCheck() && !m_waveAnimation_second.MaxCheck())
	{
		m_waveAnimation_second += DeltaTime::GetInstance().GetDeltaTime() * ANIMATION_SPEED_2;
	}
	//�@�@|=>�@���Z�b�g
	if (m_waveAnimation_first.MinCheck())
	{
		m_waveAnimation_second = 0.0f;

		for (int i = 0; i < m_waveAnimation_waves.size();i++)
		{
			m_waveAnimation_waves[i] -= DeltaTime::GetInstance().GetDeltaTime() * ANIMATION_SPEED_3;
		}
	}

	//�@====================[�@�A�j���[�V����.3�@]
	//�@�@|=>�@Wave�������o�I�ɕ\��
	if (m_waveAnimation_second.MiddleFlag())
	{
		m_waveAnimation_waves[0] += DeltaTime::GetInstance().GetDeltaTime() * ANIMATION_SPEED_3;

		//�@�@|=>�@�O�̗v�f�̎��ԕϐ��������̒l���߂�����X�V���n�߂�
		for (int i = 1; i < m_waveAnimation_waves.size();)
		{
			if (m_waveAnimation_waves[i - 1].MiddleFlag())
			{
				m_waveAnimation_waves[i] += DeltaTime::GetInstance().GetDeltaTime() * ANIMATION_SPEED_3;
			}

			i++;
		}
	}

	//�@====================[�@�\��������ݒ�@]
	m_nextWave_Top		->SetRenderRatio(Easing::EaseInOutCirc(0.0f, 1.0f, m_waveAnimation_first));
	m_nextWave_Bottom	->SetRenderRatio(Easing::EaseInOutCirc(0.0f, 1.0f, m_waveAnimation_first));

	//�@====================[�@�\���ʒu��ݒ�@]
	m_nextWave_Top		->SetPosition(SimpleMath::Vector2(width / 2.0f,			 Easing::EaseOutCubic(0.0f, VEIL_SIZE_Y, m_waveAnimation_second)));
	m_nextWave_Bottom	->SetPosition(SimpleMath::Vector2(width / 2.0f, height - Easing::EaseOutCubic(0.0f, VEIL_SIZE_Y, m_waveAnimation_second)));

}

void ClearVeil::Render(int nowWave)
{
	ShareData& pSD = ShareData::GetInstance();
	SpriteLoder& pSL = SpriteLoder::GetInstance();

	//�@====================[�@�f�o�C�X�Ɖ�ʃT�C�Y�̊m�ہ@]
	auto device = ShareData::GetInstance().GetDeviceResources();
	float width = static_cast<float>(device->GetOutputSize().right);
	float height = static_cast<float>(device->GetOutputSize().bottom);

	//�@====================[�@�`��@]
	m_nextWave_Top->Render();
	m_nextWave_Bottom->Render();

	pSD.GetSpriteBatch()->Begin(SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	//�@====================[�@�c��Wave����`��@]
	for (int i = 0; i < m_waveAnimation_waves.size(); i++)
	{
		SpriteLoder::TextureData texData = pSL.GetMachineMagicCircleTexture(0);

		// �������֋ϓ��ɕ��ׂ�
		float posX_shift = ((float)(m_waveAnimation_waves.size() - 1) / 2.0f - (float)i) * ((float)texData.width * WAVE_SIZE);

		// ���o�I�����ɏ�ɓo��ϐ�
		float posY_shift = Easing::EaseInOutCirc(0.0f, WAVE_UP_VAL, m_waveAnimation_first);

		// �F���
		SimpleMath::Color		color = SimpleMath::Color(Colors::White);

		// �N���A����Wave�Ȃ�ΐF��h��
		if (nowWave - 1 >= i)	color = SimpleMath::Color(Colors::Aqua);

		color.A(Easing::EaseInOutSine(0.0f, 1.0f, m_waveAnimation_waves[i]));

		RECT rect = { 0,0,texData.width,texData.height };
		pSD.GetSpriteBatch()->Draw(texData.tex.Get(),
			SimpleMath::Vector2(width / 2.0f - posX_shift, height / 2.0f + posY_shift), &rect,
			color,
			1.0f - m_waveAnimation_waves[i],
			SimpleMath::Vector2(texData.width / 2.0f, texData.height / 2.0f), WAVE_SIZE);
	}

	pSD.GetSpriteBatch()->End();
}

bool ClearVeil::NextWave()
{
	int waveSize = (int)m_waveAnimation_waves.size() - 1;

	return m_waveAnimation_second.MaxCheck() && m_waveAnimation_first.MaxCheck() && m_waveAnimation_waves[waveSize].MaxCheck();
}