#pragma once

class MyPostProcess
{
public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	eyes;
	};

public:
	MyPostProcess();
	~MyPostProcess();

	void CreateShader();
	void Render(ID3D11ShaderResourceView* const* offscreenTex, ID3D11ShaderResourceView* const* depthTex);

	// ��ʑS�̂̐F�����̋���������
	void SetChromaticAberrationVal(float val)	{ m_chromaticVal = val; }
	// ��ʑS�̂̃u���[�̋���������
	void SetBlerVal(float val)					{ m_blerVal = val; }

private:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>		m_geometryShader;

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

	// �F�����̋���
	float m_chromaticVal;
	// �u���[�̋���
	float m_blerVal;

};