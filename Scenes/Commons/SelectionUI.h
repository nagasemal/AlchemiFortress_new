#pragma once

#include "NecromaLib/GameData/GameObject2D.h"

class DrawKey;

class SelectionUI : public GameObject2D
{
public:
	SelectionUI();
	~SelectionUI();
	// ������
	void Initialize()			override;
	// �I������
	void Finalize()				override;

	// �}�E�X���G�ꂽ����
	bool HitMouse(bool layerCheck = false);
	// ���N���b�N���ꂽ����
	bool ClickMouse();
	// ���N���b�N����đI������Ă����Ԃ̏���
	bool SelectionMouse();
	// ���N���b�N�������ꑱ���Ă��鏈��
	bool HoldMouse();
	// �}�E�X�����ꂽ����
	bool ExitMouse();

public:

	// ���ݐG����Ԃ�
	bool GetActiveFlag()				{ return m_activeFlag; }
	// �F����Ԃ�
	SimpleMath::Color GetColor()		{ return m_boxColor; }
	// �F���(RGB)��Ԃ�
	SimpleMath::Vector3 GetColorRGB()	{ return SimpleMath::Vector3(m_boxColor.R(), m_boxColor.G(), m_boxColor.B()); }

	// �G�����/�G��Ȃ���Ԃւ̑J��
	void SetActiveFlag(bool flag)		{ m_activeFlag = flag; }

	// �}�E�X���������Ă��锻���ς����܂�
	void SetHitMouseFlag(bool flag)		{ m_hitMouseFlag = flag; }
	
	// �I����ԂɂȂ��Ă��锻���ς����܂�
	void SetSelectFlag(bool flag)		{ m_selectFlag = flag; }
	void SetKeySelectFlag(bool flag)	{ m_keySelectFlag = flag;}

	// �G�ꂽ�ۃ��[���h��Ԃɉe�����y�ڂ����ۂ�
	void SetWorldInfluenceFlag(bool flag) { m_worldInfluenceFlag = flag; }

	// �F�����R�ɕς����܂��B(�{�b�N�X�������������ۂȂǂɎg�p)
	void SetColor(SimpleMath::Color color) { m_boxColor = color; }

	void SetRect(RECT rect) { m_rect = rect; }

	void SetLayer(int layer) { m_layer = layer; }

	// �����ʒu���ƈꏏ�Ɉʒu���㏑�����܂�
	void SetSavePos(SimpleMath::Vector2 pos) { m_saveData.pos = m_data.pos = pos; }

	// ��������L�[��ݒ肷��
	void SetKey(std::vector<Keyboard::Keys> keys) { m_keys = keys; }

	// ��������L�[��Ԃ�
	std::vector<Keyboard::Keys> GetKeys() { return m_keys; }

protected:

	bool m_hitMouseFlag;		// �}�E�X���G��Ă��邱�Ƃ������t���O
	bool m_selectFlag;			// �I�����(ON/OFF)�������t���O
	bool m_keySelectFlag;		// �L�[�{�[�h��ɂđI�����ꂽ���Ƃ������t���O
	bool m_worldInfluenceFlag;	// �G�ꂽ�ۂɃ��[���h��Ԃɉe�����y�ڂ����Ƃ������t���O

	SimpleMath::Color m_boxColor;

	bool m_activeFlag; //���ݐG����Ԃ�

	// �������
	ObjectData2D m_saveData;

	RECT m_rect;

	int m_layer;

	// �I�����s���k�킹�鎞�ԑJ�ڗp�ϐ�
	float m_vibrationTime;

	// �z�[���h���Ԃ��擾���鎞�ԑJ�ڗp�ϐ�
	float m_holdTime;

	// ��������L�[�Q
	std::vector<Keyboard::Keys> m_keys;

};