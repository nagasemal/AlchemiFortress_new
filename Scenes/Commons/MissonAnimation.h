#pragma once

class MissionAnimation
{
public:
	MissionAnimation();
	~MissionAnimation();

	void Update();
	void Render();

private:

	// �A�j���[�V�����\�����s���t���O
	bool m_animationFlag;
	// ���̃A�j���[�V�����ɑJ�ڂ��邽�߂̕ϐ�
	float m_animTime;

};