#pragma once

class SelectionUI;

// �R�}���h�p�^�[���@�F�@ICommand_UI

struct UI_Data
{
	SelectionUI* ui;	// �ΏۂƂȂ�UI�̃|�C���^�[
	int row;	// ��
	int col;	// �s

};

// �L�[�{�[�h��UI�����������������悤�ɂ��鏈���Ɏg�p
class ICommand_UI
{
public:

	virtual UI_Data GetUIData() = 0;

	virtual void SetUIData(UI_Data ui) = 0;

	// �������s�֐�
	virtual void Execute() = 0;

	virtual ~ICommand_UI() = default;

};