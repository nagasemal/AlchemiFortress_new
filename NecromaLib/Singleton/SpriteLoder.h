//--------------------------------------------------------------------------------------
// File: SpriteLoder.h
//
// �X�v���C�g����ۑ�����V���O���g���N���X
// �J��Ԃ��g�����̂�A�V�[�����܂����Ŏg�����̂͒�`���Ďg���₷�����Ă���
// 
// Date: 2023.6.19
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once

class SpriteLoder
{
public:

	// UI�A�C�R���̎��
	enum UIICON_TYPE : int
	{

		CLOCK = 0,
		EXPRANATION = 1,
		STOP = 2,
		START = 3,
		SOUND = 4,
		SE = 5,
		SYSTEMSE = 6,
		REPAIR = 7,
		LVUP = 8,
		MACHINE = 9,
		DISMATIONG = 10,
		SPEED_1 = 11,
		SPEED_2 = 12,
		SPEED_3 = 13,
		SPEED_4 = 14,
		CANCEL = 15,

		NUM

	};

	// �e�N�X�`�����
	struct TextureData
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> tex = nullptr;
		int width = 0;
		int height = 0;
	};

public:
	~SpriteLoder() = default;

	SpriteLoder(const SpriteLoder&) = delete;
	SpriteLoder& operator=(const SpriteLoder&) = delete;

	static void Create();
	static void Destroy();

	static SpriteLoder& GetInstance() { return *instance; }

	// �ǂݍ���
	void Loading();

	// ���
	void Finalize();

	// �I���{�b�N�X�̃e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSelectBoxTexture() { return m_selectBoxTexture; }
	const wchar_t* GetSelectBoxTexturePath() { return L"Resources/Textures/log.png"; }

	// �B���p�I���{�b�N�X�̃e�N�X�`����n��
	TextureData GetAlchemiButtonTexture() { return m_alchemiSelectTexture; }

	// �B���p�I���{�b�N�X�̔w�ʃe�N�X�`����n��
	TextureData GetAlchemiButtonBackTexture() { return m_alchemiBackTexture; }

	// �B���p�I���{�b�N�X�̖��e�N�X�`����n��
	TextureData GetAlchemiArrowTexture() { return m_alchemiArrowTexture; }

	// �}�V��UI�̃J�[�\���e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetMachineUICursorTexture() { return m_machineUICursorTexture; }

	// �}�E�X�̃e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetMouseTexture() { return m_mouseTexture; }

	// �����A�C�R����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetElementTexture() { return m_elementTextures;}
	const wchar_t* GetElementTexturePath() { return L"Resources/Textures/elementTex.png";}

	// �Q�[���X�^�[�g�̕�����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetGameStartTexture() { return m_gameStartTexture; }


	// �G�l�~�[�̖��O��n��
	// ����:128�@�c��:28
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetEnemyNameTexture() { return m_enemyNameTextures; }
	const wchar_t* GetEnemyNameTexturePath() { return L"Resources/Textures/EnemyNames.png"; }

	// �u���v��n��
	// ����:28�@�c��:28
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetLetterTexture() { return m_letterTexture; }
	const wchar_t* GetLetterTexturePath() { return L"Resources/Textures/wo.png"; }

	// �~�b�V�������e��n��
	// ����:112�@�c��:28
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetMissionTexture() { return m_missionTexture; }
	const wchar_t* GetMissionTexturePath() { return L"Resources/Textures/MissionText.png"; }

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetMissionLabelTexture() { return m_missionLabelTexture; }
	const wchar_t* GetMissionLabelTexturePath() { return L"Resources/Textures/MissionLabel.png"; }

	// �u�����v�����A�C�R����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetManufacturingTexture() { return m_ManufacturingTexture; }
	const wchar_t* GetManufacturingTexturePath() { return L"Resources/Textures/Seizou.png"; }

	// �X�e�[�W�N���A�A���s�������A�C�R����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetStageClearTextTexture() { return m_stageClearTextTexture; }
	const wchar_t* GetStageClearTextTexturePath() { return L"Resources/Textures/SuccessFailureText.png"; }

	// �f�U�C�������e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetNumberTexture() { return m_NumberTexture; }
	const wchar_t* GetNumberTexturePath() { return L"Resources/Textures/number.png"; }

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSymbolTexture() { return m_SymbolTexture; }
	const wchar_t* GetSymbolTexturePath() { return L"Resources/Textures/symbol.png"; }

	// �^�C�g�����S�e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTitleLogo() { return m_titleLogo; }
	const wchar_t* GetTitleLogoPath() { return L"Resources/Textures/TitleLogo.png"; }

	// �v���C�V�[���ŕ`�悷�鑀����������e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetExplanationTextTexture() { return m_explanationTextTexture; }
	const wchar_t* GetExplanationTextTexturePath() { return L"Resources/Textures/Explanation_Text.png"; }

	// ���U���g�ŕ`�悷�镶���e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetResultTextTexture() { return m_resultTextTexture; }
	const wchar_t* GetResultTextTexturePath() { return L"Resources/Textures/Result_Text.png"; }

	// UI�A�C�R���e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetUIIcons() { return m_uiIcons; }
	const wchar_t* GetUIIconsPath() { return L"Resources/Textures/UIIcons.png"; }

	// �G�l�~�[��ԃA�C�R���e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetEnemyStateTexture() { return m_enemyStateTexture; }

	// ���A�C�R���e�N�X�`����n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetUIArrow() { return m_uiArrow; }
	const wchar_t* GetUIArrowPath() { return L"Resources/Textures/Arrow.png"; }

	// ���[���摜��n��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetRule() { return m_rule; }
	const wchar_t* GetRulePath() { return L"Resources/Textures/MagicRule.png"; }

	// �}�V���Ɏg���m�[�}���}�b�v�̉摜��n���܂�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetNormalMap(int element) { return m_machineNormalMap[element]; }
	const wchar_t* GetNormalMapPath() { return L"Resources/Textures/NormalMap.png"; }

	// �}�V���Ɏg���e�N�X�`���̉摜��n���܂�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetMachineTextuer(int element) { return m_machineTexture[element]; }

	// ���̃m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetFiledNormalMap() { return m_fieldNormalMap; }
	// ���̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetFiledTexture() { return m_fieldTexture; }

	// ��[�x�[�X]�̃m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTowerBaseNormalMap() { return m_towerNormalMap; }
	// ��[�x�[�X]�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTowerBaseTexture() { return m_towerTexture; }

	// ��[��]�̃m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTowerPillarNormalMap() { return m_towerPillarNormalMap; }
	// ��[��]�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTowerPillarTexture() { return m_towerPillarTexture; }

	// �����v�e�N�X�`��(�~��)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetRampTexture() { return m_rampTexture; }


	// 0~3
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetMagicRule(int index) { return m_transition[index]; }

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetPleaseMouseButton() { return m_pleaseMouseButtonText; }

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetAuraBase() { return m_auraBaseTexture; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetAuraMask() { return m_auraMaskTexture; }

	// �X�J�C�X�t�B�A
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSkySphereTexture() { return m_skySphereTexture; }

	// �Q�[�W:�w�i
	TextureData GetBaseGage() { return m_baseGageTex; }

	// �Q�[�W:���g
	TextureData GetMainGage() { return m_mainGageTex; }

	// �}�V��:UI�A�C�R��
	TextureData GetMachineIconTexture() { return m_machineIconTexture; }
	// �}�V��:���O
	TextureData GetMachineNameTexture() { return m_machineNameTextures; }

	/// <summary>
	/// ���@�w�e�N�X�`����n��
	/// </summary>
	/// <param name="machineType">�}�V��ID</param>
	/// <returns></returns>
	TextureData GetMachineMagicCircleTexture(int machineType) { return m_magicCircleTexture[machineType]; }

	/// <summary>
	/// �}�V��UI�e�N�X�`����n��
	/// </summary>
	/// <param name="machineType">�}�V��ID</param>
	/// <returns></returns>
	TextureData GetMachineUIText(int machineType) { return m_machineUIText[machineType]; }

	// UI�p�̃e�L�X�g
	TextureData GetUIText() { return m_uiText; }

	// �}�V���������������̖��A�C�R��
	TextureData GetInstallationMode() { return m_installationMode; }

	// �A���t�@�x�b�g�e�N�X�`����Ԃ��܂�
	TextureData GetAlphabet() { return m_alphabet; }

	TextureData GetClickMousePointer() { return m_clickMousePointer; }

	TextureData GetBottomLabel() { return m_bottomLabel; }

	TextureData GetNormalParticle() { return m_particle; }

	// �}�V���̈�s������
	TextureData GetMachineSimpleText() { return m_machineSimpleText; }

	// �摜��ǂݍ���
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> LoadingPngFile(const wchar_t* filename, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& spriteResource);

	// �摜��ǂݍ���
	TextureData LoadingPngFileData(const wchar_t* filename, TextureData& textuerData);

private:
	SpriteLoder();
	static SpriteLoder* instance;

	//�@�I���{�b�N�X�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectBoxTexture;

	//�@�Q�[���X�^�[�g�̕����e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_gameStartTexture;

	//  �G�l�~�[�A�C�R���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_enemyStateTexture;


	// �B���p�I���{�b�N�X�̃e�N�X�`��
	TextureData m_alchemiSelectTexture;

	// �B���p�I���{�b�N�X�̃J�o�[�e�N�X�`��
	TextureData m_alchemiBackTexture;

	// �B���p���e�N�X�`��
	TextureData m_alchemiArrowTexture;

	// �}�V��UI�̃J�[�\���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_machineUICursorTexture;

	// �}�E�X�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_mouseTexture;

	//�@�����A�C�R���̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_elementTextures;

	// �G�l�~�[�̖��O�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_enemyNameTextures;

	// �����̕����e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ManufacturingTexture;


	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_explanationTextTexture;

	// ���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_letterTexture;

	// �~�b�V���������e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_missionTexture;

	// �~�b�V�����̃��x���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_missionLabelTexture;

	// �f�U�C�������e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_NumberTexture;

	// �L���e�N�X�`��( / , : )
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SymbolTexture;

	// ���U���g��ʂɂĎg�p���镶���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resultTextTexture;

	// �X�e�[�W�N���A,���s�����������e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stageClearTextTexture;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleLogo;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_uiIcons;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_uiArrow;

	// ���[���摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_rule;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_transition[4];

	// PleaseMouseButton�̃e�L�X�g�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pleaseMouseButtonText;

	// �m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_machineNormalMap[5];
	// �}�V���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_machineTexture[5];

	// �~���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_rampTexture;

	// ���̃m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fieldNormalMap;
	// ���̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fieldTexture;

	// ��[�x�[�X]�̃m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_towerNormalMap;
	// ��[�x�[�X]�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_towerTexture;

	// ��[��]�̃m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_towerPillarNormalMap;
	// ��[��]�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_towerPillarTexture;

	// �X�J�C�X�t�B�A�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_skySphereTexture;

	// �G�t�F�N�g�p�̃e�N�X�`��(�I�[���\��)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_auraBaseTexture;
	// �G�t�F�N�g�p�̃e�N�X�`��(�I�[���\��)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_auraMaskTexture;


	//�@�}�V���̖��O�̃e�N�X�`��
	TextureData m_machineNameTextures;
	// �}�V���A�C�R��
	TextureData m_machineIconTexture;

	// �ݒu���[�h�e�N�X�`��
	TextureData m_installationMode;

	// �}�V���̐�����(��s)�e�N�X�`��
	TextureData m_machineSimpleText;

	// ���@�w�̃e�N�X�`��
	TextureData m_magicCircleTexture[6 + 1];

	// �Q�[�W(�w�i)
	TextureData m_baseGageTex;

	// �Q�[�W(���g)
	TextureData m_mainGageTex;

	// �}�V��UI�̐����e�L�X�g
	TextureData m_machineUIText[6];

	// UI�̐����e�L�X�g
	TextureData m_uiText;

	// �A���t�@�x�b�g�e�N�X�`��
	TextureData m_alphabet;

	// �N���b�N�ʒu������
	TextureData m_clickMousePointer;

	// ��ʉ��̃��x��
	TextureData m_bottomLabel;

	TextureData m_particle;
};