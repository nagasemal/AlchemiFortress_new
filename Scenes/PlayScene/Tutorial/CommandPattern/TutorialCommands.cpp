#include "pch.h"
#include "TutorialCommands.h"

#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/Singleton/ShareJsonData.h"

#include "Scenes/PlayScene/UI/SelectionBox.h"
#include "Scenes/Commons/DrawVariableNum.h"

#include "Scenes/Commons/DrawBox.h"
#include "Scenes/Commons/DrawArrow.h"

#include "Scenes/PlayScene/Tutorial/CommandPattern/ICommand_Tutorial.h"
#include "Scenes/PlayScene/Tutorial/TutorialManager.h"
#include "Scenes/PlayScene/PlayScene.h"


// ==�Ȃɂ����Ȃ��R�}���h=========================

Tutorial_None::Tutorial_None()
{
	Reset();
}

Tutorial_None::~Tutorial_None()
{
}

void Tutorial_None::Initialize()
{
	m_initializeFlag = true;
}

void Tutorial_None::Execute()
{}

void Tutorial_None::Finalize()
{
}

void Tutorial_None::Reset()
{
}


// ==�}�V��UI�؂�ւ��������U���R�}���h=========================

Tutorial_MachineUI::Tutorial_MachineUI(MACHINE_TYPE machineType, bool selectFlag) :
	m_machineType(machineType),
	m_selectFlag(selectFlag)
{
	Reset();
}

Tutorial_MachineUI::~Tutorial_MachineUI()
{
}

void Tutorial_MachineUI::Initialize()
{
	if (m_initializeFlag) return;

	Reset();

	// �}�V���Z���N�g�̃|�C���^�[���擾����
	auto machineSlectManager = m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager()->GetMachineSelect()->get();

	m_tutorialManager->GetDisplayBox()->ResetAnimationData();

	// �w��̃}�V����UI��؂�ւ���
	if (m_selectFlag)
	{
		machineSlectManager->ChangeSelectMachine(m_machineType);
	}

	// True�Ȃ�ΑI���̉ߒ����͂��܂Ȃ�
	m_completion = m_selectFlag;

	m_initializeFlag = true;

}

void Tutorial_MachineUI::Execute()
{
	if (m_completion) return;

	m_tutorialManager->GetDisplayBox()->SetPosRage(SimpleMath::Vector2(1120, 550),SimpleMath::Vector2(50.0f,50.0f));

	// �����U���p�{�b�N�X�̕`��,�A�j���[�V����,�X�V�������s��
	m_tutorialManager->GetDisplayBox()->SetActiveFlag(true);
	m_tutorialManager->GetDisplayBox()->Update();

	// �����U���{�b�N�X���N���b�N���ꂽ�玟�̃R�}���h�����s����
	if (m_tutorialManager->GetDisplayBox()->ClickMouse())
	{
		m_completion = true;
	}

}

void Tutorial_MachineUI::Finalize()
{
}

void Tutorial_MachineUI::Reset()
{
	m_completion		= false;
	m_initializeFlag	= false;
}

// ==�B���{�^���ւ̎����U���R�}���h=========================

Tutorial_AlchemiUI::Tutorial_AlchemiUI(MACHINE_TYPE machineType, int maxCount):
	m_machineType(machineType),
	m_alchemiCount(maxCount)
{

	Reset();

}

Tutorial_AlchemiUI::~Tutorial_AlchemiUI()
{
}

void Tutorial_AlchemiUI::Initialize()
{
	if (m_initializeFlag) return;

	Reset();

	m_tutorialManager->GetDisplayBox()->ResetAnimationData();

	m_initializeFlag = true;

	// �}�V���Z���N�g�̃|�C���^�[���擾����
	auto machineSlectManager = m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager()->GetMachineSelect()->get();

	//�@====================[�@�A�N�e�B�u�t���O�̕ύX�@]
	// �S�Ĉ�x�A�N�e�B�u��Ԃ�����
	for (int i = 0; i < MACHINE_TYPE::NUM; i++)
	{
		machineSlectManager->GetMachineSelect((MACHINE_TYPE)i)->SetTutorialLockUI(false);

	}
	// �w��̕��������ɖ߂�
	machineSlectManager->GetMachineSelect(m_machineType)->SetTutorialLockUI(true);

}

void Tutorial_AlchemiUI::Execute()
{
	if (m_completion) return;

	auto machineSelectManager = m_tutorialManager->GetPlayScene()->
		GetAlchemicalMachineManager()->
		GetMachineSelect()->get();

	m_tutorialManager->GetDisplayBox()->SetPosRage(machineSelectManager->GetAlchemiButton(m_machineType)->GetPos(), SimpleMath::Vector2(50.0f, 50.0f));

	// �����U���p�{�b�N�X�̕`��,�A�j���[�V����,�X�V�������s��
	m_tutorialManager->GetDisplayBox()->SetActiveFlag(true);
	m_tutorialManager->GetDisplayBox()->Update();

	// �p�[�e�B�N������
	m_tutorialManager->GetAlchemiParticle()->Update("BoxBig", m_tutorialManager->GetDisplayBox()->GetPos(), true);

	// �B�������������񐔂��w��J�E���g�𒴂����玟�̃R�}���h�Ɉڂ�
	if (machineSelectManager->GetManufacturingFlag())
	{
		m_alchemiCount--;
		if (m_alchemiCount <= 0)  m_completion = true;

		//�@====================[�@�A�N�e�B�u�t���O�̕ύX�@]
		// �S�Ĉ�x�A�N�e�B�u��Ԃ�����
		for (int i = 0; i < MACHINE_TYPE::NUM; i++)
		{
			machineSelectManager->GetMachineSelect((MACHINE_TYPE)i)->SetTutorialLockUI(false);

		}

	}

}

void Tutorial_AlchemiUI::Finalize()
{
}

void Tutorial_AlchemiUI::Reset()
{
	m_initializeFlag = false;

}


// ==�X�|�[���O�̃G�l�~�[�̖��@�w�����鎋���U���R�}���h=========================

Tutorial_EnemySpawn::Tutorial_EnemySpawn(float time):
	m_maxTime(time)
{
	Reset();
}

Tutorial_EnemySpawn::~Tutorial_EnemySpawn()
{
}

void Tutorial_EnemySpawn::Initialize()
{
	if (m_initializeFlag) return;

	auto camera = m_tutorialManager->GetPlayScene()->GetMoveCamrera();
	auto enemyManager = m_tutorialManager->GetPlayScene()->GetEnemyManager();

	camera->SetTargetProsition(enemyManager->GetEnemyData()->begin()->GetPos());

	m_initializeFlag = true;
}

void Tutorial_EnemySpawn::Execute()
{
	if (m_completion) return;

	auto enemyManager = m_tutorialManager->GetPlayScene()->GetEnemyManager();
	auto camera = m_tutorialManager->GetPlayScene()->GetMoveCamrera();

	camera->SetCameraLock(true);
	camera->SetTargetProsition(enemyManager->GetEnemyData()->begin()->GetPos());

	m_maxTime -= DeltaTime::GetInstance().GetDeltaTime();

	if (m_maxTime <= 0)
	{
		camera->SetCameraLock(false);
		m_completion = true;

	}

}

void Tutorial_EnemySpawn::Finalize()
{
}

void Tutorial_EnemySpawn::Reset()
{
	m_initializeFlag = false;

}


// ==�w��̃}�V���̑ϋv�l��0�ɂ���R�}���h=========================

Tutorial_MachineBreak::Tutorial_MachineBreak(MACHINE_TYPE machineType):
	m_machineType(machineType)
{
	Reset();
}

Tutorial_MachineBreak::~Tutorial_MachineBreak()
{
}

void Tutorial_MachineBreak::Initialize()
{
	if (m_initializeFlag) return;

	// ���͒l��None�ł���ΑS�Ẵ}�V���̑ϋv�l��0�ɂ���
	if (m_machineType == MACHINE_TYPE::NONE)
	{
		for (auto& machine : m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager()->GetAlchemicalMachineObject())
		{
			machine->SetHP(0);
		}
	}
	else
	{

		// �w��̃}�V����T���o��
		for (auto& machine : m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager()->GetAlchemicalMachineObject())
		{
			// �w��̃}�V���ł���Αϋv�l��0�ɂ��� �ȍ~�͍s��Ȃ�
			if (machine->GetModelID() == m_machineType && machine->GetHP() >= 0.0f)
			{
				machine->SetHP(0);

				break;
			}
		}
	}
	m_completion = true;
	m_initializeFlag = true;
}

void Tutorial_MachineBreak::Execute()
{
	if (m_completion) return;

}

void Tutorial_MachineBreak::Finalize()
{
}

void Tutorial_MachineBreak::Reset()
{
	m_initializeFlag = false;

}


// ==�w��̃}�V���̑ϋv�l��S�񕜂���R�}���h=========================

Tutorial_MachineRepia::Tutorial_MachineRepia(MACHINE_TYPE machineType):
	m_machineType(machineType)
{
	Reset();
}

Tutorial_MachineRepia::~Tutorial_MachineRepia()
{
}

void Tutorial_MachineRepia::Initialize()
{
	if (m_initializeFlag) return;

	// ���͒l��None�ł���ΑS�Ẵ}�V���̑ϋv�l��0�ɂ���
	if (m_machineType == MACHINE_TYPE::NONE)
	{
		for (auto& machine : m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager()->GetAlchemicalMachineObject())
		{
			machine->SetHP(machine->GetMAXHP());
		}
	}
	else
	{

		// �w��̃}�V����T���o��������񕜂���
		for (auto& machine : m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager()->GetAlchemicalMachineObject())
		{
			// �w��̃}�V���ł���Αϋv�l��0�ɂ��� �ȍ~�͍s��Ȃ�
			if (machine->GetModelID() == m_machineType && machine->GetHP() <= machine->GetMAXHP())
			{
				machine->SetHP(machine->GetMAXHP());

				break;
			}
		}
	}
	m_completion = true;
	m_initializeFlag = true;
}

void Tutorial_MachineRepia::Execute()
{
}

void Tutorial_MachineRepia::Finalize()
{
}

void Tutorial_MachineRepia::Reset()
{
}

Tutorial_UppperSelect::Tutorial_UppperSelect(int spawnNum):
	m_particleTime(),
	m_spawnNum(spawnNum)
{
	Reset();
}

Tutorial_UppperSelect::~Tutorial_UppperSelect()
{
}

void Tutorial_UppperSelect::Initialize()
{
	if (m_initializeFlag) return;

	m_initializeFlag = true;
}

void Tutorial_UppperSelect::Execute()
{
	if (m_completion)return;

	auto machineManager = m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager();
	auto machineArray = machineManager->GetAlchemicalMachineObject();

	m_particleTime += DeltaTime::GetInstance().GetDeltaTime();


	if (machineManager->SpawnMachineNotification() == MACHINE_TYPE::UPPER)
	{
		m_spawnNum--;
	}

	if (m_spawnNum <= 0)
	{
		m_completion = true;
	}

	if (m_particleTime <= PARTICLE_TIME) return;

	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	// �~�̑傫�����A�b�p�[�}�V���Ɠ����ɂ���
	float circleRage = pSJD.GetMachineData(MACHINE_TYPE::UPPER).effect_rage * (pSJD.GetMachineData(MACHINE_TYPE::UPPER).multiplier_effect);

	for (auto& noneMachine : machineArray)
	{
		// None�ł���Γ���
		if (noneMachine->GetModelID() != MACHINE_TYPE::NONE) continue;

		// �A�N�e�B�u�ł���Γ���
		if (!noneMachine->GetActive()) continue;

		// �����蔻��Ɏg�p����~���
		Circle nonePosData = noneMachine->GetCircle();
		nonePosData.r = circleRage;

		for (auto& machine_B : machineArray)
		{

			// Attacker�ł���Γ���
			if (machine_B->GetModelID() != MACHINE_TYPE::ATTACKER) continue;

			// �}�V��To�}�V��
			// Upper�}�V���̔����������None�}�V����Attacker�}�V���̓����蔻��
			if (CircleCollider(nonePosData, machine_B->GetCircle()))
			{
				m_tutorialManager->GetParticle()->OnShot(nonePosData.p, true,SimpleMath::Color(1.0f,1.0f,0.0f,0.5f));
			}

		}
	}

	m_particleTime = 0.0f;

}

void Tutorial_UppperSelect::Finalize()
{
}

void Tutorial_UppperSelect::Reset()
{
	m_particleTime = 0;
}

Tutorial_NoneSelect::Tutorial_NoneSelect(int spawnNum):
	m_particleTime(),
	m_spawnNum(spawnNum)
{
	Reset();
}

Tutorial_NoneSelect::~Tutorial_NoneSelect()
{
}

void Tutorial_NoneSelect::Initialize()
{
}

void Tutorial_NoneSelect::Execute()
{
	if (m_completion)return;

	auto machineManager = m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager();
	auto machineArray = machineManager->GetAlchemicalMachineObject();

	m_particleTime += DeltaTime::GetInstance().GetDeltaTime();

	if (machineManager->SpawnMachineNotification() != MACHINE_TYPE::NONE)
	{
		m_spawnNum--;
	}

	if (m_spawnNum <= 0)
	{
		m_completion = true;

		for (auto& noneMachine : machineArray)
		{
			// �N���b�N�U���\����؂�
			noneMachine->SetClickPromptFlag(false);
		}

		return;
	}

	if (m_particleTime <= PARTICLE_TIME) return;

	for (auto& noneMachine : machineArray)
	{
		// None�ł���Γ���
		if (noneMachine->GetModelID() != MACHINE_TYPE::NONE) continue;

		// �A�N�e�B�u�ł���Γ���
		if (!noneMachine->GetActive()) continue;
		
		// �p�[�e�B�N���\��
		m_tutorialManager->GetParticle()->OnShot(noneMachine->GetPos(), true, SimpleMath::Color(1.0f, 1.0f, 0.0f, 0.5f));

		// �N���b�N�U���\��
		noneMachine->SetClickPromptFlag(true);
	}

	m_particleTime = 0.0f;

}

void Tutorial_NoneSelect::Finalize()
{
}

void Tutorial_NoneSelect::Reset()
{
	m_particleTime = PARTICLE_TIME;
}




Tutorial_LockMachineUI::Tutorial_LockMachineUI(bool activeFlag):
	m_activeFlag(activeFlag)
{
	Reset();
}

Tutorial_LockMachineUI::~Tutorial_LockMachineUI()
{
}

void Tutorial_LockMachineUI::Initialize()
{
	if (m_initializeFlag) return;

	// ���EUI�ړ��������Ȃ�����
	m_tutorialManager->GetPlayScene()->GetAlchemicalMachineManager()->GetMachineSelect()->get()->LRButtonLock(m_activeFlag);

	m_initializeFlag = true;
	m_completion = true;
}

void Tutorial_LockMachineUI::Execute()
{
	if (m_completion) return;

	m_completion = true;
}

void Tutorial_LockMachineUI::Finalize()
{
}

void Tutorial_LockMachineUI::Reset()
{
}

Tutorial_TextArrow::Tutorial_TextArrow(int type):
	m_type(type)
{
	Reset();
}

Tutorial_TextArrow::~Tutorial_TextArrow()
{
}

void Tutorial_TextArrow::Initialize()
{
	if (m_initializeFlag) return;

	m_tutorialManager->GetDisplayBox()->ResetAnimationData();

	m_initializeFlag = true;
}

void Tutorial_TextArrow::Execute()
{

	SimpleMath::Vector2 arrowPos = SimpleMath::Vector2();

	if (m_type == 0)
	{
		arrowPos = m_tutorialManager->GetTextArrow_left()->GetPos();

	}
	else if (m_type == 1)
	{
		arrowPos = m_tutorialManager->GetTextArrow_right()->GetPos();
	}

	m_tutorialManager->GetDisplayBox()->SetPosRage(arrowPos, SimpleMath::Vector2(20.0f, 20.0f));

	// �����U���p�{�b�N�X�̕`��,�A�j���[�V����,�X�V�������s��
	m_tutorialManager->GetDisplayBox()->SetActiveFlag(true);
	m_tutorialManager->GetDisplayBox()->Update();

	// �p�[�e�B�N������
	m_tutorialManager->GetArrowParticle()->Update("BoxSmall", m_tutorialManager->GetDisplayBox()->GetPos(), true);

	// �����U���{�b�N�X���N���b�N���ꂽ�玟�̃R�}���h�����s����
	if (m_tutorialManager->GetDisplayBox()->ClickMouse())
	{
		m_completion = true;
	}

}

void Tutorial_TextArrow::Finalize()
{
}

void Tutorial_TextArrow::Reset()
{
}

Tutorial_LockAlchemi::Tutorial_LockAlchemi(bool activeFlag):
m_activeFlag(activeFlag)
{
	Reset();
}

Tutorial_LockAlchemi::~Tutorial_LockAlchemi()
{
}

void Tutorial_LockAlchemi::Initialize()
{
	if (m_initializeFlag) return;

	// �B���������Ȃ�����
	m_tutorialManager->GetPlayScene()->
	GetAlchemicalMachineManager()->
	GetMachineSelect()->get()->AlchemiButtonLock(m_activeFlag);

	m_initializeFlag = true;
	m_completion = true;

}

void Tutorial_LockAlchemi::Execute()
{
	if (m_completion) return;
	m_completion = true;
}

void Tutorial_LockAlchemi::Finalize()
{
}

void Tutorial_LockAlchemi::Reset()
{
}