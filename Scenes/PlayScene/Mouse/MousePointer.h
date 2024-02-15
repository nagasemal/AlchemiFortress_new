//--------------------------------------------------------------------------------------
// File: MousePointer.h
//
// �v���C�V�[����ň����B���݂̃}�E�X�ʒu��|���S���ŕ\��
//
//
// Date: 2023.5.11
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject3D.h"

class Particle;

class MousePointer : public GameObjct3D
{
public:
	MousePointer();
	~MousePointer();

	// ������
	void Initialize()	override;

	// �X�V
	void Update()		override;

	// �`��
	void Draw()			override;

	void ModelDraw(DirectX::Model* model);

	// �I������
	void Finalize()		override;

public:

	void HitMachine(SimpleMath::Vector3 pos);

	// �I�u�W�F�N�g�𓮂����ۂɓ�������
	void ObjectDragMode();

	// �I�u�W�F�N�g�𗣂����ۂɓ�������
	void ReleaseLeftButtom();

private:

	std::unique_ptr<DirectX::Model>				m_mouseCursorModel;

	// �p�[�e�B�N���N���X
	std::unique_ptr<Particle> m_particle;

	float m_time;



};