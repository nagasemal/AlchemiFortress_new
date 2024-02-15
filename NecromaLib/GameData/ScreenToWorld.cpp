#include <pch.h>
#include "ScreenToWorld.h"

SimpleMath::Vector3 CalcScreenToWorldN(int sX, int sY, float fZ, int screen_W, int screen_H, SimpleMath::Matrix view, SimpleMath::Matrix prj)
{
	// �e�s��̋t�s����Z�o
	XMMATRIX invView, invPrj, vP, invViewport = XMMATRIX();

	// �r���[�s��̋t�s��
	invView = XMMatrixInverse(nullptr, view);

	// �v���W�F�N�V�����s��̋t�s��
	invPrj	= XMMatrixInverse(nullptr, prj);

	// �r���[�|�[�g�s��
	vP		= XMMatrixIdentity();

	XMFLOAT4X4 matrix = XMFLOAT4X4();

	// ��ʃT�C�Y����r���[�|�[�g�s����Z�o����
	matrix._11 =  screen_W / 2.f;
	matrix._22 = -screen_H / 2.f;
	matrix._41 =  screen_W / 2.f;
	matrix._42 =  screen_H / 2.f;

	// XMFLOAT4X4��XMMATRIX�ɕϊ�����vP�ɓ����
	vP += DirectX::XMLoadFloat4x4(&matrix);
	// �r���[�|�[�g�s��̋t�s��
	invViewport = XMMatrixInverse(nullptr, vP);

	// �X�N���[�����W�����[���h��ԍ��W�ɕϊ�����s��@�t�ϊ�
	SimpleMath::Matrix tmp = invViewport * invPrj * invView;

	// �X�N���[�����W(sX,sY)�ƍŋ�,���_(fZ)��tmp�������ă��[���h��ԍ��W���Z�o
	SimpleMath::Vector3 pOut = XMVector3TransformCoord(SimpleMath::Vector3((float)sX, (float)sY, (float)fZ), tmp);

	return pOut;
}

SimpleMath::Vector3 CalcScreenToXZN(int sX, int sY, int screen_W, int screen_H, SimpleMath::Matrix view, SimpleMath::Matrix prj)
{
	SimpleMath::Vector3 nearPos, farPos, ray = SimpleMath::Vector3::Zero;

	// �ŋߓ_
	nearPos = CalcScreenToWorldN(sX, sY, 0.0f, screen_W, screen_H, view, prj);

	// �ŉ��_
	farPos = CalcScreenToWorldN(sX, sY, 1.0f, screen_W, screen_H, view, prj);

	// �������擾���A�m�[�}���C�Y����
	ray = farPos - nearPos;
	ray.Normalize();

	SimpleMath::Vector3 pOut = SimpleMath::Vector3::Zero;

	// �J�������猩��Y�������ɑ������ǂ����@��_�����݂��邩�ǂ���
	if (ray.y <= 0)
	{
		// ����_
		SimpleMath::Vector3 lRay = XMVector3Dot(ray, SimpleMath::Vector3(0, 1, 0));
		SimpleMath::Vector3 lp0  = XMVector3Dot(-nearPos, SimpleMath::Vector3(0, 1, 0));

		pOut = nearPos + (lp0 / lRay) * ray;

	}
	// ���݂��Ȃ��ꍇ�͍ŉ��_�Ƃ���
	else 		pOut = farPos;

	// �}�E�X�̃��[���h���W
	return pOut;
}