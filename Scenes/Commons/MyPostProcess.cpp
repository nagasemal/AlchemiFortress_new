#include "pch.h"
#include "MyPostProcess.h"

#include "NecromaLib/GameData/BinaryFile.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/SpriteLoder.h"

#include <stdio.h>
#include <wchar.h>

const std::vector<D3D11_INPUT_ELEMENT_DESC> MyPostProcess::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

MyPostProcess::MyPostProcess():
	m_blerVal(),
	m_chromaticVal()
{
}

MyPostProcess::~MyPostProcess()
{
}

void MyPostProcess::CreateShader()
{
	auto device = ShareData::GetInstance().GetDevice();
	auto context = ShareData::GetInstance().GetContext();
	auto resouce = ShareData::GetInstance().GetDeviceResources();
	RECT windowSize = resouce->GetOutputSize();

	std::wstring wFirstPath = L"Resources/Shader/PostProcess";

	const wchar_t* wLastPath[3] = { L"_VS.cso" , L"_GS.cso" , L"_PS.cso" };

	std::wstring wfilePath[3] = { wFirstPath + wLastPath[0],
								  wFirstPath + wLastPath[1],
								  wFirstPath + wLastPath[2] };

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

	//�@====================[�@�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@�����@]
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);
	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<DirectX::CommonStates>(device);


}

void MyPostProcess::Render(ID3D11ShaderResourceView* const* offscreenTex, ID3D11ShaderResourceView* const* depthTex)
{
	auto context = ShareData::GetInstance().GetContext();
	auto device = ShareData::GetInstance().GetDeviceResources();
	int width = device->GetOutputSize().right;
	int height = device->GetOutputSize().bottom;

	// ���_���(�|���S���̂S���_�̍��W���j
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(SimpleMath::Vector3(0.0f,0.0f,0.0f),SimpleMath::Vector4::One,SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = SimpleMath::Matrix::Identity;
	cbuff.matProj = SimpleMath::Matrix::Identity;
	cbuff.matWorld = SimpleMath::Matrix::Identity;
	cbuff.Diffuse = SimpleMath::Vector4((float)width, (float)height, m_chromaticVal, m_blerVal);

	ShareData::GetInstance().GetCamera()->GetViewMatrix();

	auto camera = ShareData::GetInstance().GetCamera();

	SimpleMath::Viewport viewport = SimpleMath::Viewport();

	SimpleMath::Vector3 eyespos = camera->GetTargetPosition();

	cbuff.eyes = SimpleMath::Vector4(eyespos.x, eyespos.y,eyespos.z,0.0);

	//�@====================[�@�o�b�t�@�̍X�V�@]
	//�@�@|=>�@ConstBuffer����ID3D11Buffer�ւ̕ϊ�
	context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�@====================[�@�V�F�[�_�[�Ƀo�b�t�@��n���@]
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//�@�@|=> �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//�@====================[�@�[�x�o�b�t�@�ɏ������݁@]
	context->OMSetDepthStencilState(m_states->DepthNone(), 0);

	//�@====================[�@�J�����O�F������@]
	context->RSSetState(m_states->CullNone());

	//�@====================[�@�V�F�[�_���Z�b�g�@]
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//�@====================[�@�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^�@]
	context->PSSetShaderResources(0, 1, offscreenTex);

	context->PSSetShaderResources(1, 1, depthTex);

	context->PSSetShaderResources(2, 1, SpriteLoder::GetInstance().GetRampTexture().GetAddressOf());

	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	context->IASetInputLayout(m_inputLayout.Get());

	//�@====================[�@�|���S����`��@]
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//�@====================[�@�V�F�[�_�̓o�^�������@]
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}
