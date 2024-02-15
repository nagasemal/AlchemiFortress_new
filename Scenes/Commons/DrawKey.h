#pragma once

#include "Scenes/Commons/SelectionUI.h"

class DrawKey
{
public:
	DrawKey(SelectionUI* parent);
	~DrawKey();

	void Update();
	void Draw();

	bool PushKey();

	// �A���t�@�x�b�g�̃L�[��Ԃ��܂�
	void DrawAlphabetKey(int cutVal);

private:

	SelectionUI* m_parent;

};