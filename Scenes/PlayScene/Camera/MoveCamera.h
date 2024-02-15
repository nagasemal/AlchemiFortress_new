#pragma once

#include "NecromaLib/GameData/Animation.h"

class MoveCamera
{
public:
	static const float DEFAULT_CAMERA_DISTANCE;	// �J�����̋���

	MoveCamera();
	~MoveCamera();

	void Initialize();
	// �X�V����
	void Update(bool scroll,bool move);

	// �r���[�s����擾����
	SimpleMath::Matrix GetViewMatrix() const		{ return m_view; }
	// �f�o�b�O�J�����̍��W���擾����
	SimpleMath::Vector3 GetEyePosition() const		{ return m_eye; }
	// �f�o�b�O�J�����̒����_���W���擾����
	SimpleMath::Vector3 GetTargetPosition() const	{ return m_target; }
	// �Q�[���J�n���̈������I��������Ƃ�m�点��t���O
	bool GetStopCameraFlag();

	void SetEyeProsition(SimpleMath::Vector3 eye)			{ m_eye = eye;}
	void SetTargetProsition(SimpleMath::Vector3 target)		{ m_target = target; }

	void SetCameraMove(SimpleMath::Vector3 position)		{ m_move = position; }

	void SetCameraLock(bool flag) { m_moveLock = flag; }
	bool GetCameraLock() { return m_moveLock; }

	void TargetChange(SimpleMath::Vector3 target);
	void ResetTargetChangeTimer();

private:

	// �c��]�p
	float m_angleX;								
	// ����]�p
	float m_angleY;								
	// �O��̃}�E�X���W(X,Y)
	int m_prevX, m_prevY;						
	// �}�E�X�z�C�[���̃X�N���[���l
	int m_scrollWheelValue;				
	// �O��̃X�N���[���l
	int m_prevWheelValue;						
	// �ړ��l
	SimpleMath::Vector3 m_move;		
	// �������ꂽ�r���[�s��
	SimpleMath::Matrix m_view;			
	// �J�����̍��W
	SimpleMath::Vector3 m_eye;
	// �����_
	SimpleMath::Vector3 m_target;

	// ���̒����_
	SimpleMath::Vector3 m_nextTarget;

	// �����Ŏg���^�C�}�[
	AnimationData m_time;			
	// �^�[�Q�b�g�ύX�Ɏg���^�C�}�[
	AnimationData m_targetChangeTime;

	// �}�E�X�|�C���^�̃h���b�O�J�n�ʒu����̕ψ�(���Βl)
	void DraggedDistance(int x, int y);

	// �r���[�s��̎Z�o
	void CalculateViewMatrix();

	bool m_moveLock;
};