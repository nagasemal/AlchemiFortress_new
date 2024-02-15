#pragma once
#include "PrimitiveBatch.h"

#include "NecromaLib/GameData/Animation.h"

class TitleLogo
{
public:

	//UI�̃A���J�[�|�C���g
	enum ANCHOR
	{
		TOP_LEFT = 0,
		TOP_CENTER,
		TOP_RIGHT,

		MIDDLE_LEFT,
		MIDDLE_CENTER,
		MIDDLE_RIGHT,

		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT

	};

public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		SimpleMath::Vector4	windowSize;
		SimpleMath::Vector4	color;
		SimpleMath::Vector4	diffuse;
	};

public:
	TitleLogo();
	~TitleLogo();

	void LoadTexture(const wchar_t* path);

	void Create(const wchar_t* path);

	void Update();
	void Render();

	void SetWindowSize(const int& width, const int& height);

	void SetScale(SimpleMath::Vector2 scale);
	void SetPosition(SimpleMath::Vector2 position);

	void SetColor(SimpleMath::Color color) { m_color = color; }
	SimpleMath::Color GetColor() { return m_color; }

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

private:

	// ���@�w�e�N�X�`�����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;

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

	int m_windowWidth, m_windowHeight;
	int m_textureWidth, m_textureHeight;

	SimpleMath::Vector2 m_scale;
	SimpleMath::Vector2 m_baseScale;
	SimpleMath::Vector2 m_position;
	SimpleMath::Color m_color;
	SimpleMath::Matrix	m_rotationMatrix;

	// ���@�w�𓧖����������ɏo�������鎞�Ԍv���ϐ�
	float m_animationTime;
	float m_animationSin;

	// �g��̕\���Ɏg�p
	AnimationData m_ripplesData;

private:

	void CreateShader();

};