#include "pch.h"
#include "MagicCircle.h"
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include "NecromaLib/GameData/BinaryFile.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/Singleton/ModelShader.h"

#define RAD_90 1.5708f

/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> MagicCircle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

MagicCircle::MagicCircle() :
	m_proj(),
	m_world_MagicCircle(),
	m_world_Effect(),
	m_view(),
	m_animationTime()
{
}

MagicCircle::~MagicCircle()
{
}

void MagicCircle::Initialize()
{
	auto device = ShareData::GetInstance().GetDevice();

	//�V�F�[�_�[�̍쐬
	CreateShader();

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(ShareData::GetInstance().GetContext());
	m_states = std::make_unique <DirectX::CommonStates >(device);
}

void MagicCircle::Update()
{
}

void MagicCircle::CreateMagicCircle(SimpleMath::Vector3 pos,float r, SimpleMath::Color color)
{
	// �S�ď���
	m_vertices.clear();

	color.A(0.55f);
	m_vertices.push_back({ pos,color,SimpleMath::Vector2(r * 2.5f,0.0f) });

	// ���@�w�G�t�F�N�g�p
	m_world_Effect = SimpleMath::Matrix::CreateScale(r, 1.0f, r);
	m_world_Effect *= SimpleMath::Matrix::CreateTranslation(pos.x,pos.y - r,pos.z);

}

void MagicCircle::DeleteMagicCircle()
{
	m_animationTime = 0.0f;
	// �S�ď���
	m_vertices.clear();
}

void MagicCircle::CreateWorld()
{

	m_world_MagicCircle = SimpleMath::Matrix::Identity;

	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateRotationX(RAD_90);
	
	// ��ɉE���ɉ�]
	rot *= SimpleMath::Matrix::CreateRotationY(0.25f * m_animationTime);

	m_animationTime += DeltaTime::GetInstance().GetDeltaTime();

	m_world_MagicCircle *= rot * m_world_MagicCircle;


	m_world_Effect = SimpleMath::Matrix::CreateRotationY(0.25f * m_animationTime) * m_world_Effect;


}


void MagicCircle::Render(int magicCircleNumber)
{
	auto context = ShareData::GetInstance().GetContext();
	auto view = ShareData::GetInstance().GetView();
	auto proj = ShareData::GetInstance().GetProjection();

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.m_matView = view.Transpose();
	cbuff.m_matProj = proj.Transpose();
	cbuff.m_matWorld = m_world_MagicCircle.Transpose();
	cbuff.m_diffuse = SimpleMath::Vector4(m_animationTime, 1, 1, m_animationTime);

	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap()};
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

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, SpriteLoder::GetInstance().GetMachineMagicCircleTexture(magicCircleNumber).tex.GetAddressOf());
	context->PSSetShaderResources(1, 1, SpriteLoder::GetInstance().GetRule().GetAddressOf());
	context->PSSetShaderResources(2, 1, SpriteLoder::GetInstance().GetAuraBase().GetAddressOf());

	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();

	// �v�f����
	for (auto& vertexs : m_vertices)
	{
		m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertexs, 1);
	}

	m_batch->End();

	//�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

	//�@====================[�@�J�����O�F������@]
	//ModelShader::GetInstance().GetMagicTrauabgukarPyram()->Draw(context, *common, m_world_Effect, view,proj, false, [&]
	//	{
	//		//�@====================[�@�J�����O�F������@]
	//		context->RSSetState(m_states->CullNone());
	//		ModelShader::GetInstance().ModelEffectShader(
	//			SimpleMath::Color(1.0f,1.0f,1.0f,1.0f),
	//			SimpleMath::Vector4(1, 1, 1, m_animationTime),
	//			SpriteLoder::GetInstance().GetAuraBase().Get());
	//		context->PSSetShaderResources(1, 1, SpriteLoder::GetInstance().GetAuraMask().GetAddressOf());
	//	});

}

void MagicCircle::Finalize()
{
}

void MagicCircle::CreateShader()
{
	auto device = ShareData::GetInstance().GetDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shader/MagicCircle_VS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shader/MagicCircle_GS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shader/MagicCircle_PS.cso");

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

	//�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);
}
