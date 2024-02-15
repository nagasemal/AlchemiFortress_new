//--------------------------------------------------------------------------------------
// File: MagicCircle.h
//
//  �V�F�[�_�[�g�p
//�@�A���P�~�J���}�V�����I�𒆁@/�@�v���C���[�x�[�X��Lv�\���ɂ������@�w�̏���
//  
// Date: 2023.7.10
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once

class MagicCircle
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
	MagicCircle();
	~MagicCircle();

	void Initialize();
	void Update();
	void Render(int magicCircleNumber);
	void Finalize();

	void CreateShader();

	// vector�z��ɒ��g������
	void CreateMagicCircle(SimpleMath::Vector3 pos, float r, SimpleMath::Color color = {1.0f,1.0f,1.0f,1.0f});

	void DeleteMagicCircle();

	void CreateWorld();

	void LoadTexture(const wchar_t* path);

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	float GetAnimationTime() { return m_animationTime; }

private:

private:

	// ���@�w�e�N�X�`�� �}�V���p
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textures;

	// �R���X�^���X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
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

	SimpleMath::Matrix m_world_MagicCircle;
	SimpleMath::Matrix m_world_Effect;
	SimpleMath::Matrix m_view;
	SimpleMath::Matrix m_proj;

	float m_animationTime;
};
