#include "pch.h"
#include "AM_None.h"

#include "NecromaLib/Singleton/ModelShader.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/DeltaTime.h"

AM_None::AM_None()
{
}

AM_None::~AM_None()
{

}

void AM_None::Initialize()
{
	m_machineID = MACHINE_TYPE::NONE;
	m_objectName = "None";
	m_lv = 1;

}

void AM_None::Update()
{
	m_color = Colors::Black;

	// �I�����[�h���A�F��ς���
	if (m_selectModeFlag)
	{
		m_selectModeTime += DeltaTime::GetInstance().GetNomalDeltaTime() * 2.0f;

		float transitionVal = sinf(m_selectModeTime);

		m_color = SimpleMath::Color(transitionVal, transitionVal, transitionVal / 1.25f, 1.0f);
	}
	else
	{
		m_selectModeTime = 0;
	}

	// �}�E�X���G��Ă���ԁA�F��ς���
	if (m_hitMouseFlag)
	{
		m_color = Colors::White;
	}

	// ���x���̃��Z�b�g
	m_lv = 1;
}

void AM_None::SelectUpdate()
{
}

void AM_None::Draw()
{
	if (m_selectModeFlag) LightLine();
}

void AM_None::Finalize()
{
}

void AM_None::RenderUI()
{
}

void AM_None::LightLine()
{
}
