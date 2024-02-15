#pragma once

#include "ICommand_Enemy.h"
#include <vector>

class EnemyCommander
{
public:

	std::vector<ICommand_Enemy*> GetCommand() { return m_commands; }
	void AddCommand(ICommand_Enemy* command);

public:

	EnemyCommander();
	~EnemyCommander();

	void Execute_ALL();	// �S�ē����ɉ�
	void Execute_One(); // �z�񏇂ɉ񂵁A�����������͉̂񂳂Ȃ�

	void Reset();

private:

	std::vector<ICommand_Enemy*> m_commands;

	int m_commandNumber;
};