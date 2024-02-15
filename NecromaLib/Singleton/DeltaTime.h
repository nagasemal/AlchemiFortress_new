//--------------------------------------------------------------------------------------
// File: DeltaTime.h
//
// �f���^�^�C���𓾂�ׂ̃V���O���g���N���X
//
// Date: 2023.4.19
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once
#include "StepTimer.h"

class DeltaTime
{
public:
	~DeltaTime() = default;

	DeltaTime(const DeltaTime&) = delete;
	DeltaTime& operator=(const DeltaTime&) = delete;

	static void Create();
	static void Destroy();

	static DeltaTime& GetInstance() { return *instance; }

	/// <summary>
	/// �Q�[�����ŕω�����f���^�^�C����Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	float GetDeltaTime() { return ((float)m_stepTimer.GetElapsedSeconds() * m_doubleSpeed) * !m_stopTimeFlag; }

	/// <summary>
	/// �l�̉��Z���Z�������Ȃ��ĂȂ��f�̃f���^�^�C����Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	float GetNomalDeltaTime();

	/// <summary>
	/// �X�e�b�v�^�C�}�[�N���X��Ԃ��܂�
	/// </summary>
	DX::StepTimer GetStepTimer() { return m_stepTimer; }

	/// <summary>
	/// �f���^�^�C�������
	/// </summary>
	/// <param name="time"></param>
	void SetDeltaTime(DX::StepTimer timer)		{ m_stepTimer = timer; }
	
	/// <summary>
	/// �{���ʂ����
	/// </summary>
	/// <param name="speed"></param>
	void SetDoubleSpeed(float speed)	{ m_doubleSpeed = speed; }

	/// <summary>
	/// �Q�[�������Ԃ��~�߂�t���O�����
	/// </summary>
	/// <param name="flag"></param>
	void SetStopFlag(bool flag)			{ m_stopTimeFlag = flag; }

private:
	DeltaTime();
	static DeltaTime* instance;

	// ���̃X�s�[�h����⑁������
	const float SPEED = 1.2f;

	// �X�e�b�v�^�C�}�[
	DX::StepTimer m_stepTimer;

	// �{����
	float m_doubleSpeed;

	// �Ԃ��f���^�^�C����0�ɂ���
	bool m_stopTimeFlag;

};