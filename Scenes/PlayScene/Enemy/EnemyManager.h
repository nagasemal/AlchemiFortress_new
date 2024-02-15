//--------------------------------------------------------------------------------------
// File: EnemyManager.h
//
// �G�l�~�[�̃}�l�[�W���[
//  
// 
// Date: 2023.6.7
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "EnemyObject.h"
#include "Scenes/PlayScene/Shadow/Particle.h"
#include <list>

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	/// <summary>
	/// �J�n,����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="basePos">�^�[�Q�b�g�ƂȂ�n�_</param>
	void Update(SimpleMath::Vector3 basePos);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

	/// <summary>
	/// �G�l�~�[�̏㕔�ɕ\������r���{�[�h���ꂽ�A�C�R�����o������
	/// </summary>
	void RenderUI();
	
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �G�l�~�[�̃f�[�^���ēx�ǂݎ��
	/// </summary>
	void ReloadEnemyData();

	/// <summary>
	/// �G�l�~�[�𐶐�����
	/// </summary>
	/// <param name="type">�G�l�~�[�̎��</param>
	/// <param name="spawnNumber">�o������</param>
	/// <returns></returns>
	EnemyObject CreateEnemy(ENEMY_TYPE type,int spawnNumber);

	/// <summary>
	/// �G�l�~�[�������_���ŋK�萔��������
	/// </summary>
	/// <returns></returns>
	EnemyObject GetRandomEnemy();

	/// <summary>
	/// �}�V���Ɠ��������ۂ̏���
	/// </summary>
	/// <param name="alchemicalMachines">�}�V���̃|�C���^</param>
	void HitAMObejct(AlchemicalMachineObject* alchemicalMachines);

	/// <summary>
	/// �G�l�~�[���|���ꂽ�ۂɓ����o���l
	/// </summary>
	/// <returns></returns>
	int GetNockDownEnemyExp();

	/// <summary>
	/// �����̃R�}���h�𐶐�����
	/// </summary>
	/// <param name="moveName">�����̖��O</param>
	/// <returns></returns>
	ICommand_Enemy* CreateEnemyMoveCommand(const std::string moveName);

public:


	const int GetKnokDownEnemyFlag() const { return m_knokDownFlag; }
	const ENEMY_TYPE GetKnokDownEnemyType() const { return m_knokDownEnemyType; }
	std::list<EnemyObject>* GetEnemyData() { return m_enemyObject.get(); }

private:

	std::unique_ptr<std::list<EnemyObject>> m_enemyObject;

	//===��ŏ����e�X�g�p�ϐ�
	std::unique_ptr<DirectX::GeometricPrimitive> m_testBox;	//  ���u���l�p���f��

	std::unique_ptr<DirectX::Model> m_enemyModel;

	// �p�[�e�B�N���N���X
	std::unique_ptr<Particle> m_particle_spawn;
	std::unique_ptr<Particle> m_particle_delete;

	// ���E���h�i�s
	float m_nextEnemyTime;

	float m_timer;
	float m_totalTimer;

	// �|���ꂽ�u�Ԃ��擾����t���O(1F���ɕ����̓|���Ɛ���ȏ������s���Ȃ��ׁAint�^�ŊǗ�)
	int m_knokDownFlag;
	ENEMY_TYPE m_knokDownEnemyType;

	// 1F�Ԃɉ҂���EXP�̑���
	int m_falmeTotalEnemyExp;

	int m_enemyNums;

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

};