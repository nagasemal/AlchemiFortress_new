#pragma once
#include "NecromaLib/GameData/ShaderTemplate.h"
#include "NecromaLib/GameData/Animation.h"

class Veil :public ShaderTemplate
{
public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		SimpleMath::Vector4	windowSize;
		SimpleMath::Vector4	color;
		SimpleMath::Vector4	diff;
	};

public:
	Veil(int ruleType);
	~Veil();

	void Update();
	void Render();

	bool GetAnimationFin() { return m_animData[1].MaxCheck(); }

private:

	SimpleMath::Vector4 m_animationTime;

	// �A�j���[�V�����p�̎��ԑJ�ڂ��s���N���X
	AnimationData m_animData[2];

	int m_rule;

};