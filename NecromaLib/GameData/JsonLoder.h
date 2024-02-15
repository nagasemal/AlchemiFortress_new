//--------------------------------------------------------------------------------------
// File: JsonLoder.h
//
// Json��ǂݏ�������N���X
// 
// Date: 2023.7.21
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include <string>
#include <unordered_map>

#include "NecromaLib/GameData/CommonStruct.h"
#include "NecromaLib/GameData/Particle_2D.h"

//	json�t�@�C������ǂ݂������f�[�^���i�[����\����
struct Bullet_Data
{
	std::string element = "Nomal";	//  ����
	float str = 0.0f;		//	�U����
	float speed = 0.0f;		//	�U���̑��x
	float span = 0.0f;		//�@�U���̊Ԋu
	float life = 0.0f;		//�@�e�̐�������
	int lossMp = 0;		//  ���炷����
};

struct Machine_Data
{
	std::string element = "Nomal";		// ����
	int lv = 0;		// Lv
	int hp = 0;		// Hp
	float multiplier_hp = 0.0f;		// ���x���A�b�v����HP�̏㏸��
	float effect_rage	= 0.0f;		// ���ʔ͈�
	float effect_rage_rate	= 0.0f;		// ���x���A�b�v���̌��ʔ͈͏㏸��
	float multiplier_effect	= 0.0f;		// ���x���A�b�v���̌��ʔ͈͂̏㏸��
	int alchemi_mp			= 0;		// �������Ɏg��MP�̗�
	int alchemi_crystal		= 0;		// �������Ɏg�����̗͂�
	int repea_crystal		= 0;		// �C�U���Ɏg���N���X�^���̗�
	int lvUp_crystal		= 0;		// ���x���A�b�v���Ɏg���N���X�^���̗�
	int dismantling_crystal = 0;		// �󂵂��ۂɓ�����N���X�^���̗�
	float effect_value		= 0.0f;		// ���ʒl
};

struct Enemy_MoveData
{
	std::string moveName = "Standerd";
	float delay = 0.0f;
	float time	= 0.0f;
	float value = 0.0f;
};

struct Enemy_Data
{
	ELEMENT element = ELEMENT::NOMAL;
	ENEMY_TYPE type = ENEMY_TYPE::ENMEY_NONE;
	std::string moveType = "ALL";
	int hp		= 1;
	float power = 1.0f;
	int exp		= 1;
	SimpleMath::Color color = SimpleMath::Color();

	std::vector<Enemy_MoveData> moveData;
};

// �X�e�[�W�̃N���A�������i�[
struct Stage_Condition
{
	std::string condition = "None";
	int value	 = -1;		//�ڕW�l
	int progress = 0;		//�i�s�x
};

struct Stage_Resource
{
	int mp = 400;
	int crystal = 215;
	int hp = 50;
	int exp = 0;
	int lv = 1;
	int attacker = 0;
	int upper = 0;
	int deffencer = 0;
	int mining = 0;
	int recovery = 0;
};

// �X�e�[�W���N���A�����}�V���̏����i�[
struct Stage_Machine
{
	MACHINE_TYPE type = MACHINE_TYPE::NONE;
	ELEMENT element = ELEMENT::NOMAL;
	int lv = 1;
	int number = 0;
};

// �G�l�~�[���o�������鎞��
struct Enemys_Spawn
{
	ENEMY_TYPE type = ENEMY_TYPE::ENMEY_NONE;	// �G�l�~�[�̃^�C�v
	float	spawnTime = 0.0f;					// ��������܂ł̎���
	SimpleMath::Vector3 spawnPos = SimpleMath::Vector3();	// �����ꏊ
	int		lv = 1;								// �o������G�l�~�[�̃��x��
	bool	condition = false;					// �������J�n����^�C�~���O
};

struct Tutorial_Status
{
	int type;		// �`���[�g���A���̏������e
	int val;		// �������e�ɑ΂��ĕt�����鐔�l
};



struct Stage_Data
{
	std::vector<Stage_Condition>		condition[MISSION_TYPE::MISSION_NUM];			// �X�e�[�W�̃N���A����

	std::vector<Enemys_Spawn>			enemys_Spawn;				// �G�l�~�[�̏o�����

	Stage_Resource						resource;					// ���߂��珊�����Ă��郊�\�[�X�Q
	std::vector<Stage_Machine>			machine;					// ���߂���ݒu����Ă���}�V���Q

	std::vector<SimpleMath::Vector2>	crystalPos;					// �N���X�^���̔ԍ�

	std::vector<Tutorial_Status>		tutorial;					// �`���[�g���A���ԍ�
	bool								lastWave = true;		// ���ɃX�e�[�W���T���Ă��邩	
};

struct Stage_ClearData
{
	std::vector<Stage_Machine> machines;		// �N���A�����}�V��
	int clearTime = 0;						// �N���A�܂łɂ�����������
	int num = 0;						// �����
};

struct UI_Data
{
	SimpleMath::Vector2 pos;							// �|�W�V����
	SimpleMath::Vector2 rage;							// �傫��
	std::unordered_map<std::string, float> option;		// �ǉ��L�q�̒l
	std::vector<Keyboard::Keys> key;						// �L�[�R�[�h
};

struct Game_Parameter
{
	float rotateSpeed = 0.5f;		// �}�V�������_�����X�s�[�h

	int stage_Max = 1;		// �X�e�[�W�̍ő吔

	int baseLV_MAX = 9;		// �ő�LV

	int baseHp_Max = 0;		// ���_HP�̍ő�LV�̒l

	int mp_Max = 0;		// MP���\�[�X�̍ő�LV�̒l

	int crystal_Max = 0;		// �N���X�^�����\�[�X�̍ő�LV�̒l

	int needExp = 0;		// �K�v�Ȍo���l�̗�
	int needExp_Growthrate = 0;		// �K�v�Ȍo���l�̗ʂ̏オ�蕝

	float transparent_time = 0;		// �����������J�n����b��
	float transparent_val = 0;			// ���������̐��l
};

struct Particle2D_Pram
{
	ParticleUtility_2D praticleData;
	ParticleUtility_2D random_Max;

	int num = 0;
	int maxNum = 0;

	float rage = 0.0f;
	float maxRage = 0.0f;

	float time = 0.0f;

	std::vector<SimpleMath::Vector2> points;				// �����ӏ��̊g��
	float linerSpeed	= 0.0f;
	float maxLinerSpeed = 0.0f;

	std::string tag;		// �p�[�e�B�N���������^�O
	Particle_2D::ParticleDrawType	drawType = Particle_2D::ParticleDrawType::DrawNone;
	Particle_2D::ParticleLinerType	linerType = Particle_2D::ParticleLinerType::LinerNone;		// �|�C���g�Ԃ̐����̎d��
	Particle_2D::ParticleMoveType	velocityType = Particle_2D::ParticleMoveType::MoveNone;		// ���x�̉��Z���@
	Particle_2D::ParticleMoveType	acceleType = Particle_2D::ParticleMoveType::MoveNone;		// �����x�̉��Z���@
};


// ��������
class AlchemicalMachineObject;
class ICommand_Enemy;

namespace Json
{
	// �ǂݍ��݁FAttacker���ˏo����e�̏��
	Bullet_Data FileLoad_BulletData(const std::string filePath);
	// �ǂݍ��݁F�}�V���̊�{�f�[�^
	Machine_Data FileLoad_MachineData(const std::string filePath);
	// �ǂݍ��݁F�G�l�~�[�̊�{�f�[�^
	Enemy_Data FileLoad_EnemyData(const std::string filePath);
	// �ǂݍ��݁F�X�e�[�W�̊�{�f�[�^
	Stage_Data FileLoad_StageData(const std::string filePath);
	// �ǂݍ��݁F�X�e�[�W�N���A���
	Stage_ClearData FileLoad_StageClearData(const std::string filePath);
	// �ǂݍ��݁F�Q�[�����p�����[�^���
	Game_Parameter FileLoad_GameParameter(const std::string filePath);
	// �ǂݍ��݁FUI�ʒu�̏��
	UI_Data FileLoad_UIData(const std::string filePath);
	// �ǂݍ��݁F�p�[�e�B�N��2D�̒l
	Particle2D_Pram FileLoad_Particle2D(const std::string filePath);

	void WritingJsonFile_ClearData(int number,std::vector<std::shared_ptr<AlchemicalMachineObject>> alchemicalMachineList,int time);

	// �G�f�B�^�[�Ɏg�p�@�X�e�[�W�̃f�[�^����������
	void WritingJsonFile_StageData(int number,Stage_Data stageData);

	// �X�e�[�W�̃N���A�f�[�^������������
	void InitializationClearStageData();
}