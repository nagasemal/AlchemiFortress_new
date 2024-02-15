#pragma once

#include "ICommand_Enemy.h"

class Enemy_MeanderingMove : public ICommand_Enemy
{
public:
	Enemy_MeanderingMove();
	~Enemy_MeanderingMove();

	// ���s
	void Execute()override;

	MoveParameter GetParam() override;

	bool GetCompletion() override;

	void SetCompletion(bool flag) override;

	void SetParam(MoveParameter param) override;

	void SetEnemyPtr(EnemyObject& object) override;

	void Reset() override;

private:

	MoveParameter m_param;	// �R�}���h�̃p�����[�^
	EnemyObject* m_enemyPtr;	// �Ώۂ̃|�C���^�[

	float m_time;			// �R�}���h���J�n���Ă���o�߂�������
	bool m_completion;		// �R�}���h���I���������Ƃ�m�点��t���O
};