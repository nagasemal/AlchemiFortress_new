//--------------------------------------------------------------------------------------
// File: Field.h
//
// �t�B�[���h�̏���ۗL
// �G���ł铴���@�N���X�^���@�ۗL
//
//  
// Date: 2023.4.19
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject3D.h"
#include "Scenes/PlayScene/Field/Crystal/Crystal.h"
#include "Scenes/PlayScene/Field/FieldObjectType.h"

class Field : public FieldObject
{

public:
	Field();
	~Field();

	// ������
	void Initialize()	override;

	// �X�V
	void Update()		override;

	// �`��
	void Draw()			override;

	void Render(DirectX::Model* model) override;

	void WriteDepth(DirectX::Model* model) override;

	// �I������
	void Finalize()		override;

private:

/*===[�@�A�N�Z�T�@]===*/
public:

	bool		GetHitMouse()		const	{ return m_hitMouseFlag; }

private:

	// �}�E�X�Ƃ̏Փˎ�
	bool		m_hitMouseFlag;

};