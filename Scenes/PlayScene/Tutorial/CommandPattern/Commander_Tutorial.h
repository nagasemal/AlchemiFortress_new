#pragma once

//#include "ICommand_Tutorial.h"
#include <vector>

class ICommand_Tutorial;

class TutorialCommander
{

public:
	enum TutorialType :int
	{
		NONE,						// �`���[�g���A���������Ȃ�
		ATTACKER_UI,				// �}�V��UI�ւ̗U�����s��
		DEFENSER_UI,				// �f�B�t�F���T�[�}�V��UI�ւ̗U�����s��
		UPPER_UI,					// �A�b�p�[�}�V��UI�ւ̗U�����s��
		RECOVERY_UI,				// ���J�o���[�}�V��UI�ւ̗U�����s��
		MINING_UI,					// �}�C�j���O�}�V��UI�ւ̗U�����s��

		ALCHEMI_UI,					// �B���{�^��UI�ւ̗U�����s��

		STOP_GAME_CLICK,			// �Q�[���̐i�s���~�߂�(�N���b�N�ŉ���)
		ROTATION,					// ��]���~�߂�,�J�n����
		INSTALLATION,				// �}�V���̐V�K�ݒu���~�߂�,�J�n����

		STAY_TIME,					// �w��b���`���[�g���A���̍X�V�������~�߂�

		STOP_MACHINE,				// 
		START_MACHINE,				// �}�V���̐V�K�ݒu���\�ɂ���

		LR_BUTTON_LOCK,				// �}�V��UI�̈ړ��𐧌�����

		NONE_MACHINE_SELECT,		// �m�[���}�V���ւ̎����U�����s��
		PROPHERAL_ATTACKER_MACHINE,	// �A�^�b�J�[�}�V�����ӂ̃}�V���Ɏ����U��������
		ENEMY_ATTENTION,			// �G�l�~�[�o���ʒu�Ɏ����U�����s��
		BREAK_MACHINE,				// �}�V����j�󂷂�
		REPAIR_MACHINE,				// �}�V�����C�U����

		TEXT_ARROW,					// �`���[�g���A���̃e�L�X�g�𗬂�

		ALCHEMI_LOCK,				// �B���{�^�������b�N/��������

		TRANSPARENT_START_UI,		// UI�Q�𓧖���
		TRANSPARENT_END_UI,			// UI�Q�̓���������

	};

public:

	std::vector<ICommand_Tutorial*> GetCommand() { return m_commands; }

	// �R�}���h��ǉ�����
	void AddCommand(ICommand_Tutorial* command, TutorialManager* object)
	{
		command->SetTutorialManagerPtr(object);
		m_commands.push_back(command);
	}

public:

	TutorialCommander() { m_commandNumber = 0; }
	~TutorialCommander() 
	{
	};

	// �S�ē����ɉ�
	void Execute_ALL()
	{

		for (auto& command : m_commands)
		{
			command->Execute();
		}

	};	

	// �z�񏇂ɉ񂵁A�����������͉̂񂳂Ȃ�
	void Execute_One()
	{
		int counter = 0;

		// ���������������玟�̃R�}���h�ֈڍs����
		for (auto& command : m_commands)
		{
			counter += command->GetCompletion();

			// �I���������s��
			if (command->GetCompletion())
			{
				command->Finalize();
			}

		}

		if (counter >= m_commands.size()) return;

		m_commands[counter]->Initialize();
		m_commands[counter]->Execute();

	};

	void Reset()
	{
		for (auto& command : m_commands)
		{
			delete command;
		}
		m_commands.clear();
		m_commands.shrink_to_fit();
	};

private:

	std::vector<ICommand_Tutorial*> m_commands;

	int m_commandNumber;
};