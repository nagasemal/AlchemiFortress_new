#include "pch.h"
#include "NecromaLib/GameData/SpriteCutter.h"
#include "MachineSelect.h"
#include "NecromaLib/GameData/ScreenToWorld.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/InputSupport.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/ModelShader.h"
#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/GameData/Easing.h"
#include "NecromaLib/Singleton/ShareJsonData.h"

#define SELECTBOX_RAGE		{ 1.3f,1.3f }
#define ALCHEMI_RAGE		(0.5f,0.5f)
#define ALCHEMI_POS_SHIFT	40

#define IMAGE_WIGHT			64
#define IMAGE_HEIGHT		64

#define BOX_DISTANS_X		68
#define BOX_DISTANS_Y		80

#define ALPHA_VAL 0.7f
#define SCALE_VAL 0.35f

//�@====================[�@���@�w�̉�]���x�@]
#define MAGICCIRCLE_SPEED 0.5f

MachineSelect::MachineSelect():
	m_hitMouseFlag(),
	m_onMouseFlag(),
	m_manufacturingFlag(),
	m_selectMachineType(MACHINE_TYPE::NONE),
	m_changeColorFlag(),
	m_colorChangeTime(),
	m_tutorialLockFlag(true)
{
}

MachineSelect::~MachineSelect()
{
}

void MachineSelect::Initialize()
{
	m_data.rage = SELECTBOX_RAGE;

	m_machineBox = std::make_unique<SelectionBox>(m_data.pos, m_data.rage);
	m_machineBox->Initialize();
	m_machineBox->SetColor((SimpleMath::Color)Colors::White);

	m_colorChangeTime = 0;

	RECT rect = RECT();
	rect.right = 120;
	rect.bottom = 120;

	//�@====================[�@�B���{�^���̏����擾�@]
	m_selectionAlchemi = std::make_unique<SelectionBox>(m_data.pos, m_data.rage * 0.5f);
	m_selectionAlchemi->Initialize();

}

void MachineSelect::Update()
{
	auto datas = DataManager::GetInstance();
	auto pSJD = &ShareJsonData::GetInstance();
	auto pINP = &InputSupport::GetInstance();

	float deltaTime = DeltaTime::GetInstance().GetNomalDeltaTime();

	m_manufacturingFlag = false;

	m_machineBox->SetSavePos(m_data.pos);


	// �v�f���琻���{�^���������ꂽ������󂯎�� ���\�[�X������Ȃ��ꍇ�͒e��
	m_machineBox->SetActiveFlag(
		((datas->GetNowMP() - pSJD->GetMachineData(m_selectMachineType).alchemi_mp >= 0 &&
		  datas->GetNowCrystal() - pSJD->GetMachineData(m_selectMachineType).alchemi_crystal >= 0) && m_tutorialLockFlag));

	// ���X�g�̒�����I�΂ꂽ
	m_machineBox->HitMouse(true);

	if (m_machineBox->ClickMouse())
	{
		m_onMouseFlag = !m_onMouseFlag;
	}

	//�@====================[�@�B���{�^���ɐG�ꂽ�ۂ̏����@]
	if (m_selectionAlchemi->HitMouse(true)) 					m_magicCircleAnim += deltaTime;
	else 	m_magicCircleAnim -= deltaTime;

}

void MachineSelect::Draw()
{
}

void MachineSelect::Finalize()
{
}

void MachineSelect::DisplayObject()
{
	ShareData& pSD = ShareData::GetInstance();
	SpriteLoder& pSL = SpriteLoder::GetInstance();
	auto pSB = pSD.GetSpriteBatch();

	//�@====================[�@���@�w����]������ϐ��@]
	float easingValRotate = Easing::EaseOutQuint(0.0f, XMConvertToRadians(360.0f), m_magicCircleAnim);

	//�@====================[�@�B���{�^���̔w�ʕ`��@]
	SpriteLoder::TextureData alchemiTexture_Back = pSL.GetAlchemiButtonBackTexture();
	m_selectionAlchemi->DrawUI(alchemiTexture_Back.tex.Get(), easingValRotate);


	pSB->Begin(DirectX::SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	// �摜�̃T�C�Y
	RECT srcRect = { 0, 0, IMAGE_WIGHT, IMAGE_HEIGHT };

	// ���O�̐F
	SimpleMath::Color color = m_machineBox->GetColor();

	// ����BOX (�}�V��UI��z�u����ӏ�)
	SpriteLoder::TextureData texData = pSL.GetMachineIconTexture();

	srcRect = SpriteCutter(texData.width / (MACHINE_TYPE::NUM - 1), texData.height, m_selectMachineType - 1, 0);

	pSB->Draw(texData.tex.Get(), m_data.pos, &srcRect, color, 0.0f, 
		DirectX::XMFLOAT2(static_cast<float>((texData.width / (MACHINE_TYPE::NUM - 1)) / 2),
						  static_cast<float>(texData.height / 2)), SCALE_VAL);
	
	pSB->End();


	//�@====================[�@�B���{�^���̕`��@]
	float colorElement = 0.5f + (float)m_machineBox->GetActiveFlag();
	color = SimpleMath::Color(colorElement, colorElement, colorElement, 1.0f);

	SpriteLoder::TextureData alchemiTexture = pSL.GetAlchemiButtonTexture();
	m_selectionAlchemi->SetPos(GetPos());
	m_selectionAlchemi->SetColor(color);
	m_selectionAlchemi->DrawUI(alchemiTexture.tex.Get(), 0.0f);
	m_selectionAlchemi->SetRect(RECT{ 0,0,alchemiTexture.width,alchemiTexture.height }); 

	//�@====================[�@�B���{�^�����@�w�̕`��@]
	pSB->Begin(DirectX::SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());
	
	SpriteLoder::TextureData textureData = pSL.GetMachineMagicCircleTexture(m_selectMachineType);
	srcRect = { 0,0,textureData.width,textureData.height };
	pSB->Draw(textureData.tex.Get(), m_selectionAlchemi->GetPos(),
		&srcRect, SimpleMath::Color(1.0f, colorElement, colorElement, m_magicCircleAnim * MAGICCIRCLE_SPEED), easingValRotate,
		SimpleMath::Vector2(textureData.width / 2.0f, textureData.height / 2.0f), m_magicCircleAnim * 0.1f);

	pSB->End();
}

void MachineSelect::LeftRender()
{
	ShareData& pSD = ShareData::GetInstance();
	SpriteLoder& pSL = SpriteLoder::GetInstance();
	auto pSB = pSD.GetSpriteBatch();

	pSB->Begin(DirectX::SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	// �摜�̃T�C�Y
	RECT srcRect = { 0, 0, IMAGE_WIGHT, IMAGE_HEIGHT };

	// ���O�̐F
	SimpleMath::Color color = m_machineBox->GetColor();

	color.A(ALPHA_VAL);

	// ����BOX (�}�V��UI��z�u����ӏ�)
	SpriteLoder::TextureData texData = pSL.GetMachineIconTexture();

	srcRect = SpriteCutter(texData.width / (MACHINE_TYPE::NUM - 1), texData.height, m_selectMachineType - 1, 0);

	pSB->Draw(texData.tex.Get(), m_data.pos + SimpleMath::Vector2(160.0f,0.0f), &srcRect, color, 0.0f,
		DirectX::XMFLOAT2(static_cast<float>((texData.width / (MACHINE_TYPE::NUM - 1)) / 2),
			static_cast<float>(texData.height / 2)), SCALE_VAL);

	pSB->End();
}

void MachineSelect::RightRender()
{
	ShareData& pSD = ShareData::GetInstance();
	SpriteLoder& pSL = SpriteLoder::GetInstance();
	auto pSB = pSD.GetSpriteBatch();

	pSB->Begin(DirectX::SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	// �摜�̃T�C�Y
	RECT srcRect = { 0, 0, IMAGE_WIGHT, IMAGE_HEIGHT };

	// ���O�̐F
	SimpleMath::Color color = m_machineBox->GetColor();

	color.A(ALPHA_VAL);

	// ����BOX (�}�V��UI��z�u����ӏ�)
	SpriteLoder::TextureData texData = pSL.GetMachineIconTexture();

	srcRect = SpriteCutter(texData.width / (MACHINE_TYPE::NUM - 1), texData.height, m_selectMachineType - 1, 0);

	pSB->Draw(texData.tex.Get(), m_data.pos - SimpleMath::Vector2(160.0f, 0.0f), &srcRect, color, 0.0f,
		DirectX::XMFLOAT2(static_cast<float>((texData.width / (MACHINE_TYPE::NUM - 1)) / 2),
			static_cast<float>(texData.height / 2)), SCALE_VAL);

	pSB->End();
}

bool MachineSelect::SelectUIFlag()
{
	return m_onMouseFlag;
}

