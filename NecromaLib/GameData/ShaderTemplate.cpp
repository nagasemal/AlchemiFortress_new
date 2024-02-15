#include "pch.h"
#include "ShaderTemplate.h"
#include <WICTextureLoader.h>
#include "NecromaLib/GameData/BinaryFile.h"
#include "NecromaLib/Singleton/ShareData.h"

#include <stdio.h>
#include <wchar.h>

const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderTemplate::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


ShaderTemplate::ShaderTemplate()
	: m_windowHeight(0)
	, m_windowWidth(0)
	, m_textureHeight(0)
	, m_textureWidth(0)
	, m_texture(nullptr)
	, m_res(nullptr)
	, m_scale(SimpleMath::Vector2::One)
	, m_position(SimpleMath::Vector2::Zero)
	, m_color(1.0f, 1.0f, 1.0f, 1.0f)
	, m_rotationMatrix()
{
}

ShaderTemplate::~ShaderTemplate()
{
}

void ShaderTemplate::LoadTexture(const wchar_t* path)
{
	auto device = ShareData::GetInstance().GetDevice();

	DirectX::CreateWICTextureFromFile(device, path, m_res.ReleaseAndGetAddressOf(), m_texture.ReleaseAndGetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

void ShaderTemplate::Create(const wchar_t* path)
{

	auto device = ShareData::GetInstance().GetDevice();
	auto context = ShareData::GetInstance().GetContext();
	auto resouce = ShareData::GetInstance().GetDeviceResources();
	RECT windowSize = resouce->GetOutputSize();

	m_position = { static_cast<float>(windowSize.right / 2),static_cast<float>(windowSize.bottom / 2) };
	m_baseScale = m_scale = { 1.0f,1.0f };

	//�摜�̓ǂݍ���
	LoadTexture(path);

	SetWindowSize(windowSize.right, windowSize.bottom);

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);

	m_states = std::make_unique<DirectX::CommonStates>(device);

}

void ShaderTemplate::LoadShaderFile(const wchar_t* path)
{
	auto device = ShareData::GetInstance().GetDevice();

	std::wstring wFirstPath = L"Resources/Shader/";
	wFirstPath += path;

	const wchar_t* wLastPath[3] = { L"_VS.cso" , L"_GS.cso" , L"_PS.cso" };

	std::wstring wfilePath[3] = { wFirstPath + wLastPath[0],
								  wFirstPath + wLastPath[1],
								  wFirstPath + wLastPath[2]};

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(wfilePath[0].c_str());
	BinaryFile GSData = BinaryFile::LoadFile(wfilePath[1].c_str());
	BinaryFile PSData = BinaryFile::LoadFile(wfilePath[2].c_str());

	//�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
}

void ShaderTemplate::AdvanceRender()
{
	auto context = ShareData::GetInstance().GetContext();
	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { m_states->LinearClamp() };
	context->PSSetSamplers(0, 1, sampler);

	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//�@====================[�@�J�����O�F������@]
	context->RSSetState(m_states->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	context->IASetInputLayout(m_inputLayout.Get());
}