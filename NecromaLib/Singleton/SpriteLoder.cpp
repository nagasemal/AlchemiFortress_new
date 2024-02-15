#include "pch.h"
#include "SpriteLoder.h"
#include "ShareData.h"
#include <WICTextureLoader.h>

#include "NecromaLib/GameData/CommonStruct.h"

SpriteLoder* SpriteLoder::instance = nullptr;

void SpriteLoder::Loading()
{

	// �I���{�b�N�X�̃e�N�X�`��
	LoadingPngFile(L"Resources/Textures/log.png", m_selectBoxTexture);

	// �B���p�I���{�^���̎擾
	LoadingPngFileData(L"Resources/Textures/AlchemiButton.png",m_alchemiSelectTexture);

	// �B���p�I���{�^���̔w�ʂ̎擾
	LoadingPngFileData(L"Resources/Textures/AlchemiButtonBack.png", m_alchemiBackTexture);

	// �B���p���{�^���̎擾
	LoadingPngFileData(L"Resources/Textures/AlchemiButtonArrow.png", m_alchemiArrowTexture);

	LoadingPngFileData(L"Resources/Textures/BottomLabel.png", m_bottomLabel);

	LoadingPngFile(L"Resources/Textures/SelectMachineUICursor.png", m_machineUICursorTexture);

	LoadingPngFile(L"Resources/Textures/EnemyIcon.png", m_enemyStateTexture);

	// �}�E�X�e�N�X�`���̎擾
	LoadingPngFile(L"Resources/Textures/Mouse.png", m_mouseTexture);
	
	LoadingPngFile(L"Resources/Textures/GameStart.png", m_gameStartTexture);

	//�@====================[�@�}�V���̃m�[�}���}�b�v�擾�@]
	LoadingPngFile(L"Resources/Textures/NormalMap.png", m_machineNormalMap[0]);
	LoadingPngFile(L"Resources/Textures/ModelTexture/Fire_NormalMap.png", m_machineNormalMap[1]);
	LoadingPngFile(L"Resources/Textures/ModelTexture/Ice_NormalMap.png", m_machineNormalMap[2]);
	LoadingPngFile(L"Resources/Textures/ModelTexture/Wind_NormalMap.png", m_machineNormalMap[3]);
	LoadingPngFile(L"Resources/Textures/ModelTexture/Earth_NormalMap.png", m_machineNormalMap[4]);

	//�@====================[�@�}�V���̃e�N�X�`���擾�@]
	LoadingPngFile(L"Resources/Textures/NormalMap.png", m_machineTexture[0]);
	LoadingPngFile(L"Resources/Textures/ModelTexture/Fire_Texture.png", m_machineTexture[1]);
	LoadingPngFile(L"Resources/Textures/ModelTexture/Ice_Texture.png", m_machineTexture[2]);
	LoadingPngFile(L"Resources/Textures/ModelTexture/Wind_Texture.png", m_machineTexture[3]);
	LoadingPngFile(L"Resources/Textures/ModelTexture/Earth_Texture.png", m_machineTexture[4]);

	//�@====================[�@�t�B�[���h�̃m�[�}���}�b�v�擾�@]
	LoadingPngFile(L"Resources/Textures/ModelTexture/StornTile_Nomal.png", m_fieldNormalMap);
	//�@====================[�@�t�B�[���h�̃e�N�X�`���擾�@]
	LoadingPngFile(L"Resources/Textures/ModelTexture/StornTile.png", m_fieldTexture);

	//�@====================[�@��[�x�[�X]�̃m�[�}���}�b�v�擾�@]
	LoadingPngFile(L"Resources/Textures/ModelTexture/Diriseki_Nomal.png", m_towerNormalMap);
	//�@====================[�@��[�x�[�X]�̃e�N�X�`���擾�@]
	LoadingPngFile(L"Resources/Textures/ModelTexture/Diriseki.jpg", m_towerTexture);

	//�@====================[�@��[��]�̃m�[�}���}�b�v�擾�@]
	LoadingPngFile(L"Resources/Textures/ModelTexture/Pillar_Nomal.png", m_towerPillarNormalMap);
	//�@====================[�@��[��]�̃e�N�X�`���擾�@]
	LoadingPngFile(L"Resources/Textures/ModelTexture/Pillar.jpg", m_towerPillarTexture);



	LoadingPngFile(L"Resources/Textures/Effect/Aura.png", m_auraBaseTexture);
	LoadingPngFile(L"Resources/Textures/Effect/Flare.png", m_auraMaskTexture);

	// �e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/elementTex.png",
		nullptr,
		m_elementTextures.ReleaseAndGetAddressOf()
	);

	// �G�l�~�[�̖��O�̃e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/EnemyNames.png",
		nullptr,
		m_enemyNameTextures.ReleaseAndGetAddressOf()
	);

	// �����̕����e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/Seizou.png",
		nullptr,
		m_ManufacturingTexture.ReleaseAndGetAddressOf()
	);

	// �����e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/wo.png",
		nullptr,
		m_letterTexture.ReleaseAndGetAddressOf()
	);

	// �����e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/MissionText.png",
		nullptr,
		m_missionTexture.ReleaseAndGetAddressOf()
	);

	// ���U���g�ɂĕ`�悷�镶���e�N�X�`��
	LoadingPngFile(L"Resources/Textures/Result_Text.png", m_resultTextTexture);

	LoadingPngFile(L"Resources/Textures/SuccessFailureText.png", m_stageClearTextTexture);

	// ���x���e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/MissionLabel.png",
		nullptr,
		m_missionLabelTexture.ReleaseAndGetAddressOf()
	);
	
	// �����e�N�X�`��
	LoadingPngFile(L"Resources/Textures/number_1.png",m_NumberTexture);

	// �L���e�N�X�`��
	LoadingPngFile(L"Resources/Textures/symbol.png", m_SymbolTexture);

	// �^�C�g�����S�e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/TitleLogo.png",
		nullptr,
		m_titleLogo.ReleaseAndGetAddressOf()
	);

	LoadingPngFile(L"Resources/Textures/Explanation_Text.png", m_explanationTextTexture);

	// UI�A�C�R���e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/UIIcons.png",
		nullptr,
		m_uiIcons.ReleaseAndGetAddressOf()
	);

	// UI�A�C�R���e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/Arrow.png",
		nullptr,
		m_uiArrow.ReleaseAndGetAddressOf()
	);

	// ���[���摜�e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		L"Resources/Textures/Rule.png",
		nullptr,
		m_rule.ReleaseAndGetAddressOf()
	);

	LoadingPngFile(L"Resources/Textures/Rule/Right_Transition.png", m_transition[0]);
	LoadingPngFile(L"Resources/Textures/Rule/UP_Transition.png", m_transition[1]);
	LoadingPngFile(L"Resources/Textures/Rule/109.png", m_transition[2]);
	LoadingPngFile(L"Resources/Textures/Rule/156.png", m_transition[3]);

	LoadingPngFile(L"Resources/Textures/TitleText.png", m_pleaseMouseButtonText);

	LoadingPngFile(L"Resources/Textures/SkySphereTexture.png", m_skySphereTexture);

	LoadingPngFile(L"Resources/Textures/RampTexture.png", m_rampTexture);


	//�@====================[�@�}�V���̖��@�w�@]
	{
		LoadingPngFileData(L"Resources/Textures/MagicCircle/MajicCircle.png", m_magicCircleTexture[MACHINE_TYPE::NONE]);

		for (int i = 1; i < MACHINE_TYPE::NUM; i++)
		{
			// ���f�����O�z��ɉ������t�@�C���p�X��ǂݍ���
			std::wostringstream oss;
			oss << L"Resources/Textures/MagicCircle/" << ChangeData::ChangeMachineString((MACHINE_TYPE)i).c_str() << ".png";

			LoadingPngFileData(oss.str().c_str(), m_magicCircleTexture[i]);
		}

		LoadingPngFileData(L"Resources/Textures/MagicCircle/EnemySpawn.png", m_magicCircleTexture[6]);
	}

	//�@====================[�@�}�V��UI�̃e�L�X�g�@]
	{

		LoadingPngFileData(L"Resources/Textures/UIText/AttackerText.png", m_machineUIText[MACHINE_TYPE::NONE]);

		for (int i = 1; i < MACHINE_TYPE::NUM; i++)
		{
			// ���f�����O�z��ɉ������t�@�C���p�X��ǂݍ���
			std::wostringstream oss;
			oss << L"Resources/Textures/UIText/" << ChangeData::ChangeMachineString((MACHINE_TYPE)i).c_str() << "Text.png";

			LoadingPngFileData(oss.str().c_str(), m_machineUIText[i]);
		}

	}

	//�@====================[�@�A���t�@�x�b�g�̃e�N�X�`���@]
	LoadingPngFileData(L"Resources/Textures/UIText/Alphabet.png", m_alphabet);

	//�@====================[�@UI�e�N�X�`���@]
	LoadingPngFileData(L"Resources/Textures/UIText/UIText.png", m_uiText);

	//�@====================[�@�Q�[�W�@]
	//�@�@|=>�@�w�i
	LoadingPngFileData(L"Resources/Textures/Gauge_base.png", m_baseGageTex);
	//�@�@|=>�@���g
	LoadingPngFileData(L"Resources/Textures/Gauge_main.png", m_mainGageTex);

	//�@====================[�@�}�V��UI�A�C�R���@]
	LoadingPngFileData(L"Resources/Textures/MachineIcons.png", m_machineIconTexture);

	//�@====================[�@�}�V�����O�e�N�X�`���@]
	LoadingPngFileData(L"Resources/Textures/MachineNames.png", m_machineNameTextures);

	//�@====================[�@���A�C�R���@]
	LoadingPngFileData(L"Resources/Textures/ClickArrow.png", m_machineSelectArrow);

	//�@====================[�@�N���b�N�|�C���^�[�@]
	LoadingPngFileData(L"Resources/Textures/ClickPointer.png", m_clickMousePointer);

	//�@====================[�@�p�[�e�B�N���@]
	LoadingPngFileData(L"Resources/Textures/Particle.png", m_particle);

}

void SpriteLoder::Finalize()
{
	// ���
	m_selectBoxTexture.Reset();
	m_elementTextures.Reset();
	m_ManufacturingTexture.Reset();
	m_NumberTexture.Reset();
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SpriteLoder::LoadingPngFile
(const wchar_t* filename, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& spriteResource)
{
		DirectX::CreateWICTextureFromFile(
			ShareData::GetInstance().GetDevice(),
			filename,
			nullptr,
			spriteResource.ReleaseAndGetAddressOf()
		);

	return spriteResource;
}

SpriteLoder::TextureData SpriteLoder::LoadingPngFileData(const wchar_t* filename, TextureData& textuerData)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> res;

	DirectX::CreateWICTextureFromFile(
		ShareData::GetInstance().GetDevice(),
		filename,
		res.ReleaseAndGetAddressOf(),
		textuerData.tex.ReleaseAndGetAddressOf()
	);


	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(res.As(&tex));

	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	textuerData.width = desc.Width;
	textuerData.height = desc.Height;

	return textuerData;
}

SpriteLoder::SpriteLoder()
{

}

void SpriteLoder::Create()
{
	if (instance == nullptr)
	{
		instance = new SpriteLoder;
	}
}

void SpriteLoder::Destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}