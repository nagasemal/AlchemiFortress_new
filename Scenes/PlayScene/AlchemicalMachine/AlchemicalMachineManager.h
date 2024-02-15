//--------------------------------------------------------------------------------------
// File: AlchemicalMachineManager.h
//
//�@�v���C���[���t�B�[���h���ɐݒu����I�u�W�F�N�g�Q�̃}�l�[�W���[
// 
// Date: 2023.5.11
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include <map>
#include <string>
#include "Scenes/PlayScene/Mouse/MousePointer.h"
#include "Scenes/PlayScene/UI/MachineSelectManager.h"
#include "Scenes/PlayScene/Enemy/EnemyManager.h"
#include "AlchemicalMachineFilter.h"
#include "Scenes/PlayScene/AlchemicalMachine/Bullet/Bullet.h"
#include "Scenes/PlayScene/Field/FieldObjectManager.h"
#include "Scenes/PlayScene/Shadow/DorpShadow.h"
#include "Scenes/PlayScene/Shadow/Particle.h"
#include "Scenes/PlayScene/Shadow/MagicCircle.h"


class AlchemicalMachineObject;
class Number;
class MoveCamera;
class DrawVariableNum;

class AlchemicalMachineManager
{
public:
	AlchemicalMachineManager();
	~AlchemicalMachineManager();

	void Initialize();

	void Update(FieldObjectManager* fieldManager,MousePointer* pMP, EnemyManager* enemys ,MoveCamera* moveCamera);

	void Render();

	void WriteDepath();

	void DrawUI();

	void Finalize();

	void BillboardRenderUI_Start(int index,SimpleMath::Vector3 position);
	void BillboardRenderUI_End();

public:

//�A�N�Z�T
public:

	const bool GetHitMouseFlag(int number)											const { return m_AMObject[number]->GetHitMouse();}

	const std::vector<std::shared_ptr<AlchemicalMachineObject>> GetAlchemicalMachineObject()		const { return m_AMObject; }
	const std::shared_ptr<AlchemicalMachineObject>* GetAlchemicalMachineObject(int index)			const { return &m_AMObject[index];}

	std::list<std::unique_ptr<Bullet>>* GetBullet()									{ return &m_bullets;}

	const std::unique_ptr<MachineSelectManager>* GetMachineSelect()					const { return &m_selectManager; }

	Model* GetSelectModel();

	// �X�e�[�W�f�[�^���烊�\�[�X���U����
	void ReloadResource();

	// �}�V�����ݒu���ꂽ���Ƃ�m�点��t���O
	const MACHINE_TYPE SpawnMachineNotification()									const { return m_spawnMachine; }

	// �}�V����LvUp���ꂽ���Ƃ�m�点��t���O
	const MACHINE_TYPE LvUpMachineNotification()									const { return m_lvUpMachine; }

	// ���݂̃t���[���Ŗ��͂�������ꂽ�ʂ�Ԃ��܂�
	const int GetPulsMpVal()														const { return m_mpPulsVal; }

	// ���݂̃t���[���Ō�����������ꂽ�ʂ�Ԃ��܂�
	const int GetPulsCrystalVal()													const { return m_crystalPulsVal; }

	// ��]��~�̃t���O
	const bool GetRotateStopFlag()													const { return m_rotationStop; }

	// �}�V���̑I��ԍ���ύX����
	void SetSelectMachineNumber(int index) { m_selectNumber = index; }

private:

	// �p�[�e�B�N���̃A�b�v�f�[�g
	void Update_Particle();

	// ��p�̍X�V��������
	void Update_Attacker(int index, EnemyManager* enemyManager);

	void Update_Defenser(int index, EnemyManager* enemyManager);

	void Update_Mining(int index, FieldObjectManager* fieldManager, EnemyManager* enemyManager);

	void Update_Recovery(int index, EnemyManager* enemyManager);

	void Update_Upper(int index, EnemyManager* enemyManager);

	// ��
	void MovingMachine(int number);

	// �~�`��ɃA���P�~�J���}�V��(None)�𖢎g�p��Ԃŕ��ׂ�B
	void CreateAMMachine();

	// ���ׂ��A���P�~�J���}�V����lineNumber�ɉ����Ďg�p�\��ԂɕύX����
	void LvToObjectActives(int lineNumber);

	void SpawnAMMachine(bool leftButtom);

	// ��̎�����(None�ɂ��ǂ�)
	void Dismantling(int index);

	// Json�f�[�^����ǂݎ�������\�[�X�𔽉f������
	void JsonLoadResources();

private:

	// �~����ɕ��ׂ鏈��
	SimpleMath::Vector3 SetVelocityCircle(int index, int max, float range)
	{

		float radian = XM_2PI / static_cast<float>(max);

		// ��̊p�x��������΂����S���킩��
		float x = range * cosf(radian * index);
		float z = range * sinf(radian * index);

		SimpleMath::Vector3 pos = { x,0,z};

		return pos;
	}

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �A���P�~�J���}�V���I���{�b�N�X�̕\��
	std::unique_ptr<MachineSelectManager> m_selectManager;

	// �A���P�~�J���}�V���m��
	std::vector<std::shared_ptr<AlchemicalMachineObject>> m_AMObject;

	// �A���P�~�J���}�V��(�A�^�b�N�^�C�v)����ˏo�����e�̃��X�g
	std::list<std::unique_ptr<Bullet>>	m_bullets;

	// �A���P�~�J���}�V�����f���̎󂯓n��
	std::unique_ptr<AlchemicalMachineFilter> m_AMFilter;

	//===��ŏ����e�X�g�p�ϐ�
	std::unique_ptr<DirectX::GeometricPrimitive> m_testBox;	//  ���u���e���f��

	// �ۉe
	std::unique_ptr<DorpShadow> m_dorpShadow;

	// ���@�w�N���X(�}�V��)
	std::unique_ptr<MagicCircle> m_magicCircle;

	// ���@�w�N���X(�t�B�[���h)
	std::unique_ptr<MagicCircle> m_magicCircle_Field;


	// �p�[�e�B�N���N���X
	std::unique_ptr<Particle> m_particle_hit;
	// �ݒu��		�p�[�e�B�N��
	std::unique_ptr<Particle> m_particle_Put;
	// �K�[�h��		�p�[�e�B�N��
	std::unique_ptr<Particle> m_particle_Gurd;
	// ���͉����	�p�[�e�B�N��
	std::unique_ptr<Particle> m_particle_Recovery;
	// ���������	�p�[�e�B�N��
	std::unique_ptr<Particle> m_particle_Mining;
	// �e�̋O��		�p�[�e�B�N��
	std::unique_ptr<Particle> m_particle_Bullet;

	bool m_allHitObjectToMouse;

	// ��]���~�߂�
	bool m_rotationStop;

	// ���ݑI������Ă���I�u�W�F�N�g�̔ԍ�
	int m_selectNumber;
	SimpleMath::Vector3 m_prevSelectMachinePos;

	// Mp���ǉ������܂ł̎���
	float m_mpPulsTimer;

	// �O��̃}�E�X�z�C�[���̐��l
	int m_saveWheelValue;
	int m_scrollValue;

	// �}�V�����ݒu���ꂽ���Ƃ�ʒm����ϐ�
	MACHINE_TYPE m_spawnMachine;

	// �}�V����LvUp���ꂽ���Ƃ�ʒm����ϐ�
	MACHINE_TYPE m_lvUpMachine;

	// ���ݕۗL���Ă���A���P�~�J���}�V���̌�
	int m_AMnums[MACHINE_TYPE::NUM];

	// ���̓��\�[�X���񕜂�������
	int m_mpPulsVal;

	// �������\�[�X���񕜂�������
	int m_crystalPulsVal;

};