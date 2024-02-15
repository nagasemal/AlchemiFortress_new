#pragma once
#include "NecromaLib/GameData/Animation.h"

class DisplayMagicCircle
{
public:
	DisplayMagicCircle();
	~DisplayMagicCircle();

	void Update();
	void Render();

	// ����̍�
	void SpritebatchRender();

	void SetWindowSize(const int& width, const int& height);

	void SetScale(SimpleMath::Vector2 scale);
	void SetPosition(SimpleMath::Vector2 position);

	void SetColor(SimpleMath::Color color)	{ m_color = color; }
	SimpleMath::Color GetColor()			{ return m_color; }

	void SetRotationMatrix(SimpleMath::Matrix matrix) { m_rotationMatrix = matrix;}

	// ���@�w���o��������
	void TransparentUpdate(bool spawnFlag);

private:

	int m_windowWidth, m_windowHeight;
	int m_textureWidth, m_textureHeight;

	SimpleMath::Vector2 m_scale;
	SimpleMath::Vector2 m_baseScale;
	SimpleMath::Vector2 m_position;
	SimpleMath::Color m_color;
	SimpleMath::Matrix	m_rotationMatrix;

	// ���@�w���񂷎��Ԍv���ϐ�
	float m_rotateTime;

	// ���@�w�𓧖����������ɏo�������鎞�Ԍv���ϐ�
	AnimationData m_transparentTime;
	float m_easing;
};