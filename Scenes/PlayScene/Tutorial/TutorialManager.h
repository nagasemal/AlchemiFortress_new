#pragma once

#include "NecromaLib/GameData/Animation.h"
#include "Scenes/PlayScene/Tutorial/CommandPattern/ICommand_Tutorial.h"
#include "Scenes/PlayScene/Tutorial/CommandPattern/Commander_Tutorial.h"

class PlayScene;
class DrawArrow;
class DrawBox;
class SelectionBox;
class Particle;
class Particle_2D;

struct Tutorial_Status;

/// <summary>
/// �`���[�g���A���X�e�[�W�̏����𑍊����܂��B
/// </summary>
class TutorialManager
{
public:

public:
	TutorialManager(PlayScene* pPlayScene);
	~TutorialManager();

	void Update(bool clearMission);

	void Render();
	void Render_Layer2();

	/// <summary>
	/// �E�F�[�u���i�񂾍ہA�V���Ƀe�L�X�g�摜��ǂݎ��A
	/// �`���[�g���A���̏������e���ύX����
	/// </summary>
	void ChangeWave(int wave);

	/// <summary>
	/// �`���[�g���A���R�}���h�𐶐�����
	/// </summary>
	/// <param name="type">��������`���[�g���A��</param>
	/// <returns></returns>
	ICommand_Tutorial* GenerateCommand(Tutorial_Status type);

public:

	PlayScene* GetPlayScene() { return m_PlayScene; }

	DrawBox* GetDisplayBox() { return m_displayBox.get(); }

	DrawArrow* GetTextArrow_left() { return m_leftArrow.get(); }
	DrawArrow* GetTextArrow_right() { return m_rightArrow.get(); }

	Particle* GetParticle() { return m_machineSelectParticle.get(); }

	Particle_2D* GetArrowParticle()		{ return m_arrowParticle.get(); }
	Particle_2D* GetAlchemiParticle()	{ return m_alchemiParticle.get(); }

private:

	int m_tutorialNum;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tutorialTextBox;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tutorialTextTex;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;

	std::unique_ptr<DrawArrow> m_leftArrow, m_rightArrow;

	// �`���[�g���A���\���p�{�b�N�X
	std::unique_ptr<DrawBox> m_displayBox;

	std::unique_ptr<SelectionBox> m_selectNextWaveBox;

	std::unique_ptr<TutorialCommander> m_tutorialCommander;

	// None�}�V���Ɏ����U�����s���ׂ̃p�[�e�B�N��
	std::unique_ptr<Particle> m_machineSelectParticle;

	// ���e�N�X�`�����w���p�[�e�N��
	std::unique_ptr<Particle_2D> m_arrowParticle;
	// �B���{�^���e�N�X�`�����w���p�[�e�N��
	std::unique_ptr<Particle_2D> m_alchemiParticle;

	PlayScene* m_PlayScene;

	// ��������s�����@�����������茻���\���Ɏg�p
	AnimationData m_transitionTime;
	bool m_transitionFlag;

	int m_texWidth, m_texHeight;

	// �e�N�X�`����؂��
	int m_maxCutting;
	// ���ݐ؂�ꂽ��
	int m_nowCutting;

	bool m_selectNextWave;

};