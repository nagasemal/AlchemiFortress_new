//--------------------------------------------------------------------------------------
// File: Particle.h
//
//�@�p�[�e�B�N���𔭐������܂�
// 
// Date: 2023.7.3
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "ParticleUtility.h"
#include <list>

class Particle
{
public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		SimpleMath::Matrix		matWorld;
		SimpleMath::Matrix		matView;
		SimpleMath::Matrix		matProj;
		SimpleMath::Vector4		Diffuse;
	};

	enum EFFECT_TYPE : int
	{
		HIT_BULLET		= 0,		// �G�l�~�[�ɋ�����������
		SPAWN_ENEMY		= 1,		// �G�l�~�[���o������
		DELETE_ENEMY	= 2,		// �G�l�~�[���|�ꂽ
		MACHINE_LVUP	= 3,		// �}�V���̃��x�����オ����
		MACHINE_BREAK	= 4,		// �}�V�����󂳂ꂽ
		MACHINE_SPAWN	= 5,		// �}�V�����ݒu�������ۂɏo��p�[�e�B�N��
		CLICK			= 6,		// �N���b�N���ꂽ�ۂɏo��p�[�e�B�N��
		MINING_EFFECT	= 7,		// ��������������ۂɏo��p�[�e�B�N��
		RECOVERY_EFFECT	= 8,		// ���͂���������ۂɏo��p�[�e�B�N��
		DEFENSE_EFFECT	= 9,		// ���ˍU�����s�����ۂɏo��p�[�e�B�N��
		BULLET_LINE		= 10		// �o���b�g�̌��ɒǏ]����p�[�e�B�N��
	};

private:

	//�֐�
public:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	Particle(EFFECT_TYPE type);
	~Particle();

	void LoadTexture(const wchar_t* path);
	void CreateBillboard();

	void Initialize(const wchar_t* path = L"Particle");

	// �펞�p
	void Update(SimpleMath::Vector3 pos, bool flag = true,SimpleMath::Color color = { 1.0f,1.0f,1.0f,1.0f });
	// �P���p
	bool OnShot(SimpleMath::Vector3 pos, bool flag, SimpleMath::Color color = {1.0f,1.0f,1.0f,1.0f});

	// �p�[�e�B�N���𓮂���/��������
	void UpdateParticle();

	void Render();

	// �X�|�[���Ԋu��ݒ肷��
	void SetParticleSpawnTime(float time) { m_particleSpawnTime = time; }

	//�ϐ�
private:
	// �G�t�F�N�g�̎��
	EFFECT_TYPE m_effectType;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>							m_states;

	// �e�N�X�`���n���h��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>	m_texture;

	// ���_�z��
	std::vector<DirectX::VertexPositionColorTexture>				m_vertices;

	// �p�[�e�B�N���z��
	std::list<ParticleUtility>										m_particleUtility;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader>						m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader>						m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>					m_geometryShader;

	SimpleMath::Matrix m_billboard;
	SimpleMath::Matrix m_view;
	SimpleMath::Matrix m_proj;

	SimpleMath::Vector3 m_cameraPosition;
	SimpleMath::Vector3 m_cameraTarget;

	// ��x�ɏo��Particle�̗�
	int m_particleNum;

	// �p�[�e�B�N���̐����Ԋu
	float m_particleSpawnTime;

	bool m_colFlag;

	float m_timer;

private:

	void CreateShader();

	ParticleUtility CreateEffectParam(EFFECT_TYPE type, SimpleMath::Vector3 pos, SimpleMath::Color color = {1.0f,1.0f,1.0f,1.0f});

};