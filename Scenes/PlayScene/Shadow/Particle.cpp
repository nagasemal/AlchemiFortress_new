#include "pch.h"
#include "Particle.h"
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include "NecromaLib/GameData/BinaryFile.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/DeltaTime.h"

#include <algorithm>
#include <random>

// �C���v�b�g���C�A�E�g
const std::vector<D3D11_INPUT_ELEMENT_DESC> Particle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR"	,	0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,	sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

Particle::Particle(EFFECT_TYPE type) :
	m_particleNum(1),
	m_particleSpawnTime(0),
	m_colFlag(),
	m_timer(),
	m_billboard(),
	m_proj(),
	m_view(),
	m_effectType(type)
{

}

Particle::~Particle()
{
}

void Particle::LoadTexture(const wchar_t* path)
{
	auto device = ShareData::GetInstance().GetDevice();

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(device, path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture.push_back(texture);
}

void Particle::CreateBillboard()
{

	auto camera = ShareData::GetInstance().GetCamera();

	m_billboard =
		SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero,
			camera->GetEyePosition() - camera->GetTargetPosition(), camera->GetUpVector());

	SimpleMath::Matrix rot = SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	m_cameraPosition = camera->GetEyePosition();
	m_cameraTarget = camera->GetTargetPosition();
	m_billboard = rot * m_billboard;
}

void Particle::Initialize(const wchar_t* path)
{
	auto device = ShareData::GetInstance().GetDevice();

	//�V�F�[�_�[�̍쐬
	CreateShader();

	std::wstring wFirstPath = L"Resources/Textures/";
	wFirstPath += path;
	wFirstPath += L".png";

	//�摜�̓ǂݍ���
	LoadTexture(wFirstPath.c_str());

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique <DirectX::PrimitiveBatch <DirectX::VertexPositionColorTexture>> (ShareData::GetInstance().GetContext());

	m_states = std::make_unique<DirectX::CommonStates>(device);

}

void Particle::Update(SimpleMath::Vector3 pos, bool flag,SimpleMath::Color color)
{
	// flase�Ȃ�ʂ��Ȃ�
	if (!flag) return ;

	CreateBillboard();

	// ���Ԃ������琶�����s��
	if (m_timer > m_particleSpawnTime)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			m_particleUtility.push_back(CreateEffectParam(m_effectType,pos,color));
			m_timer = 0.0f;
		}
	}
}

bool Particle::OnShot(SimpleMath::Vector3 pos, bool flag, SimpleMath::Color color)
{
	// flase�Ȃ�ʂ��Ȃ�
	if (!flag) return false;

	CreateBillboard();

	// ��������������
	for (int i = 0; i < m_particleNum; i++)
	{
		m_particleUtility.push_back(CreateEffectParam(m_effectType, pos, color));
	}

	return true;

}

void Particle::UpdateParticle()
{
	m_timer += DeltaTime::GetInstance().GetDeltaTime();

	//Particle�̗��̍X�V�������s��
	for (std::list<ParticleUtility>::iterator ite = m_particleUtility.begin(); ite != m_particleUtility.end(); ite++)
	{
		// �q�N���X����false�ŏ���
		if (!(ite)->Update())
		{
			ite = m_particleUtility.erase(ite);
			if (ite == m_particleUtility.end()) break;
		}
	}
}

void Particle::Render()
{
	auto context = ShareData::GetInstance().GetContext();
	auto view = ShareData::GetInstance().GetView();
	auto proj = ShareData::GetInstance().GetProjection();

	// ���_���(�|���S���̂S���_�̍��W���j
	SimpleMath::Vector3 cameraDir = m_cameraTarget - m_cameraPosition;
	cameraDir.Normalize();

	m_particleUtility.sort(
		[&](ParticleUtility lhs,ParticleUtility  rhs)
		{
			//�J�������ʂ̋����Ń\�[�g
			return cameraDir.Dot(lhs.GetPosition() - m_cameraPosition) > cameraDir.Dot(rhs.GetPosition() - m_cameraPosition);
		});

	//�o�^����Ă��钸�_�����Z�b�g
	m_vertices.clear();

	for (auto& li : m_particleUtility)
	{
		if (cameraDir.Dot(li.GetPosition() - m_cameraPosition) < 0.0f) {
			//���ς��}�C�i�X�̏ꍇ�̓J�����̌��Ȃ̂ŕ\������K�v�Ȃ�
			continue;
		}

		VertexPositionColorTexture vPCT = VertexPositionColorTexture();

		vPCT.position = XMFLOAT3(li.GetPosition());
		vPCT.color = XMFLOAT4(li.GetNowColor());
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//�\������_���Ȃ��ꍇ�͕`����I���
	if (m_vertices.empty())
	{
		return;
	}

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView	= view.Transpose();
	cbuff.matProj	= proj.Transpose();
	cbuff.matWorld	= m_billboard.Transpose();
	cbuff.Diffuse	= SimpleMath::Vector4(1, 1, 1, 1);

	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//�@====================[�@�摜�p�T���v���[�̓o�^�@]
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�@====================[�@�������`��w��@]
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);

	//�@====================[�@�J�����O�F������@]
	context->RSSetState(m_states->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//�@====================[�@�C���v�b�g���C�A�E�g�̓o�^�@]
	context->IASetInputLayout(m_inputLayout.Get());

	//// �|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());
	m_batch->End();

	//�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

	m_particleUtility.sort(
		[&](ParticleUtility lhs, ParticleUtility  rhs)
		{
			//�J�������ʂ̋����Ń\�[�g
			return cameraDir.Dot(lhs.GetPosition() - m_cameraPosition) > cameraDir.Dot(rhs.GetPosition() - m_cameraPosition);
		});
}

void Particle::CreateShader()
{
	auto device = ShareData::GetInstance().GetDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shader/Shadow_VS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shader/Shadow_GS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shader/Shadow_PS.cso");

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

ParticleUtility Particle::CreateEffectParam(EFFECT_TYPE type, SimpleMath::Vector3 pos, SimpleMath::Color color)
{

	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> dist(0, DirectX::XM_2PI);
	float range = 0.5f;
	float rand = static_cast<float>(dist(engine));

	ParticleUtility pU(
		1.0f,																			// ��������
		SimpleMath::Vector3::Zero,														// ����W
		SimpleMath::Vector3::Zero,														// ���x
		SimpleMath::Vector3::Zero,														// �����x
		SimpleMath::Vector3(0.7f, 0.7f, 0.7f), SimpleMath::Vector3::Zero,				// �����X�P�[���A�ŏI�X�P�[��
		SimpleMath::Color(color), SimpleMath::Color(0.f, 0.f, 0.f, 0.f)					// �����J���[�A�ŏI�J���[
	);

	SimpleMath::Vector3 vectol = pU.GetPosition() - pos;


	switch (type)
	{
	case Particle::HIT_BULLET:

		// �g�U����G�t�F�N�g

		pU.SetLife(0.8f);

		pU.SetPosition(SimpleMath::Vector3(
			pos.x + range * cosf(rand),
			pos.y + range * sinf(rand),
			pos.z + range * cosf(rand)));

		pU.SetVelocity(SimpleMath::Vector3(0.0f,0.8f,0.0f));

		pU.SetEndColor({color.R(),color.G(),color.B(),0.0f});

		m_particleNum = 5;

		break;
	case Particle::SPAWN_ENEMY:
		pU.SetPosition(SimpleMath::Vector3(pos.x + range * cosf(rand),
			pos.y,
			pos.z + range * sinf(rand)));

		pU.SetVelocity(SimpleMath::Vector3(0.0f, 0.8f, 0.0f));

		m_particleNum = 10;
		break;

	case Particle::DELETE_ENEMY:

		pU.SetPosition(SimpleMath::Vector3(pos.x + range * cosf(rand),
										   pos.y + range * rand,
										   pos.z + range * sinf(rand)));

		pU.SetVelocity(SimpleMath::Vector3(0.0f, 0.8f, 0.0f));
		pU.SetAccele(SimpleMath::Vector3(0.0f, -0.025f, 0.0f));

		m_particleNum = 10;
		break;

	case Particle::MACHINE_LVUP:

		// �g�U����G�t�F�N�g

		pU.SetLife(1.2f);

		pU.SetPosition(SimpleMath::Vector3(
			pos.x + range * cosf(rand),
			pos.y + range * sinf(rand),
			pos.z + range * cosf(rand)));

		pU.SetVelocity(SimpleMath::Vector3(cosf(rand), sinf(rand), cosf(rand)));

		pU.SetEndColor({ color.R(),color.G(),color.B(),0.0f });

		m_particleNum = 5;

		break;

	case Particle::MACHINE_BREAK:

		break;

	case Particle::MACHINE_SPAWN:

		// �e����G�t�F�N�g
		pU.SetLife(1.6f);

		pU.SetPosition(SimpleMath::Vector3(pos.x + 0.75f * cosf(rand),
			pos.y,
			pos.z + 0.75f * sinf(rand)));

		vectol = pU.GetPosition() - pos;
		vectol.Normalize();

		pU.SetStartScale(SimpleMath::Vector3(0.4f, 0.4f, 0.4f));
		pU.SetVelocity(SimpleMath::Vector3(sinf(vectol.x), 6.0f, cosf(vectol.z)));
		pU.SetAccele(SimpleMath::Vector3(0.0f, -7.0f, 0.0f));

		pU.SetEndColor({ color.R(),color.G(),color.B(),0.0f });

		m_particleNum = 10;

		break;

	case Particle::CLICK:

		pU.SetLife(0.8f);

		pU.SetPosition(SimpleMath::Vector3(
			pos.x + range * cosf(rand),
			pos.y + range * sinf(rand),
			pos.z + range * cosf(rand)));



		pU.SetVelocity(SimpleMath::Vector3(0.0f, sinf(rand), sinf(rand)));

		pU.SetRad(SimpleMath::Vector3(0.0f,1.0f,0.0f));

		pU.SetStartColor({ color.R(),color.G(),color.B(),1.0f });
		pU.SetEndColor({ color.R(),color.G(),color.B(),0.0f });

		m_particleNum = 5;

		break;

	case Particle::MINING_EFFECT:
		// �������G�t�F�N�g
		pU.SetLife(0.7f);

		pU.SetPosition(SimpleMath::Vector3( pos.x, pos.y + 2.0f , pos.z ));
		pU.SetStartScale(SimpleMath::Vector3(0.8f, 0.8f, 0.8f));
		pU.SetVelocity(SimpleMath::Vector3(0.0f, 6.0f, 0.0f));
		pU.SetAccele(SimpleMath::Vector3(0.0f, -7.0f, 0.0f));

		pU.SetEndColor({ color.R(),color.G(),color.B(),0.0f });

		m_particleNum = 1;


		break;

	case Particle::RECOVERY_EFFECT:

		// �o��Ȃ���L�k����
		pU.SetLife(1.6f);

		pU.SetPosition(SimpleMath::Vector3(pos.x + 0.75f * cosf(rand),
			pos.y,
			pos.z + 0.75f * sinf(rand)));

		pU.SetStartScale(SimpleMath::Vector3(0.6f, 0.6f, 0.6f));
		pU.SetEndScale(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		pU.SetVelocity(SimpleMath::Vector3(0.0f, 6.0f, 0.0f));
		pU.SetAccele(SimpleMath::Vector3(0.0f, -3.0f, 0.0f));

		pU.SetEndColor({ color.R(),color.G(),color.B(),0.0f });

		m_particleNum = 5;

		break;

	case Particle::DEFENSE_EFFECT:


		pU.SetLife(1.2f);

		pU.SetPosition(SimpleMath::Vector3(pos.x,
			pos.y + range * sinf(rand),
			pos.z));

		vectol = pU.GetPosition().Cross(pos);
		vectol.Normalize();

		pU.SetStartScale(SimpleMath::Vector3(0.6f, 0.6f, 0.6f));
		pU.SetEndScale(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		pU.SetVelocity(SimpleMath::Vector3(vectol.x + sinf(vectol.x), 0.0f, vectol.z + cosf(vectol.z)));
		pU.SetAccele(SimpleMath::Vector3(2.0f, 0.0f, 0.0f));

		pU.SetEndColor({ color.R(),color.G(),color.B(),0.0f });

		m_particleNum = 10;


		break;

	case Particle::BULLET_LINE:

		pU.SetLife(1.2f);
		pU.SetPosition(SimpleMath::Vector3(pos.x,pos.y + 1.0f,pos.z));
		pU.SetStartScale(SimpleMath::Vector3(0.6f, 0.6f, 0.6f));
		pU.SetEndScale(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		pU.SetEndColor({ color.R(),color.G(),color.B(),0.0f });

		m_particleNum = 1;

		break;

	default:
		break;
	}

	return pU;
}
