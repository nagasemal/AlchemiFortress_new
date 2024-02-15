#include "pch.h"
#include "BaseLv.h"

#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/SpriteLoder.h"

#include "Scenes/PlayScene/UI/Number.h"
#include "Scenes/PlayScene/Field/FieldObjectManager.h"

#define SECOND_COLOR SimpleMath::Color(0.2f,0.2f,0.8f,1.0f);

BaseLv::BaseLv()
{
	auto device = ShareData::GetInstance().GetDevice();

	ShareJsonData& pSJD = ShareJsonData::GetInstance();

	//�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);

	//�@====================[�@�}�V��UI�̏����擾�@]
	UI_Data uiData = pSJD.GetUIData("GaugeBaseLv");

	auto windowSize = ShareData::GetInstance().GetDeviceResources()->GetOutputSize();
	Create(L"Resources/Textures/MagicCircle/Attacker.png");
	LoadShaderFile(L"BaseLv");

	m_baseLvRender	= std::make_unique<Number>(uiData.pos, uiData.rage * uiData.option["NUMBER_RAGE"]);
	m_baseLvRender	->SetColor(SimpleMath::Color(Colors::Black));

	m_expRedio = 0.0f;
}

BaseLv::~BaseLv()
{
}

void BaseLv::Update(FieldObjectManager* pFieldObjectManager)
{

	auto pPlayerBase = pFieldObjectManager->GetPlayerBase();

	//�@====================[�@���_�̌���Lv��o�^����@]
	m_baseLvRender->SetNumber(pPlayerBase->GetBaseLv());

	//�@====================[�@���_�o���l�̊����v�Z�@]
	m_expRedio = (float)pPlayerBase->GetExp() / (float)pPlayerBase->GetNextLvEXP();

}

void BaseLv::Render(float alphaVal)
{

	auto context = ShareData::GetInstance().GetContext();
	auto windowSize = ShareData::GetInstance().GetDeviceResources()->GetOutputSize();

	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	UI_Data uiData = pSJD.GetUIData("GaugeBaseLv");

	// ���_���
	// Position.xy	:�g�k�p�X�P�[��
	// Position.z	:�A���J�[�^�C�v(0�`8)�̐����Ŏw��
	// Color.xy�@	:�A���J�[���W(�s�N�Z���w��:1280 �~720)
	// Color.zw		:�摜�T�C�Y
	// Tex.xy		:�E�B���h�E�T�C�Y�i�o�b�t�@�������B������͖��g�p�j
	VertexPositionColorTexture vertex[1] = {
		VertexPositionColorTexture(SimpleMath::Vector3(uiData.rage.x, uiData.rage.y, static_cast<float>(MIDDLE_CENTER))
		, SimpleMath::Vector4(uiData.pos.x,uiData.pos.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight))
		, SimpleMath::Vector2(m_expRedio,0.8f))
	};

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.windowSize	= SimpleMath::Vector4(static_cast<float>(windowSize.right), static_cast<float>(windowSize.bottom), 1, 1);
	cbuff.base_color	= SimpleMath::Color(1.0f, 1.0f, 1.0f, alphaVal);
	cbuff.second_color	= SimpleMath::Color(0.0f, 1.0f, 1.0f, alphaVal);

	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context			->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	context			->VSSetConstantBuffers(0, 1, cb);
	context			->GSSetConstantBuffers(0, 1, cb);
	context			->PSSetConstantBuffers(0, 1, cb);

	AdvanceRender();

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context			->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	context			->PSSetShaderResources(1, 1, SpriteLoder::GetInstance().GetMagicRule(0).GetAddressOf());

	// �|���S����`��
	m_batch			->Begin();
	m_batch			->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch			->End();

	//�V�F�[�_�̓o�^���������Ă���
	context			->VSSetShader(nullptr, nullptr, 0);
	context			->GSSetShader(nullptr, nullptr, 0);
	context			->PSSetShader(nullptr, nullptr, 0);

	// ���_Lv�̕`��
	m_baseLvRender	->SetPosition(uiData.pos);
	m_baseLvRender	->SetRage(uiData.rage * uiData.option["NUMBER_RAGE"]);
	m_baseLvRender	->SetColor(SimpleMath::Color(m_baseLvRender->GetColorRGB(), alphaVal));
	m_baseLvRender	->Render();

}
