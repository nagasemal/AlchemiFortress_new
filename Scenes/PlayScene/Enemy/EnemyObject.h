//--------------------------------------------------------------------------------------
// File: EnemyObject.h
//
//  �G�l�~�[�̓��������@�e�N���X
//  �X�e�[�^�X��ς��邱�ƂŎ�ނ���������
// 
// Date: 2023.6.7
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject3D.h"
#include "Scenes/PlayScene/AlchemicalMachine/AlchemicalMachineObject.h"
#include "NecromaLib/GameData/CommonStruct.h"

#include "Scenes/PlayScene/Enemy/State/EnemyState.h"

class EnemyCommander;
class EnemyStateContext;
class Enemy_StanderMove;
class Enemy_MeanderingMove;
class ICommand_Enemy;
struct Enemy_Data;
class EnemyManager;

class EnemyObject : public GameObjct3D
{
public:
	/// <summary>
	/// �G�l�~�[�𐶐����܂�
	/// </summary>
	/// <param name="type">�G�l�~�[�̎��</param>
	/// <param name="startPos">�����ʒu</param>
	/// <param name="lv">����</param>
	/// <param name="spawnTime">�o���܂ł̎���</param>
	EnemyObject(ENEMY_TYPE type, SimpleMath::Vector3 startPos,int lv,float spawnTime);
	~EnemyObject();

	// ������
	void Initialize()					override;

	// �X�V
	void Update()						override;

	// �`��@(UI�֌W)
	void Draw()							override;

	void Render(Model* model);

	// �I������
	void Finalize()						override;

	// �i�܂Ȃ��悤�ɂ��鏈��
	void HitMachine(bool flag);

	// �o�E���h������
	void Bouns();

// �A�N�Z�T
public:

	// �̗�
	void SetHp(int hp)									{ m_hp = hp; }

	// �^�[�Q�b�g
	void SetTargetPos(SimpleMath::Vector3 targetPos)	{ m_targetPos = targetPos; }

	//�@�ړI�n�܂ł̋���
	void SetLengthVec(SimpleMath::Vector3 lengthVec)	{ m_lengthVec = lengthVec; }

	//�@�~�܂鏈��
	void SetStopFlag(bool flag)							{ m_stopFlag = flag;}

	void SetAliveTimer(float aliveTime)					{ m_aliveTimer = aliveTime; }

	//�@�����x
	void SetAccele(SimpleMath::Vector3 accele)			{ m_accele = accele; }

	//�@�����x���Z
	void AddAccele(SimpleMath::Vector3 accele)			{ m_accele += accele; }

	//�@��]�ݒ�
	void SetRotate(SimpleMath::Quaternion rotation)		{ m_rotation = rotation; }

	//�@���S�t���O
	void SetDethFlag(bool flag) { m_dethFlag = flag; }

	//�@�X�e�[�^�X��ݒ肷��
	void SetEnemyData(Enemy_Data data,EnemyManager* manager);

	//�@�e�ɓ��������ۂ̏���
	void HitBullet(SimpleMath::Vector3 vectol,int power);

	//�@���x��
	const int GetLv()									const{ return m_lv; }
														
	//�@�̗�											
	const int GetHp()									const{ return m_hp; }
														
	//�@EXP											   
	const int GetEXP()									const{ return m_exp; }
														
	//�@�p���[											
	const float GetPower()								const{ return m_power;}
														
	//�@�Ƃ܂��Ă���t���O							  	
	const bool GetStopFlag()							const{ return m_stopFlag; }

	//  �o�������鎞�ԁ@/�@������������
	const float GetAliveTimer()							const { return m_aliveTimer; }
														
	//�@�ړI�n�̈ʒu									
	const SimpleMath::Vector3 GetTargetPos()			const{ return m_targetPos;}
														
	//�@�ړI�n�܂ł̋���								
	const SimpleMath::Vector3 GetLengthVec()			const{ return m_lengthVec;}

	//  ��]
	const SimpleMath::Quaternion GetRotate()			const { return m_rotation;}

	const SimpleMath::Color GetColor()					const { return m_color; }

	//�@
	const SimpleMath::Matrix GetModleMatrix()			const { return m_modelMatrix; }
														
	//�@�����x											
	const SimpleMath::Vector3 GetAccele()				const{ return m_accele;}
														
	//�@���g�̃G�l�~�[�^�C�v							
	const ENEMY_TYPE GetEnemyType()						const{ return m_enemyType; }

	const bool GetMoveType()							const { return m_moveType; }

	const bool GetDethFlag()							const { return m_dethFlag; }

	// �d�͂�������Ȃ�����
	void GravityReset() { m_gravityScale = 0.0f; }


	EnemyObject* GetEnemyObject()						{ return this;}

	EnemyCommander* GetEnemyCommand()					{ return m_commander.get();}

private:

	// �U����
	float m_power;
	// HP
	int m_hp;
	// ���݃��x��
	int m_lv;
	// �o���l
	int m_exp;
	// �������Ă��鎞�� / �o�������̂��̎���
	float m_aliveTimer;
	// �ړ����~�߂�
	bool m_stopFlag;
	// ����
	ELEMENT m_element;

	// �����̎�ށ@true �L�q����Ă��铮����S�ē����ɓ������@false ��������𓮂���
	bool m_moveType;
	// ���g�̃^�C�v
	ENEMY_TYPE m_enemyType;

	SimpleMath::Color m_color;

	// �����x
	SimpleMath::Vector3 m_accele;

	// �d�͉����x
	float m_gravityScale;

	SimpleMath::Vector3 m_moveVec;

	// ��]
	SimpleMath::Quaternion m_rotation;

	SimpleMath::Matrix m_modelMatrix;

	// �ړI�n�܂ł̋���
	SimpleMath::Vector3 m_lengthVec;

	// �ڕW�̈ʒu
	SimpleMath::Vector3 m_targetPos;

	// �R�}���h�N���X��ۑ����Ă����ϒ��z��
	std::vector<ICommand_Enemy*> m_moveCommands;
	// �����̃f�[�^������R�}���h
	std::shared_ptr<EnemyCommander> m_commander;

	// �G�l�~�[�̏�Ԃ��Ǘ�����N���X
	std::shared_ptr<EnemyStateContext> m_stateContext;

	// ���񂾂��Ƃ�ʒm����ϐ�
	bool m_dethFlag;

};