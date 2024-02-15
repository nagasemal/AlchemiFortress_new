#pragma once

#include "NecromaLib/SceneObject/SceneObj.h"
//#include "NecromaLib/SceneObject/SceneManager.h"

class SelectionBox;
class UIKeyControl;
class Veil;
class DrawMachine;
class ResultCamera;
class ResultDirection;

class ResultScene : public SceneObj
{
public:
	// �R���X�g���N�^
	ResultScene();

	// �f�X�g���N�^
	~ResultScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// UI�n�`��
	void DrawUI() override;

	// �I������
	void Finalize() override;

private:

	std::unique_ptr<SelectionBox> m_selectionBox_Next;
	std::unique_ptr<SelectionBox> m_selectionBox_Retry;
	std::unique_ptr<SelectionBox> m_selectionBox_Back;

	std::unique_ptr<DrawMachine> m_drawMachine;

	std::unique_ptr<Veil>		  m_veil;

	std::unique_ptr<UIKeyControl> m_uiKeyControl;

	std::unique_ptr<ResultCamera> m_resultCamera;

	std::unique_ptr<ResultDirection> m_resultDirection;

	std::unique_ptr<DirectX::Model> m_baseModel;

	std::unique_ptr<DirectX::Model>	m_skySphere;

};