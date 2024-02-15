#pragma once

enum Direction
{
	LEFT = 1 << 0,			//���ɓ������Ă���
	TOP = 1 << 1,			//��ɓ������Ă���
	RIGHT = 1 << 2,			//�E�ɓ������Ă���
	BOTTOM = 1 << 3,		//���ɓ������Ă���
	FRONT = 1 << 4,			//�O�ɓ������Ă���
	BACK = 1 << 5,			//��ɓ������Ă���
	TOP_LEFT = TOP + LEFT,		//����ɓ������Ă���
	TOP_RIGHT = TOP + RIGHT,		//�E��ɓ������Ă���
	BOTTOM_LEFT = BOTTOM + LEFT,	//�����ɓ������Ă���
	BOTTOM_RIGHT = BOTTOM + RIGHT,	//�E���ɓ������Ă���
	CENTER = LEFT + TOP + RIGHT + BOTTOM		//�㉺���E�̒��S�ɓ������Ă���
};

struct Circle
{
	SimpleMath::Vector3 p;

	float r;

	Circle(SimpleMath::Vector3 ip = SimpleMath::Vector3(), float ir = 0.f) { p = ip, r = ir; }

	Circle(float ix, float iy,float iz, float ir) { p = SimpleMath::Vector3(ix, iy,iz), r = ir; }

};

int AABB_XZ(SimpleMath::Vector3 box1APos, SimpleMath::Vector3 box1BPos, SimpleMath::Vector3 box2APos, SimpleMath::Vector3 box2BPos);

int AABB_XY(SimpleMath::Vector3 box1APos, SimpleMath::Vector3 box1BPos, SimpleMath::Vector3 box2APos, SimpleMath::Vector3 box2BPos);

int AABB_3D(SimpleMath::Vector3 box1APos, SimpleMath::Vector3 box1BPos, SimpleMath::Vector3 box2APos, SimpleMath::Vector3 box2BPos);

bool PointerToBox(SimpleMath::Vector2 screenPos,SimpleMath::Vector2 box1, SimpleMath::Vector2 box2);

/// <summary>
/// �~�`��̓����蔻���Circle��p���Ĕ��肵�܂��B
/// </summary>
/// <param name="gameObjectA"></param>
/// <param name="gameObjectB"></param>
/// <returns></returns>
bool CircleCollider(Circle circle1, Circle circle2);

class GameObjct3D;
/// <summary>
/// �~�`��̓����蔻���GameObject3D��p���Ĕ��肵�܂��B
/// </summary>
/// <param name="gameObjectA"></param>
/// <param name="gameObjectB"></param>
/// <returns></returns>
bool CircleCollider(GameObjct3D* gameObjectA, GameObjct3D* gameObjectB);

bool PointerToCircle(Circle circle, SimpleMath::Vector3 point);

struct OBB
{
	SimpleMath::Vector3 pos;		//�@���S�_
	SimpleMath::Vector3 inc[3];	//	�e���W���̌X����\�������x�N�g��
	float length[3];						//	���S�_����ʂ܂ł̒��� * 2
};

bool OBBToOBB(OBB obbA, OBB obbB);

struct Plane
{
	SimpleMath::Vector3 pos;		//���S�_
	SimpleMath::Vector3 m_local;	//���[�J�����W�ł̖@���x�N�g��
};

// OBB�ƕ���
bool OBBToPlane(OBB obb, Plane plane,float* len);

// �h�b�g�ς����߂�֐�
float Dot3D(SimpleMath::Vector3 a, SimpleMath::Vector3 b);

// �N���X��
SimpleMath::Vector3 Cross3D(SimpleMath::Vector3 a, SimpleMath::Vector3 b);

float LenSegOnSeparateAxis(SimpleMath::Vector3 Sep, SimpleMath::Vector3 e1, SimpleMath::Vector3 e2, SimpleMath::Vector3* e3 = 0);