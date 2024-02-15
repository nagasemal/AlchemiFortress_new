#include "pch.h"
#include "SelectionUI.h"

#include "NecromaLib/GameData/UserInterfase.h"
#include "NecromaLib/Singleton/DeltaTime.h"

#include "NecromaLib/Singleton/InputSupport.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/SoundData.h"

#include <random>

// �摜�T�C�Y�̏c���̑傫��
#define SPRITE_RAGE 64

// ���s���U���̑傫��
#define SHAKE_RAGE 2.0f

SelectionUI::SelectionUI() :
	m_selectFlag(),
	m_hitMouseFlag(),
	m_keySelectFlag(),
	m_worldInfluenceFlag(true),
	m_layer(),
	m_activeFlag(true),
	m_rect{ 0,0,SPRITE_RAGE,SPRITE_RAGE },
	m_vibrationTime(),
	m_holdTime(),
	m_keys()
{
}

SelectionUI::~SelectionUI()
{
}

void SelectionUI::Initialize()
{
	m_boxColor = Colors::White;
}

void SelectionUI::Finalize()
{
}

bool SelectionUI::HitMouse(bool layerCheck)
{
	InputSupport& pINP = InputSupport::GetInstance();

	// ����(�����Ȃ�)�ꍇ��false��Ԃ�
	if (m_boxColor.A() < 0.0f)
	{
		m_hitMouseFlag = false;
		return false;
	}

	// ������擾����
	m_hitMouseFlag = HitObject_RageSet(pINP.GetMousePosScreen(), 
									   static_cast<float>(m_rect.right),
									   static_cast<float>(m_rect.bottom),
									   m_data.rage) || m_keySelectFlag;

	m_keySelectFlag = false;

	for (auto& key : m_keys)
	{
		if (!m_keySelectFlag)
		{
			m_keySelectFlag = pINP.GetKeybordState().IsKeyPressed(key);
		}
	}

	// �}�E�X�����[���h��Ԃɉe�����y�ڂ��Ȃ��l�ɂ���
	if (m_hitMouseFlag && m_worldInfluenceFlag) pINP.HitUI();

	// �k�킹��
	if (m_vibrationTime > 0.0f)
	{
		std::uniform_real_distribution<> dist_enemyType(-m_vibrationTime, m_vibrationTime);
		std::random_device rd;
		float vibrationRand = static_cast<float>(dist_enemyType(rd)) * SHAKE_RAGE;

		m_vibrationTime -= DeltaTime::GetInstance().GetNomalDeltaTime();

		m_data.pos = SimpleMath::Vector2(m_saveData.pos.x + sinf(vibrationRand) , m_saveData.pos.y + cosf(vibrationRand));

	}
	else
	{
		m_vibrationTime = 0.0f;
		m_data.pos = m_saveData.pos;
	}


	// �G��Ă���Ԃ̓��[���h��ԍ��W�ɉe�����y�ڂ��Ȃ��悤�ɂ���
	// layer�`�F�b�N��ԂȂ�Βǉ��Ń`�F�b�N���s��
	if (m_hitMouseFlag && layerCheck)
	{
		// ���g�̕����傫����΃��C���[�����X�V���� �����łȂ���Ώ�����ʂ��Ȃ�
		if (m_layer >= (int)pINP.GetLayer())	pINP.SetLayer(m_layer);
		else return m_hitMouseFlag = false;

	}

	return m_hitMouseFlag;
}

bool SelectionUI::ClickMouse()
{
	InputSupport& pINP = InputSupport::GetInstance();

	if ((m_hitMouseFlag && pINP.LeftButton_Press()) || m_keySelectFlag)
	{
		// �A�N�e�B�u��
		if (m_activeFlag)
		{
			SoundData::GetInstance().PlaySystemSE_Auto(XACT_WAVEBANK_SYSTEMSE_BUTTOMPUSH);
			return true;
		}
		else
		{
			SoundData::GetInstance().PlaySystemSE_Auto(XACT_WAVEBANK_SYSTEMSE_POPTEXT);

			m_vibrationTime = 1.0f;

			return false;
		}
	}

	return false;
}

bool SelectionUI::SelectionMouse()
{
	//�@====================[�@UI�������ꂽ�ۂ�ON�EOFF�����@]
	//�@�@|=>�@ON
	if (ClickMouse() && !m_selectFlag)
	{
		m_selectFlag = true;
		return m_selectFlag;
	}
	//�@�@|=>�@OFF
	if (ClickMouse() && m_selectFlag)
	{
		m_selectFlag = false;
	}

	return m_selectFlag;
}

bool SelectionUI::HoldMouse()
{
	InputSupport& pINP = InputSupport::GetInstance();
	bool leftFlag = pINP.GetMouseState().leftButton;

	if (m_hitMouseFlag && leftFlag) m_holdTime += DeltaTime::GetInstance().GetDeltaTime();
	else m_holdTime = 0.0f;

	return m_holdTime >= 1.0f;
}

bool SelectionUI::ExitMouse()
{
	InputSupport& pINP = InputSupport::GetInstance();
	bool exitFlag = false;

	if (m_hitMouseFlag)
	{
		exitFlag = !HitObject_RageSet(pINP.GetMousePosScreen(), SPRITE_RAGE, SPRITE_RAGE, m_data.rage);
	}

	return exitFlag;
}


