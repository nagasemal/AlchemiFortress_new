#pragma once

class EnemyObject;

struct MoveParameter
{
	float delay = 0;		// �R�}���h�ڍs����ۂɎ~�߂�ꍇ�͋L�q
	float time	= 0;		// �ғ�����
	float value = 0;		// �s���ɒu���鋭��
};

class ICommand_Enemy
{
public:
	virtual MoveParameter GetParam() = 0;

	virtual bool GetCompletion() = 0;

	virtual void SetCompletion(bool flag) = 0;

	virtual void SetParam(MoveParameter param) = 0;

	virtual void SetEnemyPtr(EnemyObject& object) = 0;

	virtual void Reset() = 0;

	// �������s�֐�
	virtual void Execute() = 0;

	virtual ~ICommand_Enemy() = default;

};