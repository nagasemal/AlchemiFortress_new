//--------------------------------------------------------------------------------------
// File: AM_Recovery.h
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

class AM_Recovery : public AlchemicalMachineObject
{
public:
	AM_Recovery();
	~AM_Recovery();

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

	void HitEnemy(std::list<EnemyObject>* enemy);

	void MPPuls(DataManager* pDM);

private:

};