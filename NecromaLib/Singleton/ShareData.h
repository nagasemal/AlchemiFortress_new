//--------------------------------------------------------------------------------------
// File: ShareData.h
//
// ���L���鐔�l��|�C���^�𓾂�ׂ̃V���O���g���N���X
// �ϐ��̐錾�ƁA�A�N�Z�T��p�ӂ���K�v������
//
// Date: 2023.4.19
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once
#include "DeviceResources.h"
#include "SpriteBatch.h"
#include "NecromaLib/GameData/Camera.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "Effects.h"

class ShareData
{
public:
	~ShareData() = default;

	ShareData(const ShareData&) = delete;
	ShareData& operator=(const ShareData&) = delete;

	static void Create();
	static void Destroy();

	static ShareData& GetInstance()						{ return *instance; }


	//[�@�A�N�Z�T�@]
public:

	// �f�o�C�X���\�[�X
	void SetDeviceResources(DX::DeviceResources* pDR)	{ m_deviceResources = pDR;}
	DX::DeviceResources* GetDeviceResources()			{ return m_deviceResources;}

	ID3D11Device1* GetDevice()							{ return m_deviceResources->GetD3DDevice();}
	ID3D11DeviceContext1* GetContext()					{ return m_deviceResources->GetD3DDeviceContext(); }

	// �R�����X�e�[�g
	void SetCommonStates(DirectX::CommonStates* pCS)	{ m_commonStates = pCS; }
	DirectX::CommonStates* GetCommonStates()			{ return m_commonStates; }

	// �X�v���C�g�o�b�`
	void SetSpriteBatch(DirectX::SpriteBatch* pSB)		{ m_spriteBatch = pSB; }
	DirectX::SpriteBatch* GetSpriteBatch()				{ return m_spriteBatch; }

	// �G�t�F�N�g�t�@�N�g���[
	void SetEffectFactory(DirectX::EffectFactory* pEF)	{ m_effectFactory = pEF; }
	DirectX::EffectFactory* GetEffectFactory()			{ return m_effectFactory; }

	// �J����
	void SetCamera(Camera* camera)						{ m_camera = camera;}
	Camera* GetCamera()									{ return m_camera; }

	// View�s��
	SimpleMath::Matrix GetView()				{ return m_camera->GetViewMatrix(); }
	// Projection�s��
	SimpleMath::Matrix GetProjection()			{ return m_camera->GetProjectionMatrix(); }

private:
	ShareData();
	static ShareData*				instance;

	Camera*							m_camera;

	DirectX::CommonStates*			m_commonStates;

	DX::DeviceResources*			m_deviceResources;

	DirectX::SpriteBatch*			m_spriteBatch;

	DirectX::EffectFactory*			m_effectFactory;

};