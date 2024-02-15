#pragma once

#include "Scenes/Commons/SelectionUI.h"

class ShaderTemplate
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
	ShaderTemplate();
	~ShaderTemplate();

	void LoadTexture(const wchar_t* path);

	void Create(const wchar_t* path);
	void LoadShaderFile(const wchar_t* path);
	void AdvanceRender(); // ���O�ɒ��������͌Ă�ł���

	void SetWindowSize(const int& width, const int& height)	{ m_windowWidth = width; m_windowHeight = height; };

	void SetScale(SimpleMath::Vector2 scale)				{ m_scale = scale;}
	SimpleMath::Vector2 GetScale()							{ return m_scale; }

	void SetPosition(SimpleMath::Vector2 position)			{ m_position = position;}
	SimpleMath::Vector2 GetPosition()						{ return m_position; }

	void SetColor(SimpleMath::Color color)					{ m_color = color; }
	void SetColor(const DirectX::XMVECTORF32 color)			{ m_color = (SimpleMath::Color)color; }
	SimpleMath::Color GetColor()							{ return m_color; }

	void SetRotationMatrix(SimpleMath::Matrix matrix)		{ m_rotationMatrix = matrix; }

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

protected:

	// �e�N�X�`�����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource>				m_res;

	// �R���X�^���X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_cBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_inputLayout;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// ���_���
	std::vector<DirectX::VertexPositionColorTexture>	m_vertices;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>				m_states;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>		m_geometryShader;

	int m_windowWidth, m_windowHeight;
	int m_textureWidth, m_textureHeight;

	SimpleMath::Vector2 m_scale;
	SimpleMath::Vector2 m_baseScale;
	SimpleMath::Vector2 m_position;
	SimpleMath::Color m_color;
	SimpleMath::Matrix	m_rotationMatrix;

};