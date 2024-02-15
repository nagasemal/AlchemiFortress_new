//--------------------------------------------------------------------------------------
// File: AM_Attacker.h
//
//�@�G�l�~�[���U������A���P�~�J���}�V��
// 
// Date: 2023.5.15
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------


#pragma once
#include "NecromaLib/GameData/GameObject3D.h"
#include "AlchemicalMachineObject.h"
#include "Scenes/PlayScene/Mouse/MousePointer.h"
#include "Scenes/PlayScene/AlchemicalMachine/Bullet/BulletDataBase.h"

class AM_Attacker final : public AlchemicalMachineObject
{
public:

	AM_Attacker();
	~AM_Attacker();

	// ������
	void Initialize()					override;

	// �X�V
	void Update()						override;

	// �I�����ɍX�V����鏈��
	void SelectUpdate()					override;

	// �`��@(UI�֌W)
	void Draw()							override;

	// �I������
	void Finalize()						override;

	void RenderUI() override;

	// �ˏo�̃��N�G�X�g���o��
	bool BulletRequest(std::list<EnemyObject>* enemys);

	// 
	Bullet GetBulletData();

//�@�A�N�Z�T
public:

	const Bullet_Data GetBulletStatus()	const { return m_bulletStatus;}

private:

	float	m_timer;

	Bullet_Data m_bulletStatus;		// �o���b�g�f�[�^
	Bullet_Data m_saveBulletStatus;	// ���H���̃o���b�g�f�[�^

	SimpleMath::Vector3 m_targetPos;

	// �I���\�I�u�W�F�N�g
	std::unique_ptr<SelectionBox> m_selectBox[4];
};