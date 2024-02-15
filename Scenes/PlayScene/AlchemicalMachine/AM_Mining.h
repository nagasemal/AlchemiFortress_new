//--------------------------------------------------------------------------------------
// File: AM_Mining.h
//
//�@�͈͓��̍z���ɑ΂���
//  ���ʂ𔭊�����
// 
// Date: 2023.5.29
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject3D.h"
#include "AlchemicalMachineObject.h"
#include <Scenes/PlayScene/Mouse/MousePointer.h>

class AM_Mining : public AlchemicalMachineObject
{
public:
	AM_Mining();
	~AM_Mining();

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

	int AllFieldObject(FieldObjectManager* fieldManager);

	void HitEnemy(std::list<EnemyObject>* enemy);

	// �N���X�^������������u�Ԃ𓾂�
	bool GetCrystalFlag();

	void RenderUI() override;

public:

	// �������X�p��
	float m_timer;

private:

};