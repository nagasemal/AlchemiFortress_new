#include "pch.h"
#include "EnemyCommander.h"

EnemyCommander::EnemyCommander():
	m_commandNumber(),
	m_commands()
{
}

EnemyCommander::~EnemyCommander()
{
}

void EnemyCommander::AddCommand(ICommand_Enemy* command)
{
	m_commands.push_back(command);
}

void EnemyCommander::Execute_ALL()
{
	// �S�ẴR�}���h�����s
	for (auto& command : m_commands)
	{
		command->Execute();
	}
}

void EnemyCommander::Execute_One()
{
	// ���݂̃R�}���h�ԍ�
	int counter = 0;

	// �ғ����Ԃ𖞂����Ă�������Z
	for (auto& command : m_commands)
	{
		counter += command->GetCompletion();
	}

	// �R�}���h�ʂ�葽���Ȃ����ꍇ��0�ɖ߂�
	if (m_commands.size() <= counter)
	{
		// �S�Ẳғ������ς݃R�}���h�����Z�b�g����
		for (auto& command : m_commands)
		{
			command->SetCompletion(false);
			command->Reset();
		}

		counter = 0;
	}

	// ���s
	m_commands[counter]->Execute();

}

void EnemyCommander::Reset()
{
	m_commands.clear();
}
