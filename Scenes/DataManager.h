//--------------------------------------------------------------------------------------
// File: DataManager.h
//
//�@���̃N���X���狤�ʂŎg���ϐ��̎󂯓n����S������V���O���g���N���X
//  �������́@���������@�|�����G�̐��@�ݒu���Ă���A���P�~�J���}�V���̑���/��ޕ�
// 
// Date: 2023.6.14
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once

class DataManager
{
public:
	~DataManager() = default;

	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;

	//static void Create();
	//static void Destroy();

	//static DataManager& GetInstance() { return *instance; }

	//	�C���X�^���X�̊m��
	static DataManager* GetInstance() { return instance; }

	//	�C���X�^���X�̐���
	static void Create() { if (instance == nullptr) instance = new DataManager; }

	//	�C���X�^���X�̍폜
	static void Destroy()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void Initialize();
	void Update();

// �Q�b�^�[�@�Z�b�^�[
public:

	//���͑���
	int GetNowMP()					const { return m_nowMP; }
	void SetNowMP(int value)			  { m_nowMP = value; }
	int GetNowMP_MAX()				const { return m_nowMP_MAX; }
	void SetNowMP_MAX(int value)		  { m_nowMP_MAX = value; }

	// �ő喂�͑��ʂ̍Čv�Z
	void MPMAXRecalculation(int lv);

	//��������
	int GetNowCrystal()				const { return m_nowCrystal; }
	void SetNowCrystal(int value)		  { m_nowCrystal = value; }
	int GetNowCrystal_MAX()			const { return m_nowCrystal_MAX; }
	void SetNowCrystal_MAX(int value)	  { m_nowCrystal_MAX = value; }

	// �ő�N���X�^�����ʂ̍Čv�Z
	void CrystalMAXRecalculation(int lv);

	//HP����
	int GetNowBaseHP()				const { return m_nowBaseHp; }
	void SetNowBaseHP(int hp)			  { m_nowBaseHp = hp; }
	int GetNowBaseHP_MAX()			const { return m_nowBaseHp_MAX; }
	void SetNowBaseHP_MAX(int hp)		  { m_nowBaseHp_MAX = hp; }

	// �ő�N���X�^�����ʂ̍Čv�Z
	void BaseHPMAXRecalculation(int lv);

	//�G������
	int GetNowEnemyKill()		const	{ return m_nowEnemyKill; }
	void SetNowEnemyKill(int value)		{ m_nowEnemyKill = value; }

	// ���E���h��
	int GetRound()				const	{ return m_round; }
	void SetRound(int value)			{ m_round = value;}

	// �X�e�[�W�ԍ�
	int GetStageNum()			const { return m_stageNum;}
	void SetStageNum(int stageNum) { this->m_stageNum = stageNum; }

	int GetStageMax()			const { return 10;}


private:
	DataManager();
	static DataManager* instance;

	// ���݂̖��͑���
	int m_nowMP;

	// ���݂̖��͍ő��
	int m_nowMP_MAX;

	// ���݂̌�������
	int m_nowCrystal;

	// ���݂̌����ő��
	int m_nowCrystal_MAX;

	// ���݂̋��_HP
	int m_nowBaseHp;
	int m_nowBaseHp_MAX;

	// ���݂̓G������
	int m_nowEnemyKill;

	// ���݂̃��E���h��
	int m_round;

	// ���݂̃X�e�[�W��
	int m_stageNum;

	// �X�e�[�W���N���A�����t���O
	bool m_stageClearFlag;

};