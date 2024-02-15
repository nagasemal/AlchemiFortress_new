#pragma once

#include "NecromaLib/SceneObject/SceneObj.h"

#include "NecromaLib/GameData/Camera.h"

#include "Scenes/Commons/DrawMachine.h"
#include "Scenes/SelectScene/SelectCamera.h"
#include "Scenes/SelectScene/MissionRender.h"

class DrawArrow;
class SelectionBox;
class UIKeyControl;
class Number;

class SelectScene : public SceneObj
{
public:
	// �R���X�g���N�^
	SelectScene();

	// �f�X�g���N�^
	~SelectScene();

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

	int GetStageNumber() const { return m_selectStageNumber;}
	void SetStageNumber(int number) { m_selectStageNumber = number;}

private:

	// �I�������X�e�[�W�̔ԍ�
	int m_selectStageNumber;

	std::unique_ptr<DirectX::Model>		m_skySphere;

	// �Z���N�g�V�[�����̃J����
	std::unique_ptr<SelectCamera> m_selectCamera;

	// �}�V���̕`��
	std::unique_ptr<DrawMachine> m_machineDraw;

	// �~�b�V�����̕`��
	std::unique_ptr<MissionRender> m_missionDraw;

	// ���I�u�W�F�N�g�̕`��
	std::unique_ptr<DrawArrow> m_arrowDraw[2];

	// �I���{�b�N�X�̕`��(���̃V�[���֑J��)
	std::unique_ptr<SelectionBox> m_nextSceneBox;

	// �X�e�[�W�ԍ��`��
	std::unique_ptr<Number> m_stageNumber;

	bool m_changeMachine;							// �}�V�����ύX���ꂽ���Ƃ�m�点��t���O

};