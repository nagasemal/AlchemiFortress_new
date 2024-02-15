#include "pch.h"
#include "AM_Recovery.h"
#include "NecromaLib/GameData/SpriteCutter.h"
#include "NecromaLib/Singleton/SpriteLoder.h"

#include "NecromaLib/Singleton/ShareJsonData.h"

AM_Recovery::AM_Recovery()
{
}

AM_Recovery::~AM_Recovery()
{
}

void AM_Recovery::Initialize()
{

	m_machineID = MACHINE_TYPE::RECOVERY;
	m_objectName = "Recovery";

	// Json����ǂݎ�����}�V���̃f�[�^��K������
	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	m_hp = m_maxHp = ((int)(pSJD.GetMachineData(m_machineID).hp + (pSJD.GetMachineData(m_machineID).multiplier_hp * m_lv)));
	m_machineEffectValue = pSJD.GetMachineData(m_machineID).effect_value;

	m_color = Colors::DarkCyan;
}

void AM_Recovery::Update()
{
	// Json����ǂݎ�����}�V���̃f�[�^��K������
	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	m_maxHp = ((int)(pSJD.GetMachineData(m_machineID).hp + (pSJD.GetMachineData(m_machineID).multiplier_hp * m_lv)));


	m_magicCircle.p = m_data.pos;

	// ���x���̃��Z�b�g
	m_lv = 1;

}

void AM_Recovery::SelectUpdate()
{

}

void AM_Recovery::Draw()
{
}

void AM_Recovery::Finalize()
{
}

void AM_Recovery::RenderUI()
{
}

void AM_Recovery::HitEnemy(std::list<EnemyObject>* enemy)
{

	// TRUE�Ȃ�Α��}�ɒe��
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

void AM_Recovery::MPPuls(DataManager* pDM)
{
	// MP�𑝂₷
	pDM->SetNowMP(pDM->GetNowMP() + (int)(m_lv * m_machineEffectValue));

}
