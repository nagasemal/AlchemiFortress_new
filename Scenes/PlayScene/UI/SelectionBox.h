//--------------------------------------------------------------------------------------
// File		: SelectionBox.h
//
// �I�u�W�F�N�g�I�������Ɍ����I���\UI
// ��{�@�\ �G���@�N���b�N�@�z�[���h�@�{�^�����@���ꂽ�u�ԁ@ �̎擾
// 
// Use		: MachineSelect AlchemicalMachineObject
//			  AM_Attacker AM_Upeer
// Date		: 2023.7.12
// Author	: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once
#include "Scenes/Commons/SelectionUI.h"
#include "Scenes/PlayScene/AlchemicalMachine/AlchemicalMachineObject.h"

class SelectionBox : public SelectionUI
{
public:
	SelectionBox(SimpleMath::Vector2 pos,SimpleMath::Vector2 rage);
	~SelectionBox();

	void Update()				override;
	// �`��
	void Draw()					override;

	void DrawUI(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pulsTexture = nullptr,
		RECT rect = { 0,0,64,64 },
		SimpleMath::Color pulsTextureCol = { 1.0f,1.0f,1.0f,1.0f }, float pulsRage = 0.8f,int pulsWidth = 64, int pulsHeight = 64);

	// �摜�̊g�喳���o�[�W����
	void DrawUI(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,float rotate);

	// ���g��UI�A�C�R���ł���ꍇ�Ɏg�p
	void DrawUI(int UInumber);

	void DrawUI(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pulsTexture = nullptr,
		RECT rect = { 0,0,64,64 },float pulsRage = 0.8f,
		SimpleMath::Color pulsTextureCol = {1.0f,1.0f,1.0f,1.0f},
		SimpleMath::Color nomalColor	 = {1.0f,1.0f,1.0f,1.0f},
		SimpleMath::Color onColor		 = {0.9f,0.9f,0.9f,1.0f},
		SimpleMath::Color pressdColor	 = {0.7f,0.7f,0.7f,1.0f});

	void DrawUI(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
		RECT rect							= { 0,0,64,64 },
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pulsTexture = nullptr,
		RECT pulsTexRect					= { 0,0,64,64 },
		SimpleMath::Color pulsTextureCol	= { 1.0f,1.0f,1.0f,1.0f },
		SimpleMath::Color nomalColor		= { 1.0f,1.0f,1.0f,1.0f },
		SimpleMath::Color onColor			= { 0.9f,0.9f,0.9f,1.0f },
		SimpleMath::Color pressdColor		= { 0.7f,0.7f,0.7f,1.0f });

private:

	float m_popUITextTimer;

	std::unique_ptr<DrawKey> m_drawKey;

};
