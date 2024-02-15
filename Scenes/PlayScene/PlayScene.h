#pragma once

#include "NecromaLib/SceneObject/SceneObj.h"

#include "NecromaLib/GameData/Camera.h"
#include "Camera/MoveCamera.h"

// �Q�[���̃I�u�W�F�N�g
#include "Field/FieldObjectManager.h"
#include "Mouse/MousePointer.h"
#include "AlchemicalMachine/AlchemicalMachineManager.h"
#include "Enemy/EnemyManager.h"

// �~�b�V����
#include "Scenes/PlayScene/Mission/MissionManager.h"

// UI�֘A
#include "Scenes/PlayScene/UI/BaseLv.h"
#include "Scenes/PlayScene/UI/Gauge.h"
#include "Scenes/PlayScene/Tutorial/OperationInstructions.h"
#include "Scenes/PlayScene/Tutorial/TutorialManager.h"
#include "Scenes/PlayScene/Tutorial/Explanation.h"

// ����|�X�g�v���Z�X
#include "Scenes/Commons/MyPostProcess.h"


class MouseStaging;

class PlayScene : public SceneObj
{
public:
	// �R���X�g���N�^
	PlayScene();

	// �f�X�g���N�^
	~PlayScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// �[�x�`��
	void DrawShadow();

	// UI�n�`��
	void DrawUI() override;

	// �I������
	void Finalize() override;

	void EnemyToAMMachine();
	void EnemyToPlayerBase();
	void EnemyToBullet();

public:

	// �t�B�[���h�}�l�[�W���[�N���X
	FieldObjectManager*			GetFieldManager()				const { return m_fieldManager.get(); }
	//�}�E�X�|�C���^�[�N���X
	MousePointer*				GetMousePointer()				const { return m_mousePointer.get(); }
	//�}�V���}�l�[�W���[�N���X
	AlchemicalMachineManager*	GetAlchemicalMachineManager()	const { return m_AM_Manager.get(); }
	//�G�l�~�[�}�l�[�W���[�N���X
	EnemyManager*				GetEnemyManager()				const { return m_enemyManager.get();}
	//�~�b�V�����}�l�[�W���[�N���X
	MissionManager*				GetMissionManager()				const { return m_missionManager.get();}
	//�Q�[�W�N���X
	Gauge*						GetGauge()						const { return m_resourceGauge.get(); }
	//Lv�N���X
	BaseLv*						GetBaseLv()						const { return m_baseLv.get(); }
	//�����N���X
	Explanation*				GetExplanation()				const { return m_explanation.get(); }
	//�{���{�^���N���X
	SelectionBox*				GetSpeedUpButton()				const { return m_doubleSpeedButton.get(); }
	// �J�����N���X
	MoveCamera*					GetMoveCamrera()				const { return m_moveCamera.get(); }

private:

	// �����UI�Q�̃A���t�@�l��ς��A����������
	void TransparentUI(float transparentVal);

private:

	// �t�B�[���h�ɑ��݂���I�u�W�F�N�g���Ǘ�
	std::unique_ptr<FieldObjectManager>			m_fieldManager;

	// �}�E�X�|�C���^�[�ɂ����鏈��
	std::unique_ptr<MousePointer>				m_mousePointer;

	// �}�V�����j�b�g/�}�V���Ɋ֘A����UI�̊Ǘ�
	std::unique_ptr<AlchemicalMachineManager>	m_AM_Manager;

	// �J�����ɑ΂��鏈��
	std::unique_ptr<MoveCamera>					m_moveCamera;

	// �G�l�~�[���Ǘ�
	std::unique_ptr<EnemyManager>				m_enemyManager;

	// �~�b�V�������Ǘ�
	std::unique_ptr<MissionManager>				m_missionManager;

	// HP,MP,�N���X�^���̃Q�[�W
	std::unique_ptr<Gauge>						m_resourceGauge;

	// EXP�\���Ɏg�p
	std::unique_ptr<BaseLv>						m_baseLv;

	// �`���[�g���A���N���X
	std::unique_ptr<OperationInstructions>		m_operationInstructions;

	// �`���[�g���A���}�l�[�W���[�N���X
	std::unique_ptr<TutorialManager>			m_tutorialManager;

	// �}�E�X��������N���X
	std::unique_ptr<Explanation>				m_explanation;

	// �V�����f��
	std::unique_ptr<Model>						m_skySphere;

	// �{���{�^��
	std::unique_ptr<SelectionBox>				m_doubleSpeedButton; 

	// �}�E�X���͈͂ɓ����Ă��邩�ۂ������o���铖���蔻��N���X
	std::unique_ptr<SelectionBox> m_collider;
	// UI��������������܂ł̎���
	float m_uiTransparentTime;

	// �X�e�[�W�ԍ�
	int m_stageNumber;
	// �ő�X�e�[�W�ԍ�
	int m_maxWaveNum;
	// �{���{��
	int m_doubleSpeedNum;

	// �����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_offscreenRT;

	// �|�X�g�v���Z�X
	std::unique_ptr<MyPostProcess> m_postProcess;

};