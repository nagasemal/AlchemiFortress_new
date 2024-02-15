//--------------------------------------------------------------------------------------
// File: Crystal.h
//
// ���\�[�X�Q�@MiningType�̃A���P�~�J���}�V�����G���ƌ������\�[�X��������
//
//  
// Date: 2023.6.13
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject3D.h"
#include "Scenes/PlayScene/Field/FieldObjectType.h"

class Crystal : public FieldObject
{
public:
	Crystal(SimpleMath::Vector3 pos,float rotateY);
	~Crystal();

	// ������
	void Initialize()					override;

	// �X�V
	void Update()						override;

	// �`��
	void Draw()							override;

	// �I������
	void Finalize()						override;

	// ���f���`��
	void Render(Model* model)			override;

	void WriteDepth(DirectX::Model* model) override;

	// �e�N���X�ɏ����������s�킹��
	bool DeleteRequest();

	bool GetHitMouse();

public:

	// �I�u�W�F�N�g�^�C�v��n��
	OBJECT_TYPE GetObjectType() { return m_type; }

private:

	float m_rotateY;

	bool m_selectFlag;

	OBJECT_TYPE m_type;
	
};