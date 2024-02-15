#include "pch.h"
#include "JsonLoder.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include "picojson.h"

// �\���̗p
#include "Scenes/PlayScene/AlchemicalMachine/AlchemicalMachineObject.h"
#include "Scenes/PlayScene/Enemy/EnemyList/ICommand_Enemy.h"
#include "NecromaLib/GameData/CommonStruct.h"

Bullet_Data Json::FileLoad_BulletData(const std::string filePath)
{
	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();
	Bullet_Data status;

	//	�ǂݍ��񂾃f�[�^���\���̂ɑ��
	status.element = val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["ELEMENT"].get<std::string>();

	status.str = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["STR"].get<double>();

	status.speed = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["SPEED"].get<double>();

	status.span = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["SPAN"].get<double>();

	status.life = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["LIFE"].get<double>();

	status.lossMp = (int)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["LOSSMP"].get<double>();

	return status;
}

Machine_Data Json::FileLoad_MachineData(const std::string filePath)
{
	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();
	Machine_Data status;

	//	�ǂݍ��񂾃f�[�^���\���̂ɑ��
	status.element = val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["ELEMENT"].get<std::string>();

	status.lv = (int)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["LV"].get<double>();

	status.hp = (int)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["HP"].get<double>();

	status.multiplier_hp = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["MULTIPLIER_HP"].get<double>();

	status.effect_rage = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["AREAEFFECT"].get<double>();

	status.effect_rage_rate = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["LVUP_AREAEFFECT_RATE"].get<double>();

	status.multiplier_effect = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["MULTIPLIER_EFFECT"].get<double>();

	status.alchemi_mp = (int)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["ALCHEMI_MP"].get<double>();

	status.alchemi_crystal = (int)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["ALCHEMI_CRYSTAL"].get<double>();

	status.repea_crystal = (int)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["REPEA_CRYSTAL"].get<double>();

	status.lvUp_crystal = (int)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["LVUP_CRYSTAL"].get<double>();

	status.dismantling_crystal = (int)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["DISMANTLING_CRYSTAL"].get<double>();

	status.effect_value = (float)val.get<picojson::object>()
		["Status"].get<picojson::object>()
		["EFFECT_VALUE"].get<double>();

	return status;
}

Enemy_Data Json::FileLoad_EnemyData(const std::string filePath)
{
	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();

	Enemy_Data data;

	picojson::object status = val.get<picojson::object>()["Status"].get<picojson::object>();

	//	�ǂݍ��񂾃f�[�^���\���̂ɑ��

	// ����
	data.element	= ChangeData::ChangeElement(status["ELEMENT"].get<std::string>());
	// �G�l�~�[�̎��
	data.type		= ChangeData::ChangeEnemy(status["TYPE"].get<std::string>());
	// �G�l�~�[�̓����̎��(����or�S��)
	data.moveType	= status["MOVETYPE"].get<std::string>();
	// HP
	data.hp			= (int)status["HP"].get<double>();
	// ���_LVUP�Ɏg�p�����EXP
	data.exp		= (int)status["EXP"].get<double>();
	// �U����
	data.power		= (float)status["STR"].get<double>();

	picojson::array moves = status["MOVEING"].get<picojson::array>();
	// �v�f����
	for (picojson::array::iterator it = moves.begin(); it != moves.end(); it++)
	{
		Enemy_MoveData param;

		param.moveName = it->get<picojson::object>()["TYPE"].get<std::string>();
		param.time = (float)it->get<picojson::object>()["TIME"].get<double>();
		param.delay = (float)it->get<picojson::object>()["DELAY"].get<double>();
		param.value = (float)it->get<picojson::object>()["VALUE"].get<double>();

		data.moveData.push_back(param);
	}

	return data;
}

Stage_Data Json::FileLoad_StageData(const std::string filePath)
{
	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();
	Stage_Data status;


	// �E�F�[�u�̃N���A�����𐶐�����
	auto createCondition = [&](std::string objectName, std::string arrayName, std::vector<Stage_Condition>& push_condition) {

		picojson::object& stageData = val.get<picojson::object>()[objectName].get<picojson::object>();
		picojson::array& stageConditions = stageData[arrayName].get<picojson::array>();

		// �v�f����
		for (picojson::array::iterator it = stageConditions.begin(); it != stageConditions.end(); it++) {

			Stage_Condition condition;
			condition.condition = it->get<picojson::object>()["TYPE"].get<std::string>();
			condition.value = (int)it->get<picojson::object>()["VALUE"].get<double>();

			push_condition.push_back(condition);

		}

	};


	// �}�V���ݒu
	createCondition("Conditions_Machine", "MACHINE_SPAWN", status.condition[MISSION_TYPE::SPAWN]);

	// �}�V���B��
	createCondition("Conditions_Alchemi", "MACHINE_ALCHEMI", status.condition[MISSION_TYPE::ALCHEMI]);

	// ���_LV
	createCondition("Conditions_BaseLv", "BASE_LV", status.condition[MISSION_TYPE::BASELV]);

	// �G�l�~�[����
	createCondition("Conditions_Enemy", "ENEMY_KNOCKDOWN", status.condition[MISSION_TYPE::ENEMY_KILL]);

	// �w�莞��
	createCondition("Conditions_Time", "TIME", status.condition[MISSION_TYPE::TIMER]);

	// ���\�[�X�l��
	createCondition("Conditions_Resource", "RESOURCE", status.condition[MISSION_TYPE::RESOURCE]);

	// �G�l�~�[�̃X�|�[���^�C�~���O�Ǝ�ށA�ꏊ�𓾂�
	picojson::object& enemy_span = val.get<picojson::object>()["ENEMY_SPAWNTIME"].get<picojson::object>();
	picojson::array& enemys = enemy_span["ENEMYS"].get<picojson::array>();

	for (picojson::array::iterator it = enemys.begin(); it != enemys.end(); it++)
	{

		Enemys_Spawn enemySpawn;
		enemySpawn.type = ChangeData::ChangeEnemy(it->get<picojson::object>()["TYPE"].get<std::string>());
		enemySpawn.spawnTime = (float)it->get<picojson::object>()["SPAWNTIME"].get<double>();
		enemySpawn.spawnPos.x = (float)it->get<picojson::object>()["SPAWN_X"].get<double>();
		enemySpawn.spawnPos.y = (float)it->get<picojson::object>()["SPAWN_Y"].get<double>();
		enemySpawn.spawnPos.z = (float)it->get<picojson::object>()["SPAWN_Z"].get<double>();
		enemySpawn.lv = (int)it->get<picojson::object>()["LV"].get<double>();

		// �������[�h���̃t���O
		if (it->get<picojson::object>()["CONDITION"].get<std::string>() == "Explanation")
		{
			enemySpawn.condition = true;
		}

		status.enemys_Spawn.push_back(enemySpawn);

	}

	// ���߂���ݒu����Ă���}�V���̏��𓾂�
	picojson::object& defaulet_machine = val.get<picojson::object>()["MACHINE_DEFAULET"].get<picojson::object>();
	picojson::array& machine = defaulet_machine["MACHINES"].get<picojson::array>();

	for (picojson::array::iterator it = machine.begin(); it != machine.end(); it++)
	{

		Stage_Machine stage_machine;
		stage_machine.lv = (int)it->get<picojson::object>()["LV"].get<double>();
		stage_machine.type = ChangeData::ChangeMachine(it->get<picojson::object>()["TYPE"].get<std::string>());
		stage_machine.element = ChangeData::ChangeElement(it->get<picojson::object>()["ELEMENT"].get<std::string>());
		stage_machine.number = (int)it->get<picojson::object>()["NUMBER"].get<double>();

		status.machine.push_back(stage_machine);

	}

	// �X�e�[�W��Resource�Q���
	picojson::object& default_resource = val.get<picojson::object>()["RESOURCE_DEFAULET"].get<picojson::object>();
	Stage_Resource stage_resource;

	stage_resource.lv = (int)default_resource["LV"].get<double>();
	stage_resource.mp = (int)default_resource["MP"].get<double>();
	stage_resource.exp = (int)default_resource["EXP"].get<double>();
	stage_resource.crystal = (int)default_resource["CRYSTAL"].get<double>();
	stage_resource.attacker = (int)default_resource["ATTACKER"].get<double>();
	stage_resource.upper = (int)default_resource["UPPER"].get<double>();
	stage_resource.mining = (int)default_resource["MINING"].get<double>();
	stage_resource.deffencer = (int)default_resource["DEFFENCER"].get<double>();
	stage_resource.recovery = (int)default_resource["RECOVERY"].get<double>();
	stage_resource.hp = (int)default_resource["HP"].get<double>();

	status.resource = stage_resource;

	// �`���[�g���A���ԍ��擾
	picojson::array& tutorialArray = val.get<picojson::object>()["TUTORIAL"].get<picojson::array>();

	for (picojson::array::iterator it = tutorialArray.begin(); it != tutorialArray.end(); it++)
	{
		Tutorial_Status tutorial = Tutorial_Status();

		tutorial.type = (int)it->get<picojson::object>()["NUMBER"].get<double>();
		tutorial.val = (int)it->get<picojson::object>()["VAL"].get<double>();

		status.tutorial.push_back(tutorial);

	}

	// �N���X�^���̈ʒu�����߂�
	picojson::object& defaulet_crystal = val.get<picojson::object>()["CRYSTAL_SPAWN"].get<picojson::object>();
	picojson::array& crystal = defaulet_crystal["CRYSTALS"].get<picojson::array>();

	for (picojson::array::iterator it = crystal.begin(); it != crystal.end(); it++)
	{
		SimpleMath::Vector2 crystalPos = SimpleMath::Vector2();

		// �������I�������l������Vector2���̗p
		crystalPos.x = (float)it->get<picojson::object>()["SPAWN_X"].get<double>();
		crystalPos.y = (float)it->get<picojson::object>()["SPAWN_Z"].get<double>();

		status.crystalPos.push_back(crystalPos);

	}

	// ���ꂪ���̃X�e�[�W�ł̍Ō�̃E�F�[�u�ł���
	bool lastWave = val.get<picojson::object>()["LastWave"].get<bool>();

	// ����WAVE�ŏo������G��LV
	int enemyLv = 0;
	enemyLv = (int)val.get<picojson::object>()["EnemyLv"].get<double>();

	status.lastWave = lastWave;

	return status;
}

Stage_ClearData Json::FileLoad_StageClearData(const std::string filePath)
{
	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();
	Stage_ClearData status;

	//	�ǂݍ��񂾃f�[�^���\���̂ɑ��
	// �N���A����
	// stageData����MACHINE_SPAWN�̔z��̒��g�𓾂�
	picojson::object& clearData = val.get<picojson::object>()["ClearData"].get<picojson::object>();
	picojson::array& machines = clearData["MACHINES"].get<picojson::array>();

	// �v�f����
	for (picojson::array::iterator it = machines.begin(); it != machines.end(); it++) {

		Stage_Machine condition;

		condition.lv		= (int)it->get<picojson::object>()["LV"].get<double>();
		condition.type		= ChangeData::ChangeMachine(it->get<picojson::object>()["NAME"].get<std::string>());
		condition.element	= ChangeData::ChangeElement(it->get<picojson::object>()["ELEMENT"].get<std::string>());
		condition.number	= (int)it->get<picojson::object>()["NUMBER"].get<double>();

		status.machines.push_back(condition);

	}

	status.clearTime = (int)clearData["TIME"].get<double>();
	status.num		 = (int)clearData["NUM"].get<double>();

	return status;
}

void Json::WritingJsonFile_ClearData(int number,std::vector<std::shared_ptr<AlchemicalMachineObject>> alchemicalMachineList,int time)
{
	time;

	// number�ɉ������t�@�C���p�X��ǂݍ���
	std::ostringstream oss;
	oss << number;
	std::string filePath = "Resources/Json/ClearData/ClearData_" + oss.str() + ".json";

	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();

	// �������������json����擾
	picojson::object& clearMachineObj = val.get<picojson::object>()["ClearData"].get<picojson::object>();
	picojson::array& clearMachineArr = clearMachineObj["MACHINES"].get<picojson::array>();

	//picojson::object& timeObj = val.get<picojson::object>()["TIME"].get<picojson::object>();

	// ������
	clearMachineArr.clear();

	for (int i = 0; i < alchemicalMachineList.size(); i++)
	{
		// ���e�ǉ�
		picojson::object id;
		id.insert(std::make_pair("LV", picojson::value((double)alchemicalMachineList[i]->GetLv())));
		id.insert(std::make_pair("NAME", picojson::value(alchemicalMachineList[i]->GetObjectName())));
		id.insert(std::make_pair("ELEMENT", picojson::value(ChangeData::ChangeElementString(alchemicalMachineList[i]->GetElement()))));
		id.insert(std::make_pair("NUMBER", picojson::value((double)i)));
		// ���e��������
		clearMachineArr.emplace_back(picojson::value(id));

	}

	std::ofstream ofs(filePath);

	ofs << picojson::value(val).serialize(true) << std::endl;
}

void Json::WritingJsonFile_StageData(int number, Stage_Data stageData)
{

	// number�ɉ������t�@�C���p�X��ǂݍ���
	std::ostringstream oss;
	oss << number;
	std::string filePath = "Resources/Json/StageData/StageData_" + oss.str() + ".json";

	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	std::ifstream empty_file; // ��̃t�H�[�}�b�g
	std::ofstream writing_file;// �������ރt�@�C��

	// �t�@�C������(��̃t�H�[�}�b�g���R�s�[���� �ǂݎ���p)
	empty_file.open("Resources/Json/StageData/StageData_EMPTY.json", std::ios::in);
	writing_file.open(filePath, std::ios::out);

	std::string line;
	while (std::getline(empty_file, line)) {
		writing_file << line << std::endl;
	}

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	empty_file.close();
	writing_file.close();

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[��f���B��R�[�h�Ő������Ă��邽�߁A�G���[�͊�{�f����Ȃ�
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();

	// �o������G�l�~�[���
	{
		picojson::object& stageData_SpawnEnemy = val.get<picojson::object>()["ENEMY_SPAWNTIME"].get<picojson::object>();
		picojson::array& spawnEnemy_array = stageData_SpawnEnemy["ENEMYS"].get<picojson::array>();

		spawnEnemy_array.clear();
		for (int i = 0; i < stageData.enemys_Spawn.size(); i++)
		{
			picojson::object id;
			id.insert(std::make_pair("TYPE", ChangeData::ChangeEnemyString(stageData.enemys_Spawn[i].type)));
			id.insert(std::make_pair("SPAWN_X", (double)stageData.enemys_Spawn[i].spawnPos.x));
			id.insert(std::make_pair("SPAWN_Y", (double)stageData.enemys_Spawn[i].spawnPos.y));
			id.insert(std::make_pair("SPAWN_Z", (double)stageData.enemys_Spawn[i].spawnPos.z));
			id.insert(std::make_pair("SPAWNTIME", (double)stageData.enemys_Spawn[i].spawnTime));
			id.insert(std::make_pair("CONDITION", stageData.enemys_Spawn[i].condition));

			spawnEnemy_array.emplace_back(picojson::value(id));
		}

	}

	// ���߂���ݒu����Ă���}�V�����
	{
		// �������������json����擾
		picojson::object& default_Machine = val.get<picojson::object>()["MACHINE_DEFAULET"].get<picojson::object>();
		picojson::array& defaultMachine_array = default_Machine["MACHINES"].get<picojson::array>();
		// ������
		defaultMachine_array.clear();

		for (int i = 0; i < stageData.machine.size(); i++)
		{
			// ���e�ǉ�
			picojson::object id;
			id.insert(std::make_pair("LV", picojson::value((double)stageData.machine[i].lv)));
			id.insert(std::make_pair("NAME", picojson::value(ChangeData::ChangeMachineString(stageData.machine[i].type))));
			id.insert(std::make_pair("ELEMENT", picojson::value(ChangeData::ChangeElementString(stageData.machine[i].element))));
			id.insert(std::make_pair("NUMBER", picojson::value((double)stageData.machine[i].number)));
			// ���e��������
			defaultMachine_array.emplace_back(picojson::value(id));

		}
	}
	// �X�e�[�W�̃��\�[�X�Q
	{
		// �������������json����擾
		picojson::object& default_Resource = val.get<picojson::object>()["RESOURCE_DEFAULET"].get<picojson::object>();

		// ������
		default_Resource.clear();

		// ��������
		default_Resource.insert(std::make_pair("CRYSTAL", picojson::value((double)stageData.resource.crystal)));
		default_Resource.insert(std::make_pair("MP", picojson::value((double)stageData.resource.mp)));
		default_Resource.insert(std::make_pair("LV", picojson::value((double)stageData.resource.lv)));
		default_Resource.insert(std::make_pair("EXP", picojson::value((double)stageData.resource.lv)));
		default_Resource.insert(std::make_pair("ATTACKER", picojson::value((double)stageData.resource.attacker)));
		default_Resource.insert(std::make_pair("UPPER", picojson::value((double)stageData.resource.upper)));
		default_Resource.insert(std::make_pair("DEFFENCER", picojson::value((double)stageData.resource.deffencer)));
		default_Resource.insert(std::make_pair("MINING", picojson::value((double)stageData.resource.mining)));
		default_Resource.insert(std::make_pair("RECOVERY", picojson::value((double)stageData.resource.recovery)));
	}
	// �`���[�g���A���̎擾
	picojson::array& tutorial = val.get<picojson::object>()["TUTORIAL"].get<picojson::array>();
	tutorial.clear();

	for (int i = 0; i < tutorial.size(); i++)
	{
		picojson::object id;
		id.insert(std::make_pair("NUMBER", picojson::value((double)stageData.tutorial[i].type)));
		id.insert(std::make_pair("VAL", picojson::value((double)stageData.tutorial[i].val)));

		tutorial.emplace_back(id);
	}

	// �N���X�^���̏����ʒu���
	{
		picojson::object& stageData_Crystal = val.get<picojson::object>()["CRYSTAL_SPAWN"].get<picojson::object>();
		picojson::array& spawnCrystal_array = stageData_Crystal["CRYSTALS"].get<picojson::array>();

		spawnCrystal_array.clear();
		for (int i = 0; i < stageData.crystalPos.size(); i++)
		{
			picojson::object id;
			id.insert(std::make_pair("SPAWN_X", (double)stageData.crystalPos[i].x));
			// �������I�s�����ǂ���Y��Z�Ƃ��Ĉ���
			id.insert(std::make_pair("SPAWN_Z", (double)stageData.crystalPos[i].y));

			spawnCrystal_array.emplace_back(picojson::value(id));
		}
	}

	std::ofstream ofs(filePath);

	ofs << picojson::value(val).serialize(true) << std::endl;
}

void Json::InitializationClearStageData()
{
	// number�ɉ������t�@�C���p�X��ǂݍ���

	for (int i = 0; i < 12; i++)
	{

		std::ostringstream oss;
		oss << i;
		std::string filePath = "Resources/Json/ClearData/ClearData_" + oss.str() + ".json";

		//	�ǂݍ��ݗp�ϐ�
		std::ifstream ifs;

		//	�t�@�C���ǂݍ���
		ifs.open(filePath, std::ios::binary);

		std::ifstream empty_file; // ��̃t�H�[�}�b�g
		std::ofstream writing_file;// �������ރt�@�C��

		// �t�@�C������(��̃t�H�[�}�b�g���R�s�[���� �ǂݎ���p)
		empty_file.open("Resources/Json/ClearData/ClearData_ENPTY.json", std::ios::in);
		writing_file.open(filePath, std::ios::out);

		std::string line;
		while (std::getline(empty_file, line)) {
			writing_file << line << std::endl;
		}

		empty_file.close();
		writing_file.close();

		//	�ǂݍ��݃`�F�b�N
		//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
		assert(ifs);

		//	Picojson�֓ǂݍ���
		picojson::value val;
		ifs >> val;

		//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
		ifs.close();

		std::ofstream ofs(filePath);

		ofs << picojson::value(val).serialize(true) << std::endl;

	}
}

Game_Parameter Json::FileLoad_GameParameter(const std::string filePath)
{
	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();

	Game_Parameter data;

	picojson::object status = val.get<picojson::object>()["GAME_PARAMETER"].get<picojson::object>();

	data.rotateSpeed		= (float)status["ROTATE_SPEED"].get<double>();
	data.transparent_time	= (float)status["UI_TRANSPARENT_TIME"].get<double>();
	data.transparent_val	= (float)status["UI_TRANSPARENT_VAL"].get<double>();
	data.stage_Max			= (int)status["MAX_STAGE"].get<double>();
	data.baseLV_MAX			= (int)status["MAX_LV"].get<double>();
	data.baseHp_Max			= (int)status["MAX_BASEHP"].get<double>();
	data.crystal_Max		= (int)status["MAX_MP"].get<double>();
	data.mp_Max				= (int)status["MAX_CRYSTAL"].get<double>();
	data.needExp			= (int)status["NEED_EXP"].get<double>();
	data.needExp_Growthrate = (int)status["GROWTHRATE_EXP"].get<double>();

	return data;
}

UI_Data Json::FileLoad_UIData(const std::string filePath)
{
	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();

	UI_Data uiData = UI_Data();

	//�@====================[�@�K�w��H��@]
	picojson::object layout = val.get<picojson::object>()["UILAYOUT"].get<picojson::object>();
	picojson::object master = layout["MASTER"].get<picojson::object>();

	//�@====================[�@�擾�����l����́@]
	uiData.pos.x = (float)master["POS_X"].get<double>();
	uiData.pos.y = (float)master["POS_Y"].get<double>();

	uiData.rage.x = (float)master["RAGE_X"].get<double>();
	uiData.rage.y = (float)master["RAGE_Y"].get<double>();

	picojson::array optionVals = master["OPTION"].get<picojson::array>();

	//�@====================[�@�z�񂩂�ǉ��v�f�𓾂�@]
	//�@�@|=>�@�ǉ��v�f
	for (picojson::array::iterator it = optionVals.begin(); it != optionVals.end(); it++)
	{
		std::string tagName = it->get<picojson::object>()["TAG"].get<std::string>();
		float optionVal		= (float)it->get<picojson::object>()["VAL"].get<double>();

		uiData.option.insert(std::make_pair(tagName, optionVal));
	}

	picojson::array keys = master["KEYS"].get<picojson::array>();

	//�@�@|=>�@�L�[�ݒ�
	for (picojson::array::iterator it = keys.begin(); it != keys.end(); it++)
	{
		//�@�@|=>�@������Ŏ擾����16�i����10�i���ɕϊ�
		int num = strtol(it->get<picojson::object>()["CODE"].get<std::string>().c_str(), NULL, 16);
		//�@�@|=>�@Keys�^�ɕϊ�
		uiData.key.push_back((Keyboard::Keys)static_cast<unsigned char>(num));
	}


	return uiData;
}

Particle2D_Pram Json::FileLoad_Particle2D(const std::string filePath)
{

	//	�ǂݍ��ݗp�ϐ�
	std::ifstream ifs;

	//	�t�@�C���ǂݍ���
	ifs.open(filePath, std::ios::binary);

	//	�ǂݍ��݃`�F�b�N
	//	ifs�ϐ��Ƀf�[�^���Ȃ���΃G���[
	assert(ifs);

	//	Picojson�֓ǂݍ���
	picojson::value val;
	ifs >> val;

	//	ifs�ϐ��͂����g��Ȃ��̂ŕ���
	ifs.close();

	picojson::object status = val.get<picojson::object>()["PARAMETER"].get<picojson::object>();

	//	�ǂݍ��񂾃f�[�^���\���̂ɑ��

	auto changeVal = [&](picojson::object object, std::string key)
	{
		return (float)object[key].get<double>();
	};


	picojson::object velo = status["Velocity"].get<picojson::object>();
	picojson::object acce = status["Accele"].get<picojson::object>();
	picojson::object scaF = status["Scale_F"].get<picojson::object>();
	picojson::object scaE = status["Scale_E"].get<picojson::object>();
	picojson::object colF = status["Color_F"].get<picojson::object>();
	picojson::object colE = status["Color_E"].get<picojson::object>();

	ParticleUtility_2D pU(
		(float)status["Life"].get<double>(),													// ��������
		SimpleMath::Vector2::Zero,																// ����W
		SimpleMath::Vector2(changeVal(velo,"X"), changeVal(velo, "Y")),	// ���x
		SimpleMath::Vector2(changeVal(acce, "X"), changeVal(acce, "Y")),	// �����x
		SimpleMath::Vector2(changeVal(scaF, "X"), changeVal(scaF, "Y")),	// �����X�P�[��
		SimpleMath::Vector2(changeVal(scaE, "X"), changeVal(scaE, "Y")),		// �ŏI�X�P�[��
		SimpleMath::Color(changeVal(colF, "R"), changeVal(colF, "G"), changeVal(colF, "B"), changeVal(colF, "A")),	// �����J���[
		SimpleMath::Color(changeVal(colE, "R"), changeVal(colE, "G"), changeVal(colE, "B"), changeVal(colE, "A"))	// �ŏI�J���[
	);

	picojson::object velo_M = status["Velocity_Max"].get<picojson::object>();
	picojson::object acce_M = status["Accele_Max"].get<picojson::object>();
	picojson::object scaF_M = status["Scale_F_Max"].get<picojson::object>();
	picojson::object scaE_M = status["Scale_E_Max"].get<picojson::object>();
	picojson::object colF_M = status["Color_F_Max"].get<picojson::object>();
	picojson::object colE_M = status["Color_E_Max"].get<picojson::object>();

	ParticleUtility_2D pU_Max(
		(float)status["Life_Max"].get<double>(),												// ��������
		SimpleMath::Vector2::Zero,																// ����W
		SimpleMath::Vector2(changeVal(velo_M, "X"), changeVal(velo_M, "Y")),						// ���x
		SimpleMath::Vector2(changeVal(acce_M, "X"), changeVal(acce_M, "Y")),						// �����x
		SimpleMath::Vector2(changeVal(scaF_M, "X"), changeVal(scaF_M, "Y")),						// �����X�P�[��
		SimpleMath::Vector2(changeVal(scaE_M, "X"), changeVal(scaE_M, "Y")),						// �ŏI�X�P�[��
		SimpleMath::Color(changeVal(colF_M, "R"), changeVal(colF_M, "G"), changeVal(colF_M, "B"), changeVal(colF_M, "A")),	// �����J���[
		SimpleMath::Color(changeVal(colE_M, "R"), changeVal(colE_M, "G"), changeVal(colE_M, "B"), changeVal(colE_M, "A"))	// �ŏI�J���[
	);									

	Particle2D_Pram param;

	param.praticleData	= pU;
	param.random_Max	= pU_Max;

	param.num		= (int)status["Num"].get<double>();
	param.maxNum	= (int)status["Num_Max"].get<double>();

	param.rage		= (float)status["Rage"].get<double>();
	param.maxRage	= (float)status["Rage_Max"].get<double>();

	param.time		= (float)status["Time"].get<double>();

	param.praticleData.SetStateRad((float)status["Rotate"].get<double>());
	param.random_Max.SetEndRad((float)status["Rotate_Max"].get<double>());

	param.praticleData.SetEndRad((float)status["Rotate_E"].get<double>());
	param.random_Max.SetEndRad((float)status["Rotate_E_Max"].get<double>());

	param.tag		= status["Tag"].get<std::string>();

	//�@�@|=>�@�p�[�e�B�N���̈ړ��^�C�v
	param.acceleType	= ParticleData_Change::ChangeMoveType(velo["Type"].get<std::string>());
	param.velocityType	= ParticleData_Change::ChangeMoveType(acce["Type"].get<std::string>());

	// �p�[�e�B�N���̐����|�C���g�̐ݒ�
	for (auto& pos : status["Positions"].get<picojson::array>())
	{
		SimpleMath::Vector2 pointPos;
		pointPos.x = (float)pos.get<picojson::object>()["X"].get<double>();
		pointPos.y = (float)pos.get<picojson::object>()["Y"].get<double>();

		param.points.push_back(pointPos);
	}
	param.linerType = ParticleData_Change::ChangeLinerType(status["LinerType"].get<std::string>());
	param.linerSpeed	= (float)status["LinerSpeed"].get<double>();
	param.maxLinerSpeed = (float)status["LinerSpeed_Max"].get<double>();

	param.drawType = ParticleData_Change::ChangeDrawType(status["DrawMode"].get<std::string>());

	return param;
}
