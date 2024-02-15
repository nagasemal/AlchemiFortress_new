//--------------------------------------------------------------------------------------
// File		: Number.h
//
// �X�v���C�g�摜�ɂ�鐔���̕`��Ɏg�p
// 
// Use		: MachineSelect AlchemicalMachineObject
//			  AM_Attacker AM_Upeer
// Date		: 2023.7.17
// Author	: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject2D.h"

class Number
{
public:
	Number();
	Number(SimpleMath::Vector2 position,SimpleMath::Vector2 rage);
	~Number();

	// �\�����鐔���̐ݒ�
	void SetNumber(int num);
	void SetPosition(SimpleMath::Vector2 position) { m_position = position;	m_position.x += 32 * m_rage.x; }
	void SetRage(SimpleMath::Vector2 rage) { m_rage = rage; }

	void SetColor(SimpleMath::Color color) { m_color = color; }

	// �����摜�`��
	void Render();

	// �X�v���C�g�o�b�`��begin�֐����Ă΂Ȃ�
	void Render_NoSpriteBatch();

	/// <summary>
	/// ��/�����̕\�����\
	/// </summary>
	/// <param name="first">���q</param>
	/// <param name="next">����</param>
	/// <param name="symbol">0 = / , 1 = :</param>
	void Render_SelectScene(int first,int next,int symbol = 0);

	// �����ꂽ�������擾����
	int GetNumber() { return m_num; }

	SimpleMath::Vector2 GetPosition() { return m_position; }
	SimpleMath::Vector2 GetRage() { return m_rage; }

	// �F����Ԃ�
	SimpleMath::Color GetColor() { return m_color; }
	// �F���(RGB)��Ԃ�
	SimpleMath::Vector3 GetColorRGB() { return SimpleMath::Vector3(m_color.R(), m_color.G(), m_color.B()); }

private:

	// ������`�悷��
	void Number_Render(int num,SimpleMath::Vector2 pos);

	SimpleMath::Vector2 m_position;
	SimpleMath::Vector2 m_rage;

	SimpleMath::Color m_color;

	int m_num;

	int m_prevNum;

	float m_animationPosTime;

	bool m_animationFlag;

};