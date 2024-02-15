#pragma once

#include <SimpleMath.h>

#include "StepTimer.h"
#include "NecromaLib/GameData/Collider.h"
#include <DeviceResources.h>
#include <SpriteBatch.h>
#include "NecromaLib/Singleton/ShareData.h"

using namespace DirectX;

class GameObjct3D
{
public:

	/// <summary>
	/// 3D�I�u�W�F�N�g�̈ʒu���,�傫����񂪊i�[���ꂽ�\����
	/// </summary>
	struct ObjectData3D
	{
		SimpleMath::Vector3 pos;
		SimpleMath::Vector3 rage;

		ObjectData3D(SimpleMath::Vector3 pos = SimpleMath::Vector3::Zero,
			SimpleMath::Vector3 rage = SimpleMath::Vector3::Zero)
		{
			this->pos = pos, this->rage = rage;
		}
	};

protected:

	ObjectData3D m_data;

	bool m_colliderActive;



public:
	GameObjct3D();
	~GameObjct3D();

	// ������
	virtual void Initialize() = 0;

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

	// �I������
	virtual void Finalize() = 0;

	/// <summary>
	/// ����3D�I�u�W�F�N�g�̑傫���ƈʒu���i�[���ꂽ�\���̂�Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	ObjectData3D GetData()							{ return m_data; }

	/// <summary>
	/// GameObject3D�Ƀ_�E���L���X�g���ꂽ�N���X��Ԃ��܂��B
	/// </summary>
	GameObjct3D* GetObject3D()						{ return static_cast<GameObjct3D*>(this);}

	/// <summary>
	/// ����3D�I�u�W�F�N�g�傫����Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	SimpleMath::Vector3 GetRage()					{ return m_data.rage; }

	/// <summary>
	/// ����3D�I�u�W�F�N�g���[���h��ԍ��W��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	SimpleMath::Vector3 GetPos()					{ return m_data.pos; }

	/// <summary>
	/// �����蔻��̏������s�������߂܂��@
	/// </summary>
	/// <param name="flag">TRUE : �s���@FALSE : �s��Ȃ�</param>
	void SetColliderActive(bool flag)				{ m_colliderActive = flag; }

	/// <summary>
	/// �����蔻��̏������s�����̃t���O��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	bool GetColliderActive()						{ return m_colliderActive; }

	/// <summary>
	/// ����3D�I�u�W�F�N�g������3D�I�u�W�F�N�g�ɐG��Ă��邩�����m���܂�
	/// </summary>
	/// <param name="data">����3D�I�u�W�F�N�g</param>
	/// <returns></returns>
	int  HitObject_Box(GameObjct3D* data);

	/// <summary>
	/// ����3D�I�u�W�F�N�g������3D�I�u�W�F�N�g�ɐG��Ă��邩�����m���܂�
	/// </summary>
	/// <param name="data">����3D�I�u�W�F�N�g</param>
	/// <returns></returns>
	bool HitObject_Circle(GameObjct3D* data);

	/// <summary>
	/// ����3D�I�u�W�F�N�g�̑傫������~���͈͂����߂܂�
	/// </summary>
	/// <returns></returns>
	Circle GetCircle()								{ return Circle(m_data.pos, m_data.rage.x * 1.5f); }

};