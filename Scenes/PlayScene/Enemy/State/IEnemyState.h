/*
 *	@File	IEnemyState.h
 *	@Brief	�G�l�~�[�N���X�̏�ԃC���^�[�t�F�[�X
 *	@Date	2023-10-26
 *  @Author Nagase
 */

#pragma once
 // �O���錾
class EnemyObject;
class EnemyStateContext;

class IEnemyState
{
public:

	// �G�l�~�[�̌��ݏ�
	enum ENEMY_STATE
	{
		Idoling,
		Moveing,
		Stopping,
		KnockBack,
		Deth,
	};

protected:

	// ���݂̏��
	EnemyStateContext* m_enemyContext = nullptr;

	ENEMY_STATE m_state = ENEMY_STATE::Idoling;

public:

	virtual ~IEnemyState() {}

	// ��Ԃ��Z�b�g����
	void Set_Context(EnemyStateContext* context) { this->m_enemyContext = context; }

	virtual void Update(EnemyObject* object) = 0;
	virtual void Render(EnemyObject* object,Model* model) = 0;
	virtual void RenderIcon(EnemyObject* object) = 0;

	ENEMY_STATE GetState() { return m_state; }

};

class EnemyStateContext
{

private:
	IEnemyState* m_enemyState;

public:
	EnemyStateContext(IEnemyState* state) : 
		m_enemyState(nullptr)
	{
		this->TransitionTo(state);
	}
	~EnemyStateContext() 
	{
		delete m_enemyState; 
	}

	// ���̃X�e�[�g�Ɉڍs����
	void TransitionTo(IEnemyState* state)
	{
		// ��������Ă���ꍇ�Ɍ���s��
		if (this->m_enemyState != nullptr)

			// ���݂̃X�e�[�g������
			delete this->m_enemyState;
			
			this->m_enemyState = state;
			this->m_enemyState->Set_Context(this);

		// �V�����X�e�[�g�ɓ���ւ���
		this->m_enemyState = state;
	}

	/// <summary>
	/// ��Ԃɉ����ĕς��X�V����
	/// </summary>
	void Update(EnemyObject* object) { this->m_enemyState->Update(object); }

	/// <summary>
	/// ��Ԃɉ����ĕς��`�揈��
	/// </summary>
	void Render(EnemyObject* object,Model* model) { this->m_enemyState->Render(object,model); }

	/// <summary>
	/// ��Ԃ���������A�C�R����`��
	/// </summary>
	/// <param name="object"></param>
	void RenderIcon(EnemyObject* object) { this->m_enemyState->RenderIcon(object); }

	/// <summary>
	/// ���݂̏�Ԃ�ENEMY_STATE�ŕԂ�
	/// </summary>
	IEnemyState::ENEMY_STATE GetState() { return this->m_enemyState->GetState(); }
};
