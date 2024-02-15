#pragma once

enum ELEMENT : int
{
	NOMAL = 0,
	FLAME = 1,
	AQUA = 2,
	WIND = 3,
	EARTH = 4,
	Num
};

// �~�b�V�����̎��
enum MISSION_TYPE : int
{
	SPAWN,		// �}�V���̐���
	ALCHEMI,	// �}�V���̘B��
	ENEMY_KILL,		// �G�l�~�[�̓���
	BASELV,		// ���_���x��
	RESOURCE,	// ���\�[�X����ʎ擾
	TIMER,		// ����

	MISSION_NUM

};

// �L�[��񋓌^�Ƃ��Ď����Ă�����悤�ɂ���
enum MACHINE_TYPE : int
{
	NONE		= 0,	// �w��Ȃ�
	ATTACKER	= 1,	// �U���^
	DEFENSER	= 2,	// �h��^
	UPPER		= 3,	// �͈͓������^
	RECOVERY	= 4,	// ���͉���^
	MINING		= 5,	// �̌@�^

	NUM
};

enum ENEMY_TYPE : int
{

	ENMEY_NONE = 0,

	SLIME	= 1,	// �ʏ�
	WORM	= 2,	// �֍s
	HOP		= 3,	// �W�����v���Ȃ���
	RETREAT = 4,	// �s���Ė߂�

	ENEMY_NUM
};


namespace ChangeData
{
	// string�`����MACHINE_ELEMENT�ɕϊ�
	static ELEMENT ChangeElement(std::string element)
	{
		ELEMENT elements = ELEMENT::NOMAL;

		if (element == "Nomal") elements = ELEMENT::NOMAL;
		else if (element == "Flame") elements = ELEMENT::FLAME;
		else if (element == "Aqua")	 elements = ELEMENT::AQUA;
		else if (element == "Wind")	 elements = ELEMENT::WIND;
		else if (element == "Earth") elements = ELEMENT::EARTH;

		return elements;
	}

	static std::string ChangeElementString(const ELEMENT element)
	{
		switch (element)
		{
		case NOMAL:
			return "Nomal";
		case FLAME:
			return "Flame";
		case AQUA:
			return "Aqua";
		case WIND:
			return "Wind";
		case EARTH:
			return "Earth";
		default:
			return "Nomal";
		}

	}

	// string�`����MACHINE_TYPE�ɕϊ�
	static MACHINE_TYPE ChangeMachine(const std::string machine)
	{
		MACHINE_TYPE type = MACHINE_TYPE::NONE;

		if (machine == "None")		type = MACHINE_TYPE::NONE;
		else if (machine == "Attacker")	type = MACHINE_TYPE::ATTACKER;
		else if (machine == "Upper")	type = MACHINE_TYPE::UPPER;
		else if (machine == "Defenser")	type = MACHINE_TYPE::DEFENSER;
		else if (machine == "Mining")	type = MACHINE_TYPE::MINING;
		else if (machine == "Recovery")	type = MACHINE_TYPE::RECOVERY;

		return type;
	}

	// MACHINE_TYPE��string�`���ɕϊ�
	static std::string ChangeMachineString(const MACHINE_TYPE type)
	{
		switch (type)
		{
		case NONE:
			return "None";
		case ATTACKER:
			return "Attacker";
		case UPPER:
			return "Upper";
		case DEFENSER:
			return "Defenser";
		case MINING:
			return "Mining";
		case RECOVERY:
			return "Recovery";
		default:
			return "None";
		}

	}

	// string�`����ENEMY_TYPE�ɕϊ�
	static ENEMY_TYPE ChangeEnemy(const std::string enemy_Name)
	{
		ENEMY_TYPE type = ENEMY_TYPE::ENMEY_NONE;

		if (enemy_Name == "None")			type = ENEMY_TYPE::ENMEY_NONE;
		else if (enemy_Name == "Slime")		type = ENEMY_TYPE::SLIME;
		else if (enemy_Name == "Worm")		type = ENEMY_TYPE::WORM;
		else if (enemy_Name == "Hop")		type = ENEMY_TYPE::HOP;
		else if (enemy_Name == "Retreat")	type = ENEMY_TYPE::RETREAT;

		return type;
	}

	// ENEMY_TYPE��string�`���ɕϊ�
	static std::string ChangeEnemyString(const ENEMY_TYPE enemy_Type)
	{

		switch (enemy_Type)
		{
		case ENMEY_NONE:
			return "None";
		case SLIME:
			return "Slime";
		case WORM:
			return "Worm";
		case HOP:
			return "Hop";
		case RETREAT:
			return "Retreat";
		default:
			break;
		}

		return "None";
	}

	// ELEMENT��Color�ɕϊ�
	static SimpleMath::Color ChangeColor(ELEMENT element)
	{
		SimpleMath::Color colors = SimpleMath::Color(0.8f,0.8f,0.8f,1.0f);

		switch (element)
		{
		case NOMAL:
			return SimpleMath::Color(0.8f, 0.8f, 0.8f, 1.0f);
		case FLAME:
			return SimpleMath::Color(1.0f, 0.2f, 0.2f, 1.0f);
		case AQUA:
			return SimpleMath::Color(0.2f, 0.2f, 1.0f, 1.0f);
		case WIND:
			return SimpleMath::Color(0.2f, 1.0f, 0.2f, 1.0f);
		case EARTH:
			return SimpleMath::Color(0.8f, 0.8f, 0.2f, 1.0f);
		default:
			break;
		}

		return colors;
	}
}