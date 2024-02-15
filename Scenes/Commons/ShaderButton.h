#pragma once

#include "NecromaLib/GameData/ShaderTemplate.h"

class ShaderButton : public ShaderTemplate
{
private:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		SimpleMath::Vector4	windowSize;
		SimpleMath::Vector4	color;
		SimpleMath::Vector4	diff;
	};

public:
	ShaderButton();
	~ShaderButton();

	void Update();
	void Render();

private:

};