//
// Camera.h
//
#pragma once

#include <SimpleMath.h>

/// <summary>
/// �f�o�b�O�p�J�����N���X
/// </summary>
class Camera
{
public:
	static const float DEFAULT_CAMERA_DISTANCE;	// �J�����̋���

private:

	// �r���[�s��
	SimpleMath::Matrix mView;

	// �v���W�F�N�V�����s��
	SimpleMath::Matrix mProjection;

	// �J�������W
	SimpleMath::Vector3 mEye;

	// �����_
	SimpleMath::Vector3 mTarget;

	// ������x�N�g��
	SimpleMath::Vector3 mUp;

public:
	// �R���X�g���N�^
	Camera();

	// �f�X�g���N�^
	virtual ~Camera();

	// �r���[�s��̃A�N�Z�T
	void SetViewMatrix(SimpleMath::Matrix view) { mView = view; }

	SimpleMath::Matrix GetViewMatrix()
	{
		CalculateViewMatrix();
		return mView;
	}

	// �v���W�F�N�V�����s��̃A�N�Z�T
	void SetProjectionMatrix(SimpleMath::Matrix projection) { mProjection = projection; }

	void CameraReset();

	SimpleMath::Matrix GetProjectionMatrix()
	{
		CalculateProjectionMatrix();
		return mProjection;
	}

	// �J�������W�̃A�N�Z�T
	void SetEyePosition(SimpleMath::Vector3 eye) { mEye = eye; }
	SimpleMath::Vector3 GetEyePosition() const { return mEye; }

	// �����_���W�̃A�N�Z�T
	void SetTargetPosition(SimpleMath::Vector3 target) { mTarget = target; }
	SimpleMath::Vector3 GetTargetPosition() const { return mTarget; }

	// ������x�N�g���̃A�N�Z�T
	void SetUpVector(SimpleMath::Vector3 up) { mUp = up; }
	SimpleMath::Vector3 GetUpVector() const { return mUp; }

protected:

	// �r���[�s��̎Z�o
	virtual void CalculateViewMatrix();

	// �v���W�F�N�V�����s��̎Z�o
	virtual void CalculateProjectionMatrix();
};
