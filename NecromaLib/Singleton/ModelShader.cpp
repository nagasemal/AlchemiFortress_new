#include "pch.h"
#include "ModelShader.h"

#include "NecromaLib/GameData/BinaryFile.h"
#include "ShareData.h"
#include "ReadData.h"

#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/InputSupport.h"

ModelShader* ModelShader::instance = nullptr;

ModelShader::ModelShader():
	m_constBuffer(),
	m_shaderTimer()
{

	m_lightPos = SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f);

}

void ModelShader::Create()
{
	if (instance == nullptr)
	{
		instance = new ModelShader;
	}
}

void ModelShader::Destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void ModelShader::CreateModelShader()
{

	ShareData& pSD = ShareData::GetInstance();

	//�@====================[�@�V�F�[�_�[�t�@�C���̓ǂݍ��݁@]
	
	//�@�@|=>�@�V���G�b�g�`��p�̃s�N�Z���V�F�[�_�[
	BinaryFile PSData_Shadow = BinaryFile::LoadFile(L"Resources/Shader/ModelShadow_PS.cso");
	pSD.GetDevice()->CreatePixelShader(PSData_Shadow.GetData(), PSData_Shadow.GetSize(), NULL, m_modelShadowShader.ReleaseAndGetAddressOf());
	
	//�@�@|=> �������`��p�̃s�N�Z���V�F�[�_�[
	BinaryFile PSData_Transparent = BinaryFile::LoadFile(L"Resources/Shader/ModelTransparent_PS.cso");
	pSD.GetDevice()->CreatePixelShader(PSData_Transparent.GetData(), PSData_Transparent.GetSize(), NULL, m_modelTransparentShader.ReleaseAndGetAddressOf());

	//�@�@|=> �}�V�����f���`��p�̃s�N�Z���V�F�[�_�[
	BinaryFile PSData_MachineModel = BinaryFile::LoadFile(L"Resources/Shader/MyModelShader_PS.cso");
	pSD.GetDevice()->CreatePixelShader(PSData_MachineModel.GetData(), PSData_MachineModel.GetSize(), NULL, m_machineModelShader_PS.ReleaseAndGetAddressOf());
	
	//�@�@|=> �ʏ탂�f���`��p�̃s�N�Z���V�F�[�_�[
	BinaryFile PSData_MyModel = BinaryFile::LoadFile(L"Resources/Shader/NomalModelShader_PS.cso");
	pSD.GetDevice()->CreatePixelShader(PSData_MyModel.GetData(), PSData_MyModel.GetSize(), NULL, m_modelMyShader_PS.ReleaseAndGetAddressOf());

	//�@�@|=> ���f����p�����G�t�F�N�g�p�̃V�F�[�_�[
	BinaryFile PSData_EffectModel = BinaryFile::LoadFile(L"Resources/Shader/MagicEffectShader_PS.cso");
	pSD.GetDevice()->CreatePixelShader(PSData_EffectModel.GetData(), PSData_EffectModel.GetSize(), NULL, m_modelEffect_PS.ReleaseAndGetAddressOf());

	//�@�@|=> ���_���󂯓n���p�̃o�[�e�b�N�X�V�F�[�_�[
	BinaryFile VSData_MyModel = BinaryFile::LoadFile(L"Resources/Shader/MyModelShader_VS.cso");
	pSD.GetDevice()->CreateVertexShader(VSData_MyModel.GetData(), VSData_MyModel.GetSize(), NULL, m_modelMyShader_VS.ReleaseAndGetAddressOf());

	//�@�@|=> ���_���󂯓n���p�̃o�[�e�b�N�X�V�F�[�_�[(�A�E�g���C���g���p)
	BinaryFile VSData_OutlineModel = BinaryFile::LoadFile(L"Resources/Shader/ModelOutLine_VS.cso");
	pSD.GetDevice()->CreateVertexShader(VSData_OutlineModel.GetData(), VSData_OutlineModel.GetSize(), NULL, m_modelOutLineShader_VS.ReleaseAndGetAddressOf());

	//�@�@|=> ���f����p�����G�t�F�N�g�p�̃V�F�[�_�[
	BinaryFile PSData_DepathShadowModel = BinaryFile::LoadFile(L"Resources/Shader/PostProcessModel_PS.cso");
	DX::ThrowIfFailed(
		pSD.GetDevice()->CreatePixelShader(PSData_DepathShadowModel.GetData(), PSData_DepathShadowModel.GetSize(), NULL, m_depathShadowShader_PS.ReleaseAndGetAddressOf())
	);

	//�@====================[�@�C���v�b�g���C�A�E�g�̍쐬�@] 
	pSD.GetDevice()->CreateInputLayout(VertexPositionNormalTangentColorTexture::InputElements,
		VertexPositionNormalTangentColorTexture::InputElementCount,
		VSData_MyModel.GetData(), VSData_MyModel.GetSize(),
		m_inputLayout.GetAddressOf());

	pSD.GetDevice()->CreateInputLayout(VertexPositionNormalTangentColorTexture::InputElements,
		VertexPositionNormalTangentColorTexture::InputElementCount,
		VSData_OutlineModel.GetData(), VSData_OutlineModel.GetSize(),
		m_inputOutlineLayout.GetAddressOf());
	

	//�@====================[�@�R���X�^���g�o�b�t�@�����@] 
	ZeroMemory(&m_constBuffer, sizeof(m_constBuffer));
	m_constBuffer.Usage = D3D11_USAGE_DEFAULT;
	m_constBuffer.ByteWidth = sizeof(ConstBuffer);
	m_constBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_constBuffer.CPUAccessFlags = 0;
	pSD.GetDevice()->CreateBuffer(&m_constBuffer, nullptr, &m_cbuffer);

	//�@====================[�@�[�x�X�e���V���̍쐬�@] 

	D3D11_DEPTH_STENCIL_DESC desc = {};

	// �^������鑤(�V���G�b�g���`�悳��鑤)
	//�@====================[�@�V���G�b�g�`��@] 	
	{
		desc.DepthEnable = TRUE;									// �[�x�e�X�g���s��
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;			// �[�x�o�b�t�@���X�V����
		desc.DepthFunc = D3D11_COMPARISON_ALWAYS;					// �[�x�l�ȉ��Ȃ�X�V����

		desc.StencilEnable		= TRUE;								// �X�e���V���e�X�g���s��
		desc.StencilReadMask	= 0xff;
		desc.StencilWriteMask	= D3D11_DEFAULT_STENCIL_WRITE_MASK;	// 0xff

		desc.FrontFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;		// OK�@�X�e���V���f�[�^���Q�ƒl�Ƃ���
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;			// NG�@�������Ȃ�
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;		// NG�@�������Ȃ�

		desc.BackFace = desc.FrontFace;	// ���ʂ�����
		pSD.GetDevice()->CreateDepthStencilState(&desc, m_depthStencilState_Base.ReleaseAndGetAddressOf());
	}
	//�@====================[�@�ʏ�`��@] 	
	{
		desc.DepthFunc		= D3D11_COMPARISON_EQUAL;			// �ȉ��Ȃ�ΐ�������
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;		// �������܂Ȃ�

		desc.StencilEnable = TRUE;
		desc.StencilReadMask = 0xff;
		desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;	// 0xff
		// �\��
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;			// ��������ΐ���
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		// OK�@�������Ȃ�
		desc.BackFace = desc.FrontFace;	// ���ʂ�����

		pSD.GetDevice()->CreateDepthStencilState(&desc, m_depthStencilState_Nomal.ReleaseAndGetAddressOf());
	}
	//�@====================[�@�e�`��@] 
	{
		desc.DepthFunc = D3D11_COMPARISON_NOT_EQUAL;				// ��ɍX�V
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;			// �������܂Ȃ�

		desc.StencilEnable = FALSE;
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;		// �����Ȃ�Βʂ�

		desc.StencilReadMask = 0xff;
		desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;	// 0xff

		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;	// OK�@�������Ȃ�

		desc.BackFace = desc.FrontFace;	// ���ʂ�����

		pSD.GetDevice()->CreateDepthStencilState(&desc, m_depthStencilState_Shadow.ReleaseAndGetAddressOf());
	}


	RECT rect = pSD.GetDeviceResources()->GetOutputSize();

	// �V���h�E�}�b�v�̐���
	m_shadowMapRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_shadowMapRT->SetDevice(pSD.GetDevice());
	m_shadowMapRT->SetWindow(rect);

	// �f�v�X�e�N�X�`���̍쐬
	CD3D11_TEXTURE2D_DESC depthStencilDesc(
		DXGI_FORMAT_D32_FLOAT,
		static_cast<UINT>(rect.right),
		static_cast<UINT>(rect.bottom),
		1, // This depth stencil view has only one texture.
		1, // Use a single mipmap level.
		D3D11_BIND_DEPTH_STENCIL
	);
	DX::ThrowIfFailed(pSD.GetDevice()->CreateTexture2D(
		&depthStencilDesc,
		nullptr,
		m_depathTexture2D.ReleaseAndGetAddressOf()
	));

	DX::ThrowIfFailed(pSD.GetDevice()->CreateDepthStencilView(
		m_depathTexture2D.Get(),
		nullptr,
		m_depathStencilView.ReleaseAndGetAddressOf()
	));

	// �T���v���[�̍쐬�i�V���h�E�}�b�v�p�j
	D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	sampler_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_LESS;
	pSD.GetDevice()->CreateSamplerState(&sampler_desc, m_shadowMapSampler.ReleaseAndGetAddressOf());

}

void ModelShader::CreateEffectModel()
{

	ShareData& pSD = ShareData::GetInstance();

	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(pSD.GetDevice());
	fx->SetDirectory(L"Resources/Models");

	//�@====================[�@�G�t�F�N�g�Ɏg�p���郂�f���@] 
	//�@�@|=>�@��`�^
	m_magicTrauabgukarPyram = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/MagicTrauabgukarPyram.cmo", *fx);

	//�@�@|=>�@��
	m_effectBox = GeometricPrimitive::CreateGeoSphere(pSD.GetContext());

}

void ModelShader::Update(float deltaTime)
{
	m_shaderTimer += deltaTime;
}

void ModelShader::MachineDrawShader(SimpleMath::Color color, SimpleMath::Vector4 time, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
{
	ShareData& pSD = ShareData::GetInstance();
	SimpleMath::Vector3 mousePos = InputSupport::GetInstance().GetMousePosWolrd();

	//�@====================[�@�o�b�t�@�̍쐬�@]
	ConstBuffer cbuff;
	cbuff.Time = SimpleMath::Vector4(time.x, time.y, time.z, m_shaderTimer);
	cbuff.PaintColor = color;
	cbuff.eyes = SimpleMath::Vector4(pSD.GetCamera()->GetTargetPosition());
	cbuff.LimLightColor = SimpleMath::Color(0.8f, 0.75f, 0.6f, 0.3f);

	cbuff.LightPos = m_lightPos;

	cbuff.mousePos = SimpleMath::Vector4(mousePos.x, mousePos.y, mousePos.z,0.0f);

	std::vector<SimpleMath::Vector2> crystalPos = ShareJsonData::GetInstance().GetStageData().crystalPos;

	for (int i = 0; i < 10; i++)
	{

		if (crystalPos.size() <= i)
		{
			// ���̉e�����󂯂Ȃ����W�ɐݒ肷��
			cbuff.crystalPos[i] = SimpleMath::Vector4(FLT_MAX, 0.0f, 0.0f, 0.0f);
		}
		else
		{
			cbuff.crystalPos[i] = SimpleMath::Vector4(crystalPos[i].x, 0.f, crystalPos[i].y, 0.0f);
		}
	}

	//�@====================[�@�o�b�t�@�̍X�V�@]
	//�@�@|=>�@ConstBuffer����ID3D11Buffer�ւ̕ϊ�
	pSD.GetContext()->UpdateSubresource(m_cbuffer.Get(), 0, NULL, &cbuff, 0, 0);
	//�@�@|=>�@�o�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cbuffer.Get(),};
	pSD.GetContext()->PSSetConstantBuffers(2, 1, cb);

	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	pSD.GetContext()->IASetInputLayout(m_inputLayout.Get());

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { pSD.GetCommonStates()->LinearWrap() };
	pSD.GetContext()->PSSetSamplers(0, 1, sampler);

	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = pSD.GetCommonStates()->NonPremultiplied();

	//�@�@|=> �������菈��
	pSD.GetContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//�@====================[�@�[�x�X�e���V���X�e�[�g�̐ݒ�@]
	pSD.GetContext()->OMSetDepthStencilState(pSD.GetCommonStates()->DepthDefault(), 0);

	//�@====================[�@�J�����O�F������@]
	pSD.GetContext()->RSSetState(pSD.GetCommonStates()->CullNone());

	//�@====================[�@���@�[�e�b�N�X�V�F�[�_�[��K���@]
	pSD.GetContext()->VSSetShader(GetModelMyShader_VS().Get(), nullptr, 0);

	//�@====================[�@�s�N�Z���V�F�[�_�[�ɓK���@]
	pSD.GetContext()->PSSetShader(GetMachineModelShader_PS().Get(), nullptr, 0);

	//�@====================[�@�e�N�X�`�������V�F�[�_�[�ɓo�^����@]
	pSD.GetContext()->PSSetShaderResources(0, 1, texture.GetAddressOf());

		//�@====================[�@�e�����V�F�[�_�[�ɓo�^����@]
	auto srv = GetShadowMap()->GetShaderResourceView();
	pSD.GetContext()->PSSetShaderResources(3, 1, &srv);

	//�@====================[�@�e�N�X�`���T���v���[�̐ݒ�@]
	ID3D11SamplerState* samplers[] = { pSD.GetCommonStates()->LinearWrap(), m_shadowMapSampler.Get()};
	pSD.GetContext()->PSSetSamplers(0, 2, samplers);


}

void ModelShader::ModelDrawShader(SimpleMath::Color color, SimpleMath::Vector4 time, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
{
	ShareData& pSD = ShareData::GetInstance();
	SimpleMath::Vector3 mousePos = InputSupport::GetInstance().GetMousePosWolrd();

	//�@====================[�@�o�b�t�@�̍쐬�@]
	ConstBuffer cbuff;
	cbuff.Time = SimpleMath::Vector4(time.x,time.y,time.z,m_shaderTimer);
	cbuff.PaintColor = color;
	cbuff.eyes = SimpleMath::Vector4(pSD.GetCamera()->GetTargetPosition());
	cbuff.LimLightColor = SimpleMath::Color(Colors::CadetBlue);
	cbuff.LimLightColor.A(0.3f);
	cbuff.LightPos = m_lightPos;
	cbuff.mousePos = SimpleMath::Vector4(mousePos.x, mousePos.y, mousePos.z, 0.0f);

	std::vector<SimpleMath::Vector2> crystalPos = ShareJsonData::GetInstance().GetStageData().crystalPos;

	for (int i = 0; i < 10; i++)
	{

		if (crystalPos.size() <= i)
		{
			// ���̉e�����󂯂Ȃ����W�ɐݒ肷��
			cbuff.crystalPos[i] = SimpleMath::Vector4(FLT_MAX, 0.0f, 0.0f, 0.0f);
		}
		else
		{
			cbuff.crystalPos[i] = SimpleMath::Vector4(crystalPos[i].x, 0.f, crystalPos[i].y, 0.0f);
		}
	}

	//�@====================[�@�o�b�t�@�̍X�V�@]
	//�@�@|=>�@ConstBuffer����ID3D11Buffer�ւ̕ϊ�
	pSD.GetContext()->UpdateSubresource(m_cbuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�@�@|=>�@�o�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cbuffer.Get() };
	pSD.GetContext()->PSSetConstantBuffers(2, 1, cb);

	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	pSD.GetContext()->IASetInputLayout(m_inputLayout.Get());

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { pSD.GetCommonStates()->LinearWrap() };
	pSD.GetContext()->PSSetSamplers(0, 1, sampler);

	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = pSD.GetCommonStates()->NonPremultiplied();

	//�@�@|=> �������菈��
	pSD.GetContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//�@====================[�@�[�x�X�e���V���X�e�[�g�̐ݒ�@]
	pSD.GetContext()->OMSetDepthStencilState(pSD.GetCommonStates()->DepthDefault(), 0);

	//�@====================[�@�J�����O�F������@]
	pSD.GetContext()->RSSetState(pSD.GetCommonStates()->CullNone());

	//�@====================[�@���@�[�e�b�N�X�V�F�[�_�[��K���@]
	pSD.GetContext()->VSSetShader(GetModelMyShader_VS().Get(), nullptr, 0);

	//�@====================[�@�s�N�Z���V�F�[�_�[�ɓK���@]
	pSD.GetContext()->PSSetShader(GetModelMyShader_PS().Get(), nullptr, 0);

	//�@====================[�@�e�N�X�`�������V�F�[�_�[�ɓo�^����@]
	pSD.GetContext()->PSSetShaderResources(0, 1, texture.GetAddressOf());

	//�@====================[�@�e�����V�F�[�_�[�ɓo�^����@]
	auto srv = GetShadowMap()->GetShaderResourceView();
	pSD.GetContext()->PSSetShaderResources(3, 1, &srv);

	//�@====================[�@�e�N�X�`���T���v���[�̐ݒ�@]
	ID3D11SamplerState* samplers[] = { pSD.GetCommonStates()->LinearWrap(), m_shadowMapSampler.Get()};
	pSD.GetContext()->PSSetSamplers(0, 2, samplers);

}

void ModelShader::ModelEffectShader(SimpleMath::Color color, SimpleMath::Vector4 time, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
{

	ShareData& pSD = ShareData::GetInstance();

	//�@====================[�@�o�b�t�@�̍쐬�@]
	ConstBuffer cbuff;
	cbuff.Time = time;
	cbuff.PaintColor = color;
	cbuff.eyes = SimpleMath::Vector4(pSD.GetCamera()->GetTargetPosition());
	cbuff.LimLightColor = SimpleMath::Color(Colors::Bisque);
	cbuff.LimLightColor.A(0.25f);

	//�@====================[�@�o�b�t�@�̍X�V�@]
	//�@�@|=>�@ConstBuffer����ID3D11Buffer�ւ̕ϊ�
	pSD.GetContext()->UpdateSubresource(m_cbuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�@�@|=>�@�o�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cbuffer.Get() };
	pSD.GetContext()->PSSetConstantBuffers(2, 1, cb);

	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	pSD.GetContext()->IASetInputLayout(m_inputLayout.Get());

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { pSD.GetCommonStates()->LinearWrap() };
	pSD.GetContext()->PSSetSamplers(0, 1, sampler);

	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = pSD.GetCommonStates()->NonPremultiplied();
	//�@�@|=> �������菈��
	pSD.GetContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//�@====================[�@�[�x�X�e���V���X�e�[�g�̐ݒ�@]
	pSD.GetContext()->OMSetDepthStencilState(pSD.GetCommonStates()->DepthRead(), 0);

	//�@====================[�@�J�����O�F������@]
	pSD.GetContext()->RSSetState(pSD.GetCommonStates()->CullNone());

	//�@====================[�@���@�[�e�b�N�X�V�F�[�_�[��K���@]
	pSD.GetContext()->VSSetShader(GetModelMyShader_VS().Get(), nullptr, 0);

	//�@====================[�@�s�N�Z���V�F�[�_�[��K���@]
	pSD.GetContext()->PSSetShader(m_modelEffect_PS.Get(), nullptr, 0);

	//�@====================[�@�e�N�X�`�������V�F�[�_�[�ɓo�^����@]
	pSD.GetContext()->PSSetShaderResources(0, 1, texture.GetAddressOf());

}

void ModelShader::SilhouetteShader(SimpleMath::Color color)
{
	ShareData& pSD = ShareData::GetInstance();

	//�@====================[�@�o�b�t�@�̍쐬�@]
	ConstBuffer cbuff;
	cbuff.PaintColor = SimpleMath::Color(color);

	//�@====================[�@�o�b�t�@�̍X�V�@]
	//�@�@|=>�@ConstBuffer����ID3D11Buffer�ւ̕ϊ�
	pSD.GetContext()->UpdateSubresource(m_cbuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�@�@|=>�@�o�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cbuffer.Get() };
	pSD.GetContext()->PSSetConstantBuffers(2, 1, cb);

	//�@====================[�@�o�b�t�@�̍X�V�@]
	//�@�@|=>�@ConstBuffer����ID3D11Buffer�ւ̕ϊ�
	pSD.GetContext()->UpdateSubresource(m_cbuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { pSD.GetCommonStates()->LinearWrap() };
	pSD.GetContext()->PSSetSamplers(0, 1, sampler);

	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = pSD.GetCommonStates()->NonPremultiplied();
	//�@�@|=> �������菈��
	pSD.GetContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	pSD.GetContext()->IASetInputLayout(m_inputOutlineLayout.Get());

	//�@====================[�@�[�x�X�e���V���X�e�[�g�̐ݒ�@](���̂̔w��ɂ��Ă��`�悷�鏈��)
	pSD.GetContext()->OMSetDepthStencilState(GetStencilShadow().Get(), 1);

	//�@====================[�@�J�����O�F������@]
	pSD.GetContext()->RSSetState(pSD.GetCommonStates()->CullNone());

	//�@====================[�@���@�[�e�b�N�X�V�F�[�_�[��K���@]
	pSD.GetContext()->VSSetShader(GetModelMyShader_VS().Get(), nullptr, 0);

	//�@====================[�@���@�[�e�b�N�X�V�F�[�_�[��K���@]
	//pSD.GetContext()->VSSetShader(m_modelOutLineShader_VS.Get(), nullptr, 0);

	//�@====================[�@�s�N�Z���V�F�[�_�[��K���@]
	pSD.GetContext()->PSSetShader(GetModelShadowShader().Get(), nullptr, 0);

}

void ModelShader::ToransparentShader()
{
	ShareData& pSD = ShareData::GetInstance();

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { pSD.GetCommonStates()->LinearWrap() };
	pSD.GetContext()->PSSetSamplers(0, 1, sampler);
	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = pSD.GetCommonStates()->NonPremultiplied();

	//�@�@|=> �������菈��
	pSD.GetContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//�@====================[�@�[�x�X�e���V���X�e�[�g�̐ݒ�@]
	pSD.GetContext()->OMSetDepthStencilState(pSD.GetCommonStates()->DepthNone(), 1);

	//�@====================[�@�J�����O�F������@]
	pSD.GetContext()->RSSetState(pSD.GetCommonStates()->CullNone());

	//�@====================[�@�s�N�Z���V�F�[�_�[��K���@]
	pSD.GetContext()->PSSetShader(GetModelTransparentShader().Get(), nullptr, 0);

}

void ModelShader::ShadowModelDraw(bool outlineFlag)
{

	ShareData& pSD = ShareData::GetInstance();
	SimpleMath::Vector3 mousePos = InputSupport::GetInstance().GetMousePosWolrd();

	//�@====================[�@�o�b�t�@�̍쐬�@]
	ConstBuffer cbuff;
	cbuff.Time = SimpleMath::Vector4(outlineFlag, 0.0f, 0.0f, 0.0f);
	cbuff.PaintColor = SimpleMath::Color();
	cbuff.eyes = SimpleMath::Vector4(pSD.GetCamera()->GetTargetPosition());
	cbuff.LimLightColor = SimpleMath::Color();
	cbuff.LightPos = m_lightPos;
	cbuff.mousePos = SimpleMath::Vector4(mousePos.x, mousePos.y, mousePos.z, 0.0f);

	cbuff.view = pSD.GetView();
	cbuff.proj = pSD.GetProjection();

	pSD.GetContext()->UpdateSubresource(m_cbuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�@�@|=>�@�o�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cbuffer.Get() };
	pSD.GetContext()->PSSetConstantBuffers(2, 1, cb);

	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	pSD.GetContext()->IASetInputLayout(m_inputLayout.Get());

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { pSD.GetCommonStates()->LinearWrap() };
	pSD.GetContext()->PSSetSamplers(0, 1, sampler);

	//�@====================[�@�[�x�X�e���V���X�e�[�g�̐ݒ�@]
	pSD.GetContext()->OMSetDepthStencilState(pSD.GetCommonStates()->DepthDefault(), 0);

	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = pSD.GetCommonStates()->NonPremultiplied();
	//�@�@|=> �������菈��
	pSD.GetContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//�@====================[�@���@�[�e�b�N�X�V�F�[�_�[��K���@]
	pSD.GetContext()->VSSetShader(GetModelMyShader_VS().Get(), nullptr, 0);

	//�@====================[�@�s�N�Z���V�F�[�_�[�ɓK���@]
	pSD.GetContext()->PSSetShader(m_depathShadowShader_PS.Get(), nullptr, 0);

}

void ModelShader::DrawAuraEffect(float time, SimpleMath::Vector3 pos, SimpleMath::Vector3 rage, SimpleMath::Color color)
{
	ShareData& pSD = ShareData::GetInstance();

	SimpleMath::Matrix textBox = SimpleMath::Matrix::CreateScale(rage);
	textBox *= SimpleMath::Matrix::CreateTranslation(pos);

	m_effectBox->Draw(textBox, pSD.GetView(), pSD.GetProjection(), Colors::White, nullptr, false, [&]()
		{
			ModelShader::GetInstance().ModelEffectShader(SimpleMath::Color(color),
			SimpleMath::Vector4(0.0f, 0.0f, 0.0f, time),
			SpriteLoder::GetInstance().GetAuraBase());

	pSD.GetContext()->PSSetShaderResources(1, 1, SpriteLoder::GetInstance().GetAuraMask().GetAddressOf());

		});
}
