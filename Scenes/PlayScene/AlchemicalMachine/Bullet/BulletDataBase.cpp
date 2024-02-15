#include "pch.h"
#include "BulletDataBase.h"
#include "NecromaLib/GameData/CommonStruct.h"
#define MaxLv	5

Bullet_Data RecalculationStatus(ELEMENT element, int lv)
{
	//���ˊԊu�ȊO�@���X�e�[�^�X * lv / MaxLv + 2
	//���ˊԊu		(1 + ���X�e�[�^�X) * MaxLv / lv - 1
	Bullet_Data status = ShareJsonData::GetInstance().GetBulletData(element);

	// �U����
	status.str		= status.str	 * lv / MaxLv;
	// ��������
	status.life		= status.life	 * lv / MaxLv;
	// �X�s�[�h
	status.speed	= status.speed	 * lv / MaxLv;
	// �����
	status.lossMp	= status.lossMp  * lv / MaxLv;
	// ���ˊԊu
	status.span		= status.span * lv / MaxLv;

    return status;
}
