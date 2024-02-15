#pragma once

#include "NecromaLib/GameData/Animation.h"

class TitleCamera
{
public:

	static const float DEFAULT_CAMERA_DISTANCE;	// �J�����̋���

	TitleCamera();
	~TitleCamera();

	void Initialize();
	// �X�V����
	void Update();

	// �r���[�s����擾����
	SimpleMath::Matrix GetViewMatrix() const { return m_view; }
	// �f�o�b�O�J�����̍��W���擾����
	SimpleMath::Vector3 GetEyePosition() const { return m_eye; }
	// �f�o�b�O�J�����̒����_���W���擾����
	SimpleMath::Vector3 GetTargetPosition() const { return m_target; }

	float GetAnimTime() { return m_animationData; }

private:

	float m_angleX;								// �c��]�p
	float m_angleY;								// ����]�p
	int m_prevX, m_prevY;						// �O��̃}�E�X���W(X,Y)
	int m_scrollWheelValue;						// �}�E�X�z�C�[���̃X�N���[���l
	int m_prevWheelValue;						// �O��̃X�N���[���l
	SimpleMath::Vector3 m_move;		// �ړ��l
	SimpleMath::Matrix m_view;			// �������ꂽ�r���[�s��
	SimpleMath::Vector3 m_eye;			// �J�����̍��W
	SimpleMath::Vector3 m_target;		// �����_

	AnimationData m_animationData;								// �����Ŏg���^�C�}�[

	// �r���[�s��̎Z�o
	void CalculateViewMatrix();

};