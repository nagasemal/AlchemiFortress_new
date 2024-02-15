//--------------------------------------------------------------------------------------
// File: ScreenToWorld.h
//
// �X�N���[�����W�����[���h���W�ɕϊ����邽�߂̃N���X
// 
// Date: 2023.4.19
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once

/// <summary>
/// �X�N���[�����W����ŋߓ_,�ŉ��_�����߁A����XZ���ʂɏՓ˂��Ă����
/// ���̈ʒu��Ԃ��A�����Ă��Ȃ���΍ŉ��_��Ԃ��֐�
/// </summary>
/// <param name="sX">�X�N���[�����W�@X</param>
/// <param name="sY">�X�N���[�����W�@Y</param>
/// <param name="screen_W">��ʃT�C�Y����</param>
/// <param name="screen_H">��ʃT�C�Y�c��</param>
/// <param name="view">�r���[�s��</param>
/// <param name="prj">�v���W�F�N�V�����s��</param>
/// <returns></returns>
SimpleMath::Vector3 CalcScreenToXZN(
	int sX,		
	int sY,		
	int screen_W, 
	int screen_H, 
	SimpleMath::Matrix view,
	SimpleMath::Matrix prj
);

/// <summary>
/// �X�N���[�����W�����[���h��ԍ��W�ɂ���ɂ�����K�v�ƂȂ�t�s���
/// �v�Z���A�ϊ�����֐�
/// </summary>
/// <param name="sX">�X�N���[�����W�@X</param>
/// <param name="sY">�X�N���[�����W�@Y</param>
/// <param name="fZ">�ˉe��Ԃł�Z�l(0~1)</param>
/// <param name="screen_W">��ʉ���</param>
/// <param name="screen_H">��ʏc��</param>
/// <param name="view">�r���[�s��</param>
/// <param name="prj">�v���W�F�N�V�����s��</param>
/// <returns></returns>
SimpleMath::Vector3 CalcScreenToWorldN(
	int sX,		
	int sY,		
	float fZ,	
	int screen_W, 
	int screen_H, 
	SimpleMath::Matrix view,
	SimpleMath::Matrix prj
);