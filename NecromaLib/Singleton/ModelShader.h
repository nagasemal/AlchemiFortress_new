//--------------------------------------------------------------------------------------
// File: ModelShader.h
//
//�@3D���f���ɓK��������V�F�[�_�[�̐ݒ��ێ�����V���O���g���N���X
// 
// Date: 2023.10.06
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
class ModelShader
{
private:

	ModelShader();
	static ModelShader* instance;

public:
	~ModelShader() = default;

	ModelShader(const ModelShader&) = delete;
	ModelShader& operator=(const ModelShader&) = delete;

	static void Create();
	static void Destroy();

	static ModelShader& GetInstance() { return *instance; }

	/// <summary>
	/// 3D���f���p�̃V�F�[�_�[�𐶐����܂�
	/// </summary>
	void CreateModelShader();

	/// <summary>
	/// �G�t�F�N�g�p�̃V�F�[�_�[�𐶐����܂�
	/// </summary>
	void CreateEffectModel();

	/// <summary>
	/// �G�t�F�N�g�p�̎��ԕϐ����X�V���܂�
	/// </summary>
	/// <param name="deltaTime"></param>
	void Update(float deltaTime);

public:


	/// <summary>
	/// �V���G�b�g�`��p�̃f�v�X�X�e���V���̐ݒ��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> GetStencilShadow() { return m_depthStencilState_Shadow; }

	/// <summary>
	/// ���f���̃V���G�b�g�p�s�N�Z���V�F�[�_�[��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetModelShadowShader() { return m_modelShadowShader; }

	/// <summary>
	/// ���f���̔������`��p�s�N�Z���V�F�[�_�[��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetModelTransparentShader() { return m_modelTransparentShader; }

	/// <summary>
	/// ���f���̃G�t�F�N�g���s�N�Z���V�F�[�_�[��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetModelEffectShader() { return m_modelEffect_PS; }
	
	/// <summary>
	/// ���f���`��ݒ�Ɏg�p����s�N�Z���V�F�[�_�[��Ԃ��܂�[�}�V���p]
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetMachineModelShader_PS() { return m_machineModelShader_PS; }

	/// <summary>
	/// ���f���`��ݒ�Ɏg�p����s�N�Z���V�F�[�_�[��Ԃ��܂�[�ėp]
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetModelMyShader_PS() { return m_modelMyShader_PS; }

	/// <summary>
	/// ���f���`��ݒ�Ɏg�p���郔�@�[�e�b�N�X�V�F�[�_�[��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetModelMyShader_VS() { return m_modelMyShader_VS; }	

	DirectX::Model* GetMagicTrauabgukarPyram() { return m_magicTrauabgukarPyram.get(); }
	
	/// <summary>
	/// ���f��(�}�V��)�̕`��ݒ�
	/// </summary>
	/// <param name="color">�F���</param>
	/// <param name="time">���ԏ��</param>
	/// <param name="texture">�e�N�X�`�����</param>
	void MachineDrawShader(SimpleMath::Color color,SimpleMath::Vector4 time, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);


	/// <summary>
	/// ���f��(�ėp)�̕`��ݒ�
	/// </summary>
	/// <param name="color">�F���</param>
	/// <param name="time">���ԏ��</param>
	/// <param name="texture">�e�N�X�`�����</param>
	void ModelDrawShader(SimpleMath::Color color, SimpleMath::Vector4 time, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);

	/// <summary>
	/// ���f���G�t�F�N�g�̕`��ݒ�
	/// </summary>
	/// <param name="color">�F���</param>
	/// <param name="time">���ԏ��</param>
	/// <param name="texture">�e�N�X�`�����</param>
	void ModelEffectShader(SimpleMath::Color color, SimpleMath::Vector4 time, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);

	/// <summary>
	/// �V���G�b�g�`��̕`��ݒ�
	/// </summary>
	void SilhouetteShader(SimpleMath::Color color = SimpleMath::Color(Colors::LightYellow));

	/// <summary>
	/// �������`��̕`��ݒ�
	/// </summary>
	void ToransparentShader();

	/// <summary>
	/// �I�[�����̃G�t�F�N�g��`�悵�܂�
	/// </summary>
	/// <param name="time">�h��߂����鎞�ԕϐ�</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="rage">�傫��</param>
	/// <param name="color">�F���</param>
	void DrawAuraEffect(float time,SimpleMath::Vector3 pos, SimpleMath::Vector3 rage,SimpleMath::Color color = SimpleMath::Color(1.0f,1.0f,1.0f,1.0f));

public:

	/// <summary>
	/// �e�`��̕`��ݒ�
	/// </summary>
	void ShadowModelDraw(bool outlineFlag = true);

	// �V���h�E�}�b�v�p�i�����_�[�e�N�X�`���j
	DX::RenderTexture* GetShadowMap() { return m_shadowMapRT.get(); }
	// �[�x�o�b�t�@�p�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D> GetDepathTexture2D() { return m_depathTexture2D; }
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return m_depathStencilView; }

private:

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState_Base;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState_Shadow;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState_Nomal;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_modelShadowShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_modelTransparentShader;

	// ���Ԍo�߂�`����ǉ��̃R���X�^���g�o�b�t�@
	struct ConstBuffer
	{
		SimpleMath::Vector4 Time;			// �l�J�ڗp���ԕϐ�
		SimpleMath::Color PaintColor;		// �ǉ��̐F���
		SimpleMath::Color LimLightColor;	// �������C�g�̃J���[
		SimpleMath::Vector4 eyes;			// �����_(4�̔{�������󂯎��Ȃ��ׁAVector4�Ƃ���)


		SimpleMath::Vector4 LightPos;

		SimpleMath::Vector4 mousePos;		// �|�C���g���C�g�̈ʒu

		SimpleMath::Vector4 crystalPos[10];		// �N���X�^���̈ʒu

		SimpleMath::Matrix view;			// �r���[�s��
		SimpleMath::Matrix proj;			// �v���W�F�N�V�����s��
	};


	// �}�V�����f���Ɏg�p����V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_machineModelShader_PS;
	// �ʏ�`�惂�f���Ɏg�p����V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_modelMyShader_PS;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_modelMyShader_VS;

	//�@====================[�@�A�E�g���C���`��Ɏg�p�@]
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_modelOutLineShader_VS;
	// �C���v�b�g���C�A�E�g(�A�E�g���C���p)
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputOutlineLayout;


	// ���f����p�����G�t�F�N�g�ɗp����V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_modelEffect_PS;

	// �C���v�b�g���C�A�E�g(�ʏ�`��p)
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �󂯓n���p�̃R���X�^���g�o�b�t�@
	D3D11_BUFFER_DESC m_constBuffer;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_cbuffer;

	// �G�t�F�N�g�p�̃��f��
	std::unique_ptr<DirectX::Model> m_magicTrauabgukarPyram;

	// �G�t�F�N�g�p�̃W�I���g���b�N�v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_effectBox;

	// �V�F�[�_�[�p���ԕϐ�
	float m_shaderTimer;

	SimpleMath::Vector4 m_lightPos;

private:

	// �萔�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowConstantBuffer;

	// �e�`��(�[�x�e�N�X�`���ɏ������ނ��߂�)�g�p����V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_depathShadowShader_PS;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_depathShadowShader_VS;

	// �V���h�E�}�b�v�p�i�����_�[�e�N�X�`���j
	std::unique_ptr<DX::RenderTexture>					m_shadowMapRT;
	// �[�x�o�b�t�@�p�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_depathTexture2D;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>      m_depathStencilView;

	// �T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			m_shadowMapSampler;

};