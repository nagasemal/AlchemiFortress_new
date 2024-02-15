//--------------------------------------------------------------------------------------
// File: ShareJsonData.h
//
// json�œǂݍ��񂾐��l��n��
//
// ���e��
// �E�o���b�g�̃p�����[�^
// �E�}�V���̃p�����[�^
// �E�G�l�~�[�̃p�����[�^
// �E�Q�[���Ɋւ���Œ�̕ϐ�
// �E�X�e�[�W���
// �E�X�e�[�W�N���A���@
// �EUI�̈ʒu���
// �E2D�p�[�e�B�N���̏��
// 
// Date: 2023.7.21
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once

#include "NecromaLib/GameData/JsonLoder.h"

class ShareJsonData
{
public:
	~ShareJsonData()								= default;

	ShareJsonData(const ShareJsonData&)				= delete;
	ShareJsonData& operator=(const ShareJsonData&)	= delete;

	static void Create();
	static void Destroy();

	static ShareJsonData& GetInstance() { return *instance; }

	// �o���b�g��json�t�@�C����ǂݍ���
	void LoadingJsonFile_Bullet();

	// �}�V����json�t�@�C����ǂݍ���
	void LoadingJsonFile_Machine();

	// �G�l�~�[��json�t�@�C����ǂݍ���
	void LoadingJsonFile_Enemy();

	// �Q�[���Ɋւ���Œ�̕ϐ�(���\�[�X�̍ő�l�Ȃ�)��ǂݍ���
	void LoadingJsonFile_GameParameter();

	// �X�e�[�W��json�t�@�C����ǂݍ���
	void LoadingJsonFile_Stage(int number, int wave);

	// �N���A�f�[�^��json�t�@�C����ǂݍ���
	void LoadingJsonFile_ClearData(int number);

	// UI�̃��C�A�E�g���擾����
	void LoadingUIData(std::string pathName,std::string tagName);

	// �p�[�e�B�N��2D�̃f�[�^���擾����
	void LoadingParticle2D(std::string pathName);

	// �G���h���X���[�h���̂ݎg�p(���̃X�e�[�W���e��ς���)
	void SetEndlessStageData(Stage_Data data);

public:

	// �����ɑΉ������o���b�g�̃p�����[�^��n��
	const Bullet_Data GetBulletData(ELEMENT element);

	// �}�V���^�C�v�ɑΉ������}�V���̃p�����[�^��n��
	const Machine_Data GetMachineData(MACHINE_TYPE type);

	// �G�l�~�[�^�C�v�ɑΉ������G�l�~�[�̃p�����[�^��n��
	const Enemy_Data GetEnemyData(ENEMY_TYPE type);

	// �X�e�[�W�̃f�[�^��n��
	const Stage_Data GetStageData();

	// �X�e�[�W�̃N���A�f�[�^��n��
	const Stage_ClearData GetClearData();

	// �Q�[�����̃p�����[�^��n��
	const Game_Parameter GetGameParameter();

	// UI�̔z�u��n��
	const UI_Data GetUIData(std::string tagName);

	// �p�[�e�B�N��2D�̃f�[�^��n��
	const Particle2D_Pram GetParticle2DPram(std::string tagName);

	// �X�e�[�W�f�[�^�̒��g��S�ď���(�������̈�̈�����h������)
	void StageDataCleanUP();

	// �G�������g�ɕR�Â��F�����擾
	SimpleMath::Color GetElementColor(ELEMENT element);


private:
	ShareJsonData();
	static ShareJsonData* instance;

	// Attacker���J��o���e�̃p�����[�^
	Bullet_Data m_bulletData[ELEMENT::Num];

	// �e�}�V���̃f�[�^
	Machine_Data m_machineData[MACHINE_TYPE::NUM];

	// �e�G�l�~�[�̃f�[�^
	Enemy_Data m_enemyData[ENEMY_TYPE::ENEMY_NUM];

	// �ǂݍ��񂾃X�e�[�W�̃f�[�^(�S�Ă�ǂݍ��ނƃ����������������ׁA�����ǂݍ��ޕ������̗p)
	Stage_Data m_stageData;

	// �ǂݍ��񂾃X�e�[�W�̃N���A���f�[�^
	Stage_ClearData m_clearData;

	// �Q�[�����p�����[�^
	Game_Parameter m_gameParam;

	// 2D�p�[�e�B�N���̏����������z��
	std::unordered_map<std::string, Particle2D_Pram> m_particlePrams;

	// UI�̈ʒu�傫�����̑������������z��
	std::unordered_map<std::string, UI_Data> m_uiDatas;

};