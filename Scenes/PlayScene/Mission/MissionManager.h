#pragma once

#include "NecromaLib/GameData/Animation.h"
#include "NecromaLib/GameData/CommonStruct.h"

#include "Scenes/PlayScene/Mission/EndlessMode.h"

// �O���錾
class AlchemicalMachineManager;
class FieldObjectManager;
class EnemyManager;
class Number;
class MissionRender;
class DrawTimer;
class Veil;
class UserInterface;
class DrawArrow;
class SelectionBox;
class ClearVeil;
struct Stage_Condition;

class MissionManager
{
public:
	MissionManager();
	~MissionManager();

	void Initialize(int maxwaveNum);
	void Update(AlchemicalMachineManager* pAlchemicalManager, EnemyManager* pEnemyManager, FieldObjectManager* pFieldManager);

	void TimerUpdate();

	std::unique_ptr<MissionRender>* GetMissionRender() { return &m_missionRender; }

	void Render(int maxwaveNum);

	// �X�e�[�W�����ēx�ǂݍ���
	void ReloadWave();

	bool MissionComplete();
	// �~�b�V���������s�����ۂ̃t���O
	bool MissionFailure();
	// �~�b�V�������i�s�s�\�ɂȂ����ۂ̃t���O
	bool MissionUnable();

	// ����WAVE�ɐi�񂾂��Ƃ�m�点��t���O
	bool NextWaveFlag();

	int GetStartTimer();

	int GetWave() { return m_wave; }

	// UI�Q�̃A���t�@�l��ς��A����������
	void TransparentUI(float transparentVal);

private:

	void MachineMission(AlchemicalMachineManager* alchemicalManager);
	void AlchemiMission(AlchemicalMachineManager* alchemicalManager);

	void ResourceMission(AlchemicalMachineManager* alchemicalManager);

	void EnemyMission(EnemyManager* enemyManager);
	void BaseLvMission(int baseLv);
	void TimerMission();

private:

	// �~�b�V��������
	std::vector<Stage_Condition> m_missonCondition[MISSION_TYPE::MISSION_NUM];

	// �^�C�}�[�v��
	std::unique_ptr<DrawTimer> m_timeRender;

	// �~�b�V�����`��
	std::unique_ptr<MissionRender> m_missionRender;

	// �~�b�V�������e�J���{�^��
	std::unique_ptr<DrawArrow> m_closeButton;

	// �~�b�V�����N���A�����o�N���X
	std::unique_ptr<ClearVeil> m_clearVeil;

	// ��������(�N���A��)�̕`��
	std::unique_ptr<Veil> m_backVeil;

	// Wave���`��
	std::unique_ptr<Number> m_waveRender, m_maxWaveRender;

	// �G���h���X���[�h�p�̃~�b�V���������֐�
	std::unique_ptr<EndlessMode> m_endlessMode;

	// ���Ԍo�ߋL�^�ϐ� �Q�[���S��
	float m_gameTimer;
	// ���Ԍo�ߋL�^�ϐ� �E�F�[�u��
	float m_waveTimer;

	// �}�E�X���͈͂ɓ����Ă��邩�ۂ������o���铖���蔻��N���X
	std::unique_ptr<SelectionBox> m_collider;

	// �X�e�[�W�N���A�����ۂɗ����A�j���[�V�����p�ϐ�
	AnimationData m_clearAnimation;

	// �S�Ă̏����𖞂��������Ƃ������t���O
	bool m_allClearFlag;

	// ���������Ƃ��ł��Ȃ��Ȃ������Ƃ������t���O(���s�t���O)
	bool m_failureFlag;

	// �S�ă~�b�V�����̍��v��
	int m_missionNum;

	// ���݂̃~�b�V�����̐i�s�x
	int m_missionSituation;

	// ���݂̋��_��HP
	int m_baseHP;

	// ���݂��Ō�̃X�e�[�W�ł��邩
	bool m_lastWave;

	//�@���݂�Wave���̎擾
	int m_wave;

	// ����Wave�ɐi�񂾂��Ƃ�m�点��t���O
	bool m_nextWaveFlag;

	// �~�b�V�����̕\�������
	bool m_closeMission;

	// ��ލۂ̃A�j���[�V�����p�ϐ�
	AnimationData m_closeAnimation;

	// �X�e�[�W���G���h���X���[�h�ɂ���t���O
	bool m_endlesFlag;

};