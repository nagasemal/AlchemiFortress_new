//--------------------------------------------------------------------------------------
// File		: MachineSelectManager.h
//
// �A���P�~�J���}�V���֘A��UI�Ɋւ��N���X�����
// 
// Use		: AlchemicalMachineManager
// Date		: 2023.5.18
// Author	: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/Animation.h"
#include "Scenes/PlayScene/AlchemicalMachine/AlchemicalMachineObject.h"
#include "Scenes/PlayScene/UI/MachineSelect.h"
#include "NecromaLib/GameData/Camera.h"

#include "NecromaLib/GameData/CommonStruct.h"

class FieldObjectManager;
class DisplayMagicCircle;
class UIKeyControl;
class Number;
class Particle_2D;

class MachineSelectManager
{
public:
	MachineSelectManager();
	~MachineSelectManager();

	void TextuerLoader();

	void Initialize();

	// fieldObjecytManager = UI�ɕω���^����I�u�W�F�N�g�̌��o(�N���X�^��)
	void Update(FieldObjectManager* fieldObjectManager);

	void Render();

	void RenderUI(int machineNum[]);

	/// <summary>
	/// ���f����`�悷��
	/// </summary>
	/// <param name="index">�C���f�b�N�X�ԍ�(�}�V���^�C�vID)</param>
	void ModelRender(int index);

	void MagicCircleRender();

	void Finalize();

	// �}�V���A�C�R������
	void RotationMachineList();

	// �}�V��UI�𓮂����{�^���̃A�N�e�B�u�t���O��ύX����
	void LRButtonLock(bool flag);

	// �}�V����B������{�^���̃A�N�e�B�u�t���O��ύX����
	void AlchemiButtonLock(bool flag);

	// UI�Q�̃A���t�@�l��ς��A����������
	void TransparentUI(float transparentVal);

public:

	void SetSelectNoneFlag(bool flag) { m_selectNoneFlag = flag; }

	// �I�𒆂̃}�V���̃^�C�v��Ԃ�
	MACHINE_TYPE GetSelectMachineType()	{ return (MACHINE_TYPE)m_selectNumber; }


	int GetMachineUISelectNumber() { return m_selectNumber; }

	void ChangeSelectMachine(int machineID)							{ m_selectNumber = machineID; m_rotateTime = 0.0f; }

	// �I���{�b�N�X��������Ă��邩��Type�ɉ����ĕԂ�
	bool GetHitMouseToSelectBox(int index)							{ return m_machineSelect[index]->GetHitMouseFlag();}

	// �I���{�b�N�X��Type�ɉ����ĕԂ�
	MachineSelect* GetMachineSelect(int index)						{ return m_machineSelect[index].get();}

	bool GetManufacturingFlag()										{ return m_manufacturingFlag;}

	// ��̗v�f�ł�true�Ȃ�
	bool GetHitMouseToSelectBoxEven()								{ return m_selectBoxAll;}

	// �������j�b�g�ݒu���[�h�t���O
	bool GetAutomaticFlag()											{ return m_automaticFlag; }

	// �B���{�^��
	SelectionBox* GetAlchemiButton(MACHINE_TYPE type)	{ return m_machineSelect[type]->GetMachineBox(); }

	// �B���{�^��
	SelectionBox* GetAlchemiButton()					{ return m_machineSelect[m_selectNumber]->GetMachineBox(); }

private:

	// ���\�[�X�Q�����炷
	void ReduceResource(MACHINE_TYPE type);

private:

	std::unique_ptr<MachineSelect> m_machineSelect[MACHINE_TYPE::NUM];

	std::unique_ptr<UIKeyControl> m_uiKeyControl;

	// ������������
	std::unique_ptr<Number> m_machineNumRender;

	// �K�v���͗ʂ�����
	std::unique_ptr<Number> m_mpNumRender;
	// �K�v�����ʂ�����
	std::unique_ptr<Number> m_crystalRender;

	// �B�����̃G�t�F�N�g_���@�w
	std::unique_ptr<Particle_2D> m_alchemiCircle;
	// �B�����̃G�t�F�N�g_�p�[�e�B�N��
	std::unique_ptr<Particle_2D> m_particle;


	MACHINE_TYPE m_selectMachineType;

	bool m_selectBoxAll;
	bool m_manufacturingFlag;

	bool m_alchemiActiveFlag;

	// �t�B�[���h���None��I�������ۂɁA�S�Ă�MachineSelect�̑I��Box�̐F��ύX����
	bool m_selectNoneFlag;

	// �������j�b�g�ݒu���[�h�t���O
	bool m_automaticFlag;

	//// �I���{�b�N�X(�B���{�^���p)
	//std::unique_ptr<SelectionBox> m_selectionAlchemi;

	// �I���{�b�N�X(�ݒu���[�h�ύX�p)
	std::unique_ptr<SelectionBox> m_modeChangeButton;

	// �}�E�X���͈͂ɓ����Ă��邩�ۂ������o���铖���蔻��N���X
	std::unique_ptr<SelectionBox> m_collider;

	//��ʂɑ傫���o�������閂�@�w
	std::unique_ptr<DisplayMagicCircle>			m_displayMagicCircle;

	// �A�C�R���̉�]���s�����ԕϐ�
	float m_rotateTime;

	// �I�����Ă���}�V���̔ԍ�
	int m_selectNumber;

	// �OFrame�̃}�V���̔ԍ�
	int m_prevSelectNumber;

	// �J�[�\���ɂ����Ă���}�V���̔ԍ�
	int m_cursorMachineNumber;

	// UI��]�����]���ۂ�
	bool m_forwardOrderFlag;

	// UI��������������܂ł̎���
	float m_uiTransparentTime;

	// �}�V��UI�̏o���Ɏg�p����A�j���[�V�����p�ϐ�
	AnimationData m_textAnim;

};