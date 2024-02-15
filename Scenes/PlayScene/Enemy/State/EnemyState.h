#pragma once
#include "IEnemyState.h"

class MagicCircle;

// �G�l�~�[���X�|�[������O�̏��
// ���@�w���o������
class Enemy_IdlingState : public IEnemyState
{
public:
	Enemy_IdlingState();
	~Enemy_IdlingState() = default;

	void Update(EnemyObject* object)				override;
	void Render(EnemyObject* object,Model* model)	override;
	void RenderIcon(EnemyObject* object)			override;

private:

	std::unique_ptr<MagicCircle> m_magicCircle;

};


// �G�l�~�[���������
class Enemy_MoveingState : public IEnemyState
{
public:
	Enemy_MoveingState();
	~Enemy_MoveingState() = default;

	void Update(EnemyObject* object) override;
	void Render(EnemyObject* object, Model* model) override;
	void RenderIcon(EnemyObject* object)			override;

private:

};

// �G�l�~�[���~�܂���
class Enemy_StoppingState : public IEnemyState
{
public:
	Enemy_StoppingState();
	~Enemy_StoppingState() = default;

	void Update(EnemyObject* object) override;
	void Render(EnemyObject* object,Model* model) override;
	void RenderIcon(EnemyObject* object)			override;

private:

};

// �G�l�~�[���m�b�N�o�b�N���Ă�����(���G��� / �U���͍s���Ȃ�)
class Enemy_KnockBackState : public IEnemyState
{
public:

	/// <summary>
	/// �G�l�~�[��direction�����ɐ�����΂���܂�
	/// </summary>
	/// <param name="direction">������΂������x�N�g��</param>
	/// <param name="power">������΂���</param>
	Enemy_KnockBackState(SimpleMath::Vector3 direction,float power);
	~Enemy_KnockBackState() = default;

	void Update(EnemyObject* object) override;
	void Render(EnemyObject* object,Model* model) override;
	void RenderIcon(EnemyObject* object)			override;

private:

	SimpleMath::Vector3 m_knockBackVec;

};

// �G�l�~�[������ł�����
class Enemy_DethState : public IEnemyState
{
public:

	Enemy_DethState();
	~Enemy_DethState() = default;

	void Update(EnemyObject* object) override;
	void Render(EnemyObject* object,Model* model) override;
	void RenderIcon(EnemyObject* object)			override;

private:

	const float DETH_TIME = 5.0f;

private:

	float m_dethTime;

};