//--------------------------------------------------------------------------------------
// File: DorpShadow.h
//
//�@�I�u�W�F�N�g�̐^���ɃV�F�[�_�[��p���Ċۉe�𗎂Ƃ��܂�
// 
// Date: 2023.7.3
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once

class DorpShadow
{
public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		SimpleMath::Matrix		m_matWorld;
		SimpleMath::Matrix		m_matView;
		SimpleMath::Matrix		m_matProj;
		SimpleMath::Vector4		m_diffuse;
	};

public:
	DorpShadow();
	~DorpShadow();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
	void CreateShader();

	// vector�z��ɒ��g������
	void CreateShadow(SimpleMath::Vector3 pos);
	// vector�z��̒��g����������
	void DeleteShadow();

	void CreateWorld();

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

private:

	// �ۉe�e�N�X�`�����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �R���X�^���X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// ���_���
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	SimpleMath::Matrix m_world;
	SimpleMath::Matrix m_view;
	SimpleMath::Matrix m_proj;

};