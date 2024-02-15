//--------------------------------------------------------------------------------------
// File: Tutorial.h
//
//�@�`���[�g���A���X�e�[�W�ł���ꍇ�A
//	�Ή������`���[�g���A���摜���o��
// 
// Date: 2023.9.4
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once

#include "NecromaLib/GameData/Animation.h"

class SelectionBox;
class DrawArrow;
class UserInterface;
class DrawLine;
class DrawBox;

class AlchemicalMachineObject;
class MachineExplanation;
class Particle;

class PlayScene;

struct Tutorial_Status;

class OperationInstructions
{
public:
	enum INSTRUCTION_TYPE : int
	{
		NONE = 0,			// �w��Ȃ�
		ATTACKER = 1,		// �U���^
		DEFENSER = 2,		// �h��^
		UPPER = 3,			// �͈͓������^
		RECOVERY = 4,		// ���͉���^
		MINING = 5,			// �̌@�^

		OPERATION = 6,		// ������@
		OPERATION_MACHINE = 7,	// ������@_�}�V��
		MACHINE_UI = 8,		// �}�V��UI�̑���ɂ���

		GAUGE_HP = 9,		// HP�ɂ���
		GAUGE_MP = 10,		// MP�ɂ���
		GAUGE_CRYSTAL = 11,	// �N���X�^���ɂ���

		MISSION = 12,		// �~�b�V�����ɂ���
		ALCHEMI = 13,		// �B���ɂ���
		SPAWN = 14,			// �ݒu�ɂ���

		ROTATE_STOP = 15,
		LINE_SELECT = 16,
		CAMERA_MOVE = 17,

		TUTORIAL = 18,

		NUM
	};

public:
	OperationInstructions();
	~OperationInstructions();

	void Initialize(std::vector<Tutorial_Status> tutorialNumber, PlayScene* pPlayScene);
	void Update(PlayScene* pPlayScene,bool stopFlag = false);
	void Render();
	void Render_Layer2(); // �\���̊֌W�������֐����K�v�ł���������
	void Finalize();

	void CreateInterfase();
	
	bool GetExplanationFlag() { return m_explanationFlag; }

	// �^�C�g���V�[���֌��������߂̃{�^���擾
	SelectionBox* GetTitleSceneButton() { return m_titleSceneBox.get(); }
	// �Z���N�g�V�[���֌��������߂̃{�^���擾
	SelectionBox* GetSelectSceneButton() { return m_selectSceneBox.get(); }
	// �������[�h�Ɉڍs���邽�߂̃{�^���擾
	SelectionBox* GetExplanationButton() { return m_explanationButton.get();}

private:

	std::wstring FileNamePath(const wchar_t* path);

private:

	static const std::vector<const wchar_t*> FILENAME;

	std::unique_ptr<DrawArrow> m_arrowR,m_arrowL;

	// �������[�h�ֈڍs,��������{�^��
	std::unique_ptr<SelectionBox> m_explanationButton;
	// �`���[�g���A�����[�h����������{�^��
	std::unique_ptr<SelectionBox> m_tutorialExitButton;

	// �^�C�g���ɖ߂�I���{�b�N�X
	std::unique_ptr<SelectionBox>	m_titleSceneBox;
	// �Z���N�g�V�[���ɖ߂�I���{�b�N�X
	std::unique_ptr<SelectionBox>	m_selectSceneBox;
	// ������߂ă��U���g�V�[���Ɉڍs����I���{�b�N�X
	std::unique_ptr<SelectionBox>	m_resultSceneBox;

	std::unique_ptr<UserInterface>	m_backFlame;
	std::unique_ptr<UserInterface>	m_textTexture;

	// �������[�h�ɓ����Ă��邩�ۂ�
	bool m_explanationFlag;

	// �`���[�g���A�����[�h�ɓ����Ă��邩�ۂ�
	bool m_cameraFlag;

	// �`���[�g���A�����̃A�j���[�V����
	AnimationData m_tutorialTime;

	int m_selectNumber;

	int m_maxSelectVal;

};