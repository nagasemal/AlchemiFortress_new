#include "pch.h"
#include "InputSupport.h"
#include "NecromaLib/GameData/ScreenToWorld.h"

#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/SpriteLoder.h"

InputSupport* InputSupport::instance = nullptr;

InputSupport::InputSupport() :
	m_WorldScreenMouse(),
	m_nowLayer(),
	m_hitUIFlag(),
	m_keyDisplayMode()
{
}

void InputSupport::Create()
{
	if (instance == nullptr)
	{
		instance = new InputSupport;
	}
}

void InputSupport::Destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputSupport::Update()
{
	ShareData& pSD = ShareData::GetInstance();
	DX::DeviceResources* pDR = pSD.GetDeviceResources();

	//�@====================[�@UI�ɐG��Ă���@]
	if (m_hitUIFlag)
	{
		// �G�������̂��Ȃ��ꏊ�ɒu��
		m_WorldScreenMouse = SimpleMath::Vector3(FLT_MAX,0.0f,0.0f);
	}
	//�@====================[�@UI�ɐG��Ă��Ȃ��@]
	else
	{
		// ���[���h��ԍ��W�ɕϊ�
		m_WorldScreenMouse = CalcScreenToXZN(m_mouseTracker.GetLastState().x,
			m_mouseTracker.GetLastState().y,
			pDR->GetOutputSize().right,
			pDR->GetOutputSize().bottom,
			pSD.GetView(), pSD.GetProjection());
	}

	//�@====================[�@UI�ɐG�����悤�ɂ���@]
	m_hitUIFlag = false;

	//�@====================[�@���݂̃��C���[�ԍ���߂��@]
	m_nowLayer = 0;

	//�@====================[�@�L�[�\����L��/�����ɂ���@]
	if (GetKeybordState().IsKeyReleased(Keyboard::Tab))
	{
		m_keyDisplayMode = !m_keyDisplayMode;
	}

}

void InputSupport::SetLayer(int layer)
{
	m_nowLayer = layer;
}

bool InputSupport::LeftButton_Press()
{
	return m_mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED;
}

bool InputSupport::LeftButton_Release()
{
	return m_mouseTracker.leftButton == Mouse::ButtonStateTracker::RELEASED;
}

bool InputSupport::LeftButton_Held()
{
	return m_mouseTracker.leftButton == Mouse::ButtonStateTracker::HELD;
}

bool InputSupport::RightButton_Press()
{
	return m_mouseTracker.rightButton == Mouse::ButtonStateTracker::PRESSED;
}

bool InputSupport::RightButton_Release()
{
	return m_mouseTracker.rightButton == Mouse::ButtonStateTracker::RELEASED;
}

bool InputSupport::RightButton_Held()
{
	return m_mouseTracker.rightButton == Mouse::ButtonStateTracker::HELD;
}

bool InputSupport::MiddleButton_Press()
{
	return m_mouseTracker.middleButton == Mouse::ButtonStateTracker::PRESSED;
}

bool InputSupport::MiddleButton_Release()
{
	return m_mouseTracker.middleButton == Mouse::ButtonStateTracker::RELEASED;
}

bool InputSupport::MiddleButton_Held()
{
	return m_mouseTracker.middleButton == Mouse::ButtonStateTracker::HELD;
}

bool InputSupport::GetKeyDisplayMode()
{
	return m_keyDisplayMode;
}

SimpleMath::Vector3 InputSupport::GetMousePosWolrd()
{
	return m_WorldScreenMouse;
}

SimpleMath::Vector2 InputSupport::GetMousePosScreen()
{
	return {(float)m_mouseTracker.GetLastState().x, (float)m_mouseTracker.GetLastState().y };
}
