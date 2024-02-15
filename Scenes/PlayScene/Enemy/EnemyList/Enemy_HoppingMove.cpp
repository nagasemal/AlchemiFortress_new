#include "pch.h"
#include "Enemy_HoppingMove.h"

#include "Scenes/PlayScene/Enemy/EnemyObject.h"
#include "NecromaLib/GameData/Easing.h"
#include "NecromaLib/Singleton/DeltaTime.h"

Enemy_HoppingMove::Enemy_HoppingMove() :
	m_completion(),
	m_time(),
	m_enemyPtr(nullptr),
	m_param(),
	m_hoppingVal()
{
}

Enemy_HoppingMove::~Enemy_HoppingMove()
{
}

void Enemy_HoppingMove::Execute()
{
	m_time += DeltaTime::GetInstance().GetDeltaTime();

	// �f�B���C���Ԃ�����܂ł͏������s��Ȃ�
	if (m_time <= m_param.delay || m_enemyPtr->GetStopFlag()) return;

	// ���x�̌v�Z
	SimpleMath::Vector3 accele = SimpleMath::Vector3(0.0f, m_hoppingVal, 0.0f);

	// ��ԗ�
	m_hoppingVal -= DeltaTime::GetInstance().GetDeltaTime();

	m_enemyPtr->SetAccele(m_enemyPtr->GetAccele() + SimpleMath::Vector3(0.0f, m_hoppingVal, 0.0f));

	// �ғ�����
	m_completion = m_time >= m_param.time;

	// �n�ʂɕt�����������x���
	if (m_hoppingVal <= -m_param.value || m_enemyPtr->GetPos().y <= 0.0f)
	{
		m_hoppingVal = m_param.value;
	}
}

MoveParameter Enemy_HoppingMove::GetParam()
{
	return m_param;
}

bool Enemy_HoppingMove::GetCompletion()
{
	return m_completion;
}

void Enemy_HoppingMove::SetCompletion(bool flag)
{
	m_completion = flag;
}


void Enemy_HoppingMove::SetParam(MoveParameter param)
{
	m_param.delay = param.delay;
	m_param.time = param.time;
	m_hoppingVal = m_param.value = param.value;

}

void Enemy_HoppingMove::SetEnemyPtr(EnemyObject& object)
{
	m_enemyPtr = &object;
}

void Enemy_HoppingMove::Reset()
{
	m_hoppingVal = m_param.value;
	m_time = 0.0f;

}
