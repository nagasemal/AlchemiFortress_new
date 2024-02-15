#include "pch.h"
#include "UIKeyControl.h"
#include "NecromaLib/Singleton/InputSupport.h"
#include "Scenes/Commons/SelectionUI.h"

// �L�[�{�[�h�őI���\�ɂȂ�܂ł̎���
#define SELECT_TIME 20.0f

#define MOVE_VALUE 100.0f

UIKeyControl::UIKeyControl():
	m_maxLows{0},
	m_prevMousePos(),
	m_keyContorlFlag(false),
	m_index(-1),
	m_prevIndex(0)
{
}

UIKeyControl::~UIKeyControl()
{
}

//void UIKeyControl::Update()
//{
//	InputSupport& pIS = InputSupport::GetInstance();
//	m_nowCol -= pIS.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Up);
//	m_nowCol += pIS.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Down);
//
//	m_nowLow -= pIS.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Left);
//	m_nowLow += pIS.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Right);
//
//	m_nowCol = std::min(std::max(m_nowCol, 0), m_maxCol);
//	m_nowLow = std::min(std::max(m_nowLow, 0), m_maxLows[m_nowCol]);
//
//	// �}�E�X�𓮂����Ă��Ȃ���΃L�[�{�[�h�����ɂ���
//	if (m_prevMousePos != pIS.GetMousePosScreen()) m_keyContorlFlag = false;
//
//	// �O�t���[���̃}�E�X�ʒu��ۑ�����
//	m_prevMousePos = pIS.GetMousePosScreen();
//
//	// �\���L�[�������ꂽ��L�[�{�[�h���샂�[�h�ƂȂ�
//	ArrowKeyPush();
//
//	if (!m_keyContorlFlag) return;
//
//	// �s�Ɨ�ɑΉ�����UI�̑I�����/������Ԃ�ς��܂�
//	for (auto& selectionUI : m_selectionUIs)
//	{
//		
//		// �G��Ȃ���ԂȂ�Ώ������΂�
//		if (!selectionUI.ui->GetActiveFlag()) continue;
//
//		selectionUI.ui->Update();
//
//		if (selectionUI.col == m_nowCol && selectionUI.low == m_nowLow)
//		{
//			selectionUI.ui->SetHitMouseFlag(true);
//			selectionUI.ui->SetSelectFlag(true);
//
//			if (pIS.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Enter))
//			{
//				selectionUI.ui->SetKeySelectFlag(true);
//			}
//
//		}
//
//	}
//
//}

void UIKeyControl::Update(SimpleMath::Vector2 moveNum)
{
	InputSupport& pINP = InputSupport::GetInstance();
	m_nowUIPos.y -= pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Up)		* moveNum.y;
	m_nowUIPos.y += pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Down)		* moveNum.y;

	m_nowUIPos.x -= pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Left)		* moveNum.x;
	m_nowUIPos.x += pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Right)	* moveNum.x;

	// �}�E�X�𓮂����Ă��Ȃ���΃L�[�{�[�h�����ɂ���
	if (m_prevMousePos != pINP.GetMousePosScreen()) m_keyContorlFlag = false;

	// �O�t���[���̃}�E�X�ʒu��ۑ�����
	m_prevMousePos = pINP.GetMousePosScreen();

	// �\���L�[�������ꂽ��L�[�{�[�h���샂�[�h�ƂȂ�
	ArrowKeyPush();
	if (!m_keyContorlFlag) return;

	float dist_min = 1000000.0f;

	for (int i = 0; i < m_selectionUIs.size(); i++)
	{
		// ���ݒn�_����ł��߂�UI��T��
		SimpleMath::Vector2 distPos = m_selectionUIs[i]->GetPos() - m_nowUIPos;
		float dist = distPos.x * distPos.x + distPos.y * distPos.y;

		if (dist < dist_min)
		{
			dist_min = dist;
			m_index = i;
		}
	}

	m_prevIndex = m_index;

	m_nowUIPos = m_selectionUIs[m_prevIndex]->GetPos();
	m_selectionUIs[m_prevIndex]->SetHitMouseFlag(true);

	if (pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Enter))
	{
		m_selectionUIs[m_prevIndex]->SetKeySelectFlag(true);
	}

	m_index = -1;

}

void UIKeyControl::AddUI(SelectionUI* ui)
{
	m_selectionUIs.push_back(ui);
}

//void UIKeyControl::AddUI(SelectionUI* ui,int low, int col)
//{
//	UI_Data ui_data;
//
//	ui_data.low = low;
//	ui_data.col = col;
//	ui_data.ui = ui;
//
//	// �s��Max�l���X�V���� ����X�V����
//	if (m_maxCol < col)
//	{
//		m_maxCol = col;
//		m_maxLows.push_back(low);
//	}
//	if (m_maxLows[col] < low) m_maxLows[col] = low;
//
//	m_selectionUIs.push_back(ui_data);
//}

void UIKeyControl::DeleteUI(SelectionUI* ui)
{
	ui;
	for (int i = 0; i < m_selectionUIs.size(); i++)
	{
	}
}

bool UIKeyControl::ArrowKeyPush()
{
	if (!m_keyContorlFlag)
	{
		InputSupport& pINP = InputSupport::GetInstance();
		m_keyContorlFlag = pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Up)
						|| pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Down)
						|| pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Left)
						|| pINP.GetKeybordState().IsKeyPressed(DirectX::Keyboard::Right);
	}
	return m_keyContorlFlag;
}
