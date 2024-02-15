//--------------------------------------------------------------------------------------
// File: AM_Upper.h
//
//�@�͈͓��̃A���P�~�J���}�V���ɑ΂���
//  �������ʂ𔭊�����
// 
// Date: 2023.5.29
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject3D.h"
#include "AlchemicalMachineObject.h"
#include <Scenes/PlayScene/Mouse/MousePointer.h>

class AM_Upper : public AlchemicalMachineObject
{
public:
	AM_Upper();
	~AM_Upper();

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

	void RenderUI()						override;

	void HitEnemy(std::list<EnemyObject>* enemy);

	void MachinePowerUP(std::vector<std::shared_ptr<AlchemicalMachineObject>> objects);

private:

	// �I���\�I�u�W�F�N�g
	std::unique_ptr<SelectionBox> m_selectBox[4];

	// �񕜂܂ł̎���
	float m_healingTime;

};