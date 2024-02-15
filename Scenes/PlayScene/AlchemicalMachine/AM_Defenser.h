//--------------------------------------------------------------------------------------
// File: AM_Attacker.h
//
//�@�G�l�~�[����̍U�����󂯎~�߂�A���P�~�J���}�V��
// 
// Date: 2023.5.15
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject3D.h"
#include "AlchemicalMachineObject.h"
#include <Scenes/PlayScene/Mouse/MousePointer.h>

class EnemyManager;

class AM_Defenser : public AlchemicalMachineObject
{
public:
	AM_Defenser();
	~AM_Defenser();

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

	// �G�l�~�[�Ƃ̓����蔻��
	void EnemyHit(std::list<EnemyObject>* enemy);

	// ���ˍU�����s�������ۂ�
	bool CounterAttack();

private:

	// ���Ă��邩�ǂ���
	bool m_isBreak;
	bool m_counterFlag;

};