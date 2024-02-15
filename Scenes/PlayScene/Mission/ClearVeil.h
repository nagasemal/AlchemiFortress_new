#pragma once
#include "NecromaLib/GameData/Animation.h"

class UserInterface;
class Particle_2D;

class ClearVeil
{
public:
	ClearVeil(int waveNum);
	~ClearVeil();

	void Update(bool startFlag);
	void Render(int nowWave);

	// ����Wave�Ɉڍs������
	bool NextWave();

private:

	// NextWave�̕����`��
	std::unique_ptr<UserInterface> m_nextWave_Top,m_nextWave_Bottom;
	// WAVE�N���A�����ۂɗ����A�j���[�V�����p�ϐ�
	AnimationData m_waveAnimation_first;
	AnimationData m_waveAnimation_second;

	// Wave�������o�I�ɕ\������A�j���[�V�����p�ϐ�
	std::vector<AnimationData> m_waveAnimation_waves;

};