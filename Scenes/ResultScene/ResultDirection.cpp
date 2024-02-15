#include "pch.h"
#include "ResultDirection.h"

#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/InputSupport.h"
#include "NecromaLib/Singleton/DeltaTime.h"

#define ALPHA_VAL 0.2f			// �E�㖂�@�w�̓����x
#define ROTATE_VAL 0.5f			// �E�㖂�@�w�̉�]�p�x
#define SCALE_VAL 1.0f			// �E�㖂�@�w�̑傫��

ResultDirection::ResultDirection():
	m_animationData(),
	m_rotateNowFlag()
{
}

ResultDirection::~ResultDirection()
{
}

void ResultDirection::Update()
{
	InputSupport* pINP = &InputSupport::GetInstance();

	//�@====================[�@���N���b�N�������ۂ̏����@]
	//�@�@|=>�@�ϐ��̃��Z�b�g
	if (pINP->LeftButton_Press() && !m_rotateNowFlag)
	{
		m_animationData = 0.0f;
		m_rotateNowFlag = true;
	}

	//�@====================[�@���@�w�𓮂����@]
	if (m_rotateNowFlag)
	{
		m_animationData += DeltaTime::GetInstance().GetDeltaTime();
		m_animationData.anim = Easing::EaseInOutCubic(0.0f, XMConvertToRadians(90.0f), m_animationData);

		// �E��̖��@�w�̉�]���I�������V�[���J�ڂ��J�n���邽��
		// �A�j���[�V�����ϐ����ő�l�Ɏ����Ă��Ȃ����True�Ƃ���
		m_rotateNowFlag = !m_animationData.MaxCheck();

	}



}

void ResultDirection::Render()
{
	// �K�v�ȃ��\�[�X�̊m��
	ShareData& pSD = ShareData::GetInstance();
	SpriteLoder::TextureData texData = SpriteLoder::GetInstance().GetMachineMagicCircleTexture(1);
	auto pSB = pSD.GetSpriteBatch();
	auto device = pSD.GetDeviceResources();

	int width = device->GetOutputSize().right;
	int height = device->GetOutputSize().bottom;

	//�@====================[�@UI�`��̊J�n�@]
	pSB->Begin(DirectX::SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	//�@�@|=> �摜�̃T�C�Y
	RECT rect_circle = { 0, 0, texData.width, texData.height };

	//�@�@|=> �摜�̈ʒu�ݒ�
	SimpleMath::Vector2 box_Pos = { (float)width / 2.0f,(float)height / 2.0f };

	//�@�@|=>  �E��ɃN���b�N����]���閂�@�w��`��
	pSB->Draw(texData.tex.Get(),
		box_Pos,
		&rect_circle,
		SimpleMath::Color(1.0f, 1.0f, 1.0f, ALPHA_VAL),
		m_animationData.anim,
		DirectX::XMFLOAT2(static_cast<float>(texData.width / 2), static_cast<float>(texData.height / 2)),
		SCALE_VAL);

	pSB->End();
}
