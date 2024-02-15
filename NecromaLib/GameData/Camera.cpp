//
// Camera.cpp
//
#include "pch.h"
#include "Camera.h"

#include "DeviceResources.h"
#include "NecromaLib/Singleton/ShareData.h"


using namespace DirectX;

// �萔�̏�����
const float Camera::DEFAULT_CAMERA_DISTANCE = 5.0f;

Camera::Camera()
	: mView(SimpleMath::Matrix::Identity)
	, mEye(0.0f, 15.0f, 1.0f)
	, mTarget(0.0f, 0.0f, 0.0f)
	, mUp(0.0f, 1.0f, 0.0f)
{
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}


Camera::~Camera()
{
}

void Camera::CameraReset()
{

	mEye = SimpleMath::Vector3(0.0f, 15.0f, 1.0f);
	mTarget = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	mUp = SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

}

void Camera::CalculateViewMatrix()
{
	mView = SimpleMath::Matrix::CreateLookAt(mEye, mTarget, mUp);
}


void Camera::CalculateProjectionMatrix()
{
	DX::DeviceResources* pDR = ShareData::GetInstance().GetDeviceResources();

	// �E�B���h�E�T�C�Y�̎擾
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);

	constexpr float fieldOfView = XMConvertToRadians(45.0f);    // ��p
	float aspectRatio = width / height;							// ��ʏc����
	float nearPlane = 1.0f;                                     // �J���������ԋ߂����e��
	float farPlane = 300.0f;                                    // �J���������ԉ������e��

	mProjection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

}
