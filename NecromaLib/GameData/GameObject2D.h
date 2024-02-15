#pragma once

#include <SimpleMath.h>

#include "StepTimer.h"
#include "NecromaLib/GameData/Collider.h"
#include <DeviceResources.h>
#include <SpriteBatch.h>
#include "NecromaLib/Singleton/ShareData.h"

using namespace DirectX;

class GameObject2D
{
protected:

	struct ObjectData2D
	{
		SimpleMath::Vector2 pos = SimpleMath::Vector2();
		SimpleMath::Vector2 rage = SimpleMath::Vector2();
	};

	ObjectData2D m_data;

public:
	GameObject2D();
	~GameObject2D();

	// ������
	virtual void Initialize() = 0;

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

	// �I������
	virtual void Finalize() = 0;

	// �|�W�V�����Ƒ傫�����������\���̂�n��
	ObjectData2D GetData() { return m_data; }

	SimpleMath::Vector2 GetRage()	{ return m_data.rage; }
	SimpleMath::Vector2 GetPos()	{ return m_data.pos; }

	void SetPos(SimpleMath::Vector2 pos)	{ m_data.pos = pos;}
	void SetRage(SimpleMath::Vector2 rage)	{ m_data.rage = rage;}

	// ������Ώۂ̃I�u�W�F�N�g
	bool  HitObject(SimpleMath::Vector2 pos);

	/// <summary>
	/// �X�v���C�g�o�b�`�ł̕`��I�u�W�F�N�g�ɓK���������蔻��
	/// </summary>
	/// <param name="pos">�Ώۂ̃I�u�W�F�N�g�̃|�W�V����</param>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	/// <param name="percent">0 ~ 1�͈̔͂̊g�k��</param>
	/// <returns></returns>
	bool HitObject_RageSet(SimpleMath::Vector2 pos, float width = 64.0f, float height = 64.0f, float percent = 1.0f);

	/// <summary>
/// �X�v���C�g�o�b�`�ł̕`��I�u�W�F�N�g�ɓK���������蔻��
/// </summary>
/// <param name="pos">�Ώۂ̃I�u�W�F�N�g�̃|�W�V����</param>
/// <param name="width">����</param>
/// <param name="height">�c��</param>
/// <param name="percent">0 ~ 1�͈̔͂̊g�k��</param>
/// <returns></returns>
	bool HitObject_RageSet(SimpleMath::Vector2 pos, float width = 64.0f, float height = 64.0f, SimpleMath::Vector2 percent = {1.0f,1.0f});

};