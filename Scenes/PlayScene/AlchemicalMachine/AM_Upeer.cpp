#include "pch.h"
#include "AM_Upper.h"
#include "NecromaLib/GameData/SpriteCutter.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/DeltaTime.h"

#define HEALING_TIME 5.0f

AM_Upper::AM_Upper():
	m_healingTime()
{
}

AM_Upper::~AM_Upper()
{
}

void AM_Upper::Initialize()
{
	m_machineID = MACHINE_TYPE::UPPER;
	m_objectName = "Upper";

	// Json����ǂݎ�����}�V���̃f�[�^��K������
	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	m_hp = m_maxHp = ((int)(pSJD.GetMachineData(m_machineID).hp * (pSJD.GetMachineData(m_machineID).multiplier_hp * m_lv)));

	// ���ʔ͈͂�Lv�ɉ����Č��߂�
	m_magicCircle.r = pSJD.GetMachineData(m_machineID).effect_rage + (pSJD.GetMachineData(m_machineID).multiplier_effect * m_lv);

	m_color = Colors::YellowGreen;

}

void AM_Upper::Update()
{

	// �񕜊J�n�܂ł̎���
	m_healingTime += DeltaTime::GetInstance().GetDeltaTime();

	// Json����ǂݎ�����}�V���̃f�[�^��K������
	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	m_maxHp = ((int)(pSJD.GetMachineData(m_machineID).hp + (pSJD.GetMachineData(m_machineID).multiplier_hp * m_lv)));

	// ���x���̃��Z�b�g
	m_lv = 1;


}

void AM_Upper::SelectUpdate()
{
}

void AM_Upper::Draw()
{
}

void AM_Upper::Finalize()
{

}

void AM_Upper::RenderUI()
{

}

void AM_Upper::HitEnemy(std::list<EnemyObject>* enemy)
{

	if (m_invincibleFlag) return;

	//�@�������݂���G�l�~�[����
	//	���ʔ͈�to�G�l�~�[
	for (std::list<EnemyObject>::iterator it = enemy->begin(); it != enemy->end(); it++)
	{

		// �_�E���L���X�g���s���AGameObject3D�^�ɕϊ�������̏����𓾂�
		bool hitMachine = CircleCollider(GetObject3D(), it->GetObject3D());

		if (hitMachine)
		{
			
			// �̗͌���
			m_hp -= (int)it->GetPower();
			m_invincibleFlag = true;

		}
	}
}

void AM_Upper::MachinePowerUP(std::vector<std::shared_ptr<AlchemicalMachineObject>> objects)
{
	ShareJsonData& pSJD = ShareJsonData::GetInstance();

	for (auto& object : objects)
	{

		if (object.get() == this) continue;

		if (CircleCollider(GetMagicCircle(), object->GetCircle()))
		{
			object->SetLv(object->GetLv() + 1);
			object->SetPowerUpFlag(true);

			// �񕜊J�n
			if (m_healingTime >= HEALING_TIME && object->GetHP() > 0.0f)
			{
				object->SetHP(object->GetHP() + (int)pSJD.GetMachineData(m_machineID).effect_value * m_lv);
			}
		}
	}

	// �񕜒l���Z�b�g
	if (m_healingTime >= HEALING_TIME)
	{
		m_healingTime = 0.0f;
	}

}
