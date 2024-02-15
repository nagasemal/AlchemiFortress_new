#pragma once
#include "NecromaLib/GameData/GameObject3D.h"

class FieldObject : public GameObjct3D
{
public:
	const enum OBJECT_TYPE : int
	{
		NONE = 0,				// �w��Ȃ�
		CRYSTAL = 1,			// �N���X�^��
		ENEMY_SPAWNER = 2,		// �G�l�~�[�X�|�i�[
	};
public:
	FieldObject();
	~FieldObject();

	virtual void Render(DirectX::Model* model) = 0;

	virtual void WriteDepth(DirectX::Model* model) = 0;

protected:

};