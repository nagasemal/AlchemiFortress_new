#include "pch.h"
#include "ShareJsonData.h"
#include "NecromaLib/GameData/Easing.h"

ShareJsonData* ShareJsonData::instance = nullptr;

ShareJsonData::ShareJsonData():
	m_bulletData{}
{

}

void ShareJsonData::Create()
{
	if (instance == nullptr)
	{
		instance = new ShareJsonData;
	}
}

void ShareJsonData::Destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void ShareJsonData::LoadingJsonFile_Bullet()
{

	m_bulletData[ELEMENT::NOMAL]	= Json::FileLoad_BulletData("Resources/Json/BulletData/BulletData_Nomal.json");
	m_bulletData[ELEMENT::FLAME]	= Json::FileLoad_BulletData("Resources/Json/BulletData/BulletData_Flame.json");
	m_bulletData[ELEMENT::AQUA]		= Json::FileLoad_BulletData("Resources/Json/BulletData/BulletData_Aqua.json");
	m_bulletData[ELEMENT::WIND]		= Json::FileLoad_BulletData("Resources/Json/BulletData/BulletData_Wind.json");
	m_bulletData[ELEMENT::EARTH]	= Json::FileLoad_BulletData("Resources/Json/BulletData/BulletData_Earth.json");

}

void ShareJsonData::LoadingJsonFile_Machine()
{
	m_machineData[MACHINE_TYPE::NONE]		= Json::FileLoad_MachineData("Resources/Json/MachineData/MachineData_None.json");
	m_machineData[MACHINE_TYPE::ATTACKER]	= Json::FileLoad_MachineData("Resources/Json/MachineData/MachineData_Attacker.json");
	m_machineData[MACHINE_TYPE::DEFENSER]	= Json::FileLoad_MachineData("Resources/Json/MachineData/MachineData_Defenser.json");
	m_machineData[MACHINE_TYPE::MINING]		= Json::FileLoad_MachineData("Resources/Json/MachineData/MachineData_Mining.json");
	m_machineData[MACHINE_TYPE::RECOVERY]	= Json::FileLoad_MachineData("Resources/Json/MachineData/MachineData_Recovery.json");
	m_machineData[MACHINE_TYPE::UPPER]		= Json::FileLoad_MachineData("Resources/Json/MachineData/MachineData_Upper.json");
}

void ShareJsonData::LoadingJsonFile_Enemy()
{
	m_enemyData[ENEMY_TYPE::ENMEY_NONE] = Json::FileLoad_EnemyData("Resources/Json/EnemyData/EnemyData_None.json");
	m_enemyData[ENEMY_TYPE::SLIME] = Json::FileLoad_EnemyData("Resources/Json/EnemyData/EnemyData_Slime.json");
	m_enemyData[ENEMY_TYPE::WORM] = Json::FileLoad_EnemyData("Resources/Json/EnemyData/EnemyData_Worm.json");
	m_enemyData[ENEMY_TYPE::HOP] = Json::FileLoad_EnemyData("Resources/Json/EnemyData/EnemyData_Hop.json");
	m_enemyData[ENEMY_TYPE::RETREAT] = Json::FileLoad_EnemyData("Resources/Json/EnemyData/EnemyData_Retreat.json");
}

void ShareJsonData::LoadingJsonFile_GameParameter()
{

	m_gameParam = Json::FileLoad_GameParameter("Resources/Json/GameParameter/GameParameter.json");

}

void ShareJsonData::LoadingJsonFile_Stage(int number, int wave)
{

	// number�ɉ������t�@�C���p�X��ǂݍ���
	std::ostringstream oss;
	oss << "Stage_" << number << "/StageData_" << number << "_" << wave;

	std::string filePath = "Resources/Json/StageData/" + oss.str() + ".json";

	//�@====================[�@�����p������ۑ�����@]
	//�@�@|=>�@�N���X�^���̈ʒu
	std::vector<SimpleMath::Vector2> saveCrystalPos;
	if (wave > 1)	saveCrystalPos = m_stageData.crystalPos;

	//�@====================[�@�X�e�[�W�f�[�^��ǂݍ��ށ@]
	m_stageData = Json::FileLoad_StageData(filePath);

	//�@====================[�@�ۑ����������ēx����Ȃ����@]
	if (wave > 1)	m_stageData.crystalPos = saveCrystalPos;
}

void ShareJsonData::LoadingJsonFile_ClearData(int number)
{
	m_clearData = Stage_ClearData();

	// number�ɉ������t�@�C���p�X��ǂݍ���
	std::ostringstream oss;
	oss << number;
	std::string filePath = "Resources/Json/ClearData/ClearData_" + oss.str() + ".json";

	m_clearData = Json::FileLoad_StageClearData(filePath);
}

void ShareJsonData::LoadingUIData(std::string pathName,std::string tagName)
{
	std::string tagPath = pathName + tagName;

	//�@====================[�@�V�����A�z�z��𐶐��@]
	m_uiDatas.insert(std::make_pair(tagPath,UI_Data()));

	//�@====================[�@tagName�ɉ������t�@�C���p�X�𐶐��@]
	std::ostringstream ossPath;
	ossPath << pathName;

	std::ostringstream ossName;
	ossName << tagName;

	std::string filePath = "Resources/Json/GameParameter/" + ossPath.str() + "/UILayout_" + ossPath.str() + ossName.str() + ".json";



	//�@====================[�@���������f�[�^�����@]
	m_uiDatas[tagPath] = Json::FileLoad_UIData(filePath);

	//�@====================[�@Offset�����O�ɓ����Ă��鎞�̏����@]
	//�@�@|=>�@[�ϐ�]�@�^�O�����ʂ���
	std::string tag = std::string();

	for (size_t i = 0; i < tagPath.size(); i++)
	{
		//�@�@|=>�@[����]�@���͂��ꂽ�^�O��i�Ԗڈȍ~�̔z��Offset
		if (tagPath.substr(i) == "Offset")
		{
			//�@�@|=>�@Offset�O�̃^�O�����擾����
			tag = tagPath.substr(0,i);
		}

	}

	// �^�O�̃T�C�Y��0�Ȃ�Ώ������s���K�v�͂Ȃ�
	if (tag.size() == 0) return;

	for (auto it = m_uiDatas.begin(); it != m_uiDatas.end(); it++)
	{
		//�@�@|=>�@�����o�����^�O���Ɠ��l�̃^�O�������o
		if (it->first.substr(0, tag.size()) == tag)
		{
			if (it->first.substr(tag.size()) == "Offset") continue;

			//�@�@|=>�@�ʒu,�傫���̏������Z����
			it->second.pos	+= m_uiDatas[tagPath].pos;
			it->second.rage	+= m_uiDatas[tagPath].rage;
		}
	}


}

void ShareJsonData::LoadingParticle2D(std::string pathName)
{

	//�@====================[�@tagName�ɉ������t�@�C���p�X�𐶐��@]
	std::ostringstream ossPath;
	ossPath << pathName;

	std::string filePath = "Resources/Json/Particle2D/" + ossPath.str() + ".json";

	//�@====================[�@���������f�[�^�����@]
	Particle2D_Pram parm = Json::FileLoad_Particle2D(filePath);

	//�@====================[�@�V�����A�z�z��𐶐��@]
	m_particlePrams.insert(std::make_pair(parm.tag, parm));
}

void ShareJsonData::SetEndlessStageData(Stage_Data data)
{

	m_stageData = data;

}

const Bullet_Data ShareJsonData::GetBulletData(ELEMENT element)
{
	return m_bulletData[element];
}

const Machine_Data ShareJsonData::GetMachineData(MACHINE_TYPE type)
{
	return m_machineData[type];
}

const Enemy_Data ShareJsonData::GetEnemyData(ENEMY_TYPE type)
{
	return m_enemyData[type];
}

const Stage_Data ShareJsonData::GetStageData()
{
	return m_stageData;
}

const Stage_ClearData ShareJsonData::GetClearData()
{
	return m_clearData;
}

const Game_Parameter ShareJsonData::GetGameParameter()
{
	return m_gameParam;
}

const UI_Data ShareJsonData::GetUIData(std::string tagName)
{

	if (&m_uiDatas[tagName] == nullptr)
	{
		assert("���݂��Ă��Ȃ�UI�f�[�^���Q�Ƃ��Ă��܂�");
	}

	return m_uiDatas[tagName];
}

const Particle2D_Pram ShareJsonData::GetParticle2DPram(std::string tagName)
{
	return m_particlePrams[tagName];
}

void ShareJsonData::StageDataCleanUP()
{

	m_stageData = Stage_Data();

}

SimpleMath::Color ShareJsonData::GetElementColor(ELEMENT element)
{
	return ChangeData::ChangeColor(element);
}
