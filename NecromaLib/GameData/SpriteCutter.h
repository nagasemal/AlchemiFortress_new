//--------------------------------------------------------------------------------------
// File: ShareData.h
//
// 2D�A�j���[�V�����̕\���ɖ��ɗ��֐����܂Ƃ߂��N���X
// 
// Date: 2023.4.21
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include <SimpleMath.h>

/// <summary>
/// 2D�A�j���[�V�����̐؂�ւ��ɖ��ɗ��֐�
/// </summary>
/// <param name="wight">	1�摜�̉���</param>
/// <param name="height">	1�摜�̏c��</param>
/// <param name="key">		�A�j���[�V�������񂷏���</param>
/// <param name="beside">	�����w��</param>
/// <param name="vertical">	�s���w��</param>
/// <param name="interval"> ���̃A�j���[�V�����ɐ؂�ւ��܂ł̎���</param>
/// <returns></returns>
RECT SpriteCutter(int wight, int height, int key[], int beside = 0, int vertical = 0, int interval = 60);

/// <summary>
/// �X�v���C�g��؂邾���̊֐�
/// </summary>
/// <param name="wight">	1�摜�̉���</param>
/// <param name="height">	1�摜�̏c��</param>
/// <param name="beside">	�����w��</param>
///  <param name="vertical">�s���w��</param>
/// <returns></returns>
RECT SpriteCutter(int wight, int height, int beside = 0, int vertical = 0);