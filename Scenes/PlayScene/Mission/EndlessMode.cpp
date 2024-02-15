#include "pch.h"
#include "EndlessMode.h"
#include "Scenes/PlayScene/UI/Number.h"
#include "NecromaLib/Singleton/ShareJsonData.h"

#include <algorithm>
#include <random>

EndlessMode::EndlessMode():
	m_score()
{

	m_renderScore = std::make_unique<Number>();

}

EndlessMode::~EndlessMode()
{
}

void EndlessMode::Initialize()
{
}

void EndlessMode::Update()
{
}

void EndlessMode::ScoreRender()
{
}

void EndlessMode::CreateStage(int wave)
{

	Stage_Data stageData = Stage_Data();
	std::random_device rd;

	// �}�V���p�~�b�V�������e�ݒ�
	auto CreateStageCondition_Machine = [&]()
	{
		// �}�V���̎�ގ擾�p
		std::uniform_int_distribution<> dist_machineType(1, MACHINE_TYPE::NUM - 1);
		MACHINE_TYPE machineType_rand = static_cast<MACHINE_TYPE>(dist_machineType(rd));

		Stage_Condition stageCondition = Stage_Condition();

		// �}�V���̎�ތ���
		stageCondition.condition = ChangeData::ChangeMachineString((MACHINE_TYPE)machineType_rand);

		// �K�v�ʎ擾�p
		std::uniform_int_distribution<> dist_val(1 + wave - 6 <= 0 ? 0 : wave - 6, wave / 2 <= 0 ? 1 : wave / 2);
		int val_rand = static_cast<int>(dist_val(rd));

		stageCondition.value = val_rand;

		return stageCondition;
	};

	// �G�l�~�[�p�~�b�V�������e�ݒ�
	auto CreateStageCondition_Enemy = [&]()
	{
		Stage_Condition stageCondition = Stage_Condition();

		// �G�l�~�[�̎�ތ���
		stageCondition.condition = ChangeData::ChangeEnemyString(ENMEY_NONE);

		// �K�v�ʎ擾�p
		std::uniform_int_distribution<> dist_val(1 , wave);
		int val_rand = static_cast<int>(dist_val(rd));

		stageCondition.value = val_rand;

		return stageCondition;
	};

	// �G�l�~�[�֌W�̃~�b�V��������
	stageData.condition[MISSION_TYPE::ENEMY_KILL].push_back(CreateStageCondition_Enemy());

	// �~�b�V�����̎�ގ擾
	std::uniform_int_distribution<> dist_missionType(0, MISSION_TYPE::ALCHEMI);
	MISSION_TYPE missionType = static_cast<MISSION_TYPE>(dist_missionType(rd));

	for (int i = 0; i < MISSION_TYPE::MISSION_NUM; i++)
	{
		// �ǉ�����\���mission�Ɠ����Ȃ�Δ�΂�
		if (missionType == (MISSION_TYPE)i ||
			MISSION_TYPE::ENEMY_KILL == (MISSION_TYPE)i) continue;

		Stage_Condition noneCondition = Stage_Condition();

		noneCondition.condition = "None";
		noneCondition.value = -1;

		stageData.condition[i].push_back(noneCondition);
	}

	// �}�V���֌W�̃~�b�V��������
	if (missionType == MISSION_TYPE::SPAWN || missionType == MISSION_TYPE::ALCHEMI)
	{
		stageData.condition[missionType].push_back(CreateStageCondition_Machine());
	}

	ShareJsonData::GetInstance().SetEndlessStageData(stageData);

}

