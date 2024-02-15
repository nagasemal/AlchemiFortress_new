#pragma once
#include "NecromaLib/GameData/ShaderTemplate.h"

class FieldObjectManager;
class Number;

class BaseLv : public ShaderTemplate
{
private:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		SimpleMath::Vector4	windowSize;
		SimpleMath::Vector4	base_color;
		SimpleMath::Vector4	second_color;
	};

public:
	BaseLv();
	~BaseLv();

	void Update(FieldObjectManager* pFieldObjectManager);
	void Render(float alphaVal);

private:

	// ���_Lv�̕`��
	std::unique_ptr<Number> m_baseLvRender;

	// exp�̊���
	float m_expRedio;

};