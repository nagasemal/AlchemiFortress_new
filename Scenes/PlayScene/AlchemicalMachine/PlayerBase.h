//--------------------------------------------------------------------------------------
// File: PlayerBase.h
//
// �Q�[�����̋��_(�h�q�Ώ�)�ƂȂ�I�u�W�F�N�g
//  
// 
// Date: 2023.5.10
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "NecromaLib/GameData/GameObject3D.h"
#include "Scenes/PlayScene/Field/FieldObjectType.h"


class PlayerBase : public FieldObject
{

public:
	PlayerBase();
	~PlayerBase();

	// ������
	void Initialize()	override;

	// �X�V
	void Update()		override;

	// �`��
	void Draw()			override;

	void Render(DirectX::Model* model_1) override;

	void WriteDepth(DirectX::Model* model) override;

	// �I������
	void Finalize()		override;

	void RenderBillboardUI();

 /*===[�@�A�N�Z�T�@]===*/
public:

	int			GetBaseLv()		const { return m_baseLv;}
	float		GetHP()			const { return m_hp; }
	float		GetExp()		const { return m_exp; }
	int			GetNextLvEXP();

	bool		GetHitMouse()	const { return m_hitMouseFlag;}
	bool		GetLvUpTiming() const { return m_lvUpTiming; }

	void		SetExp(float setExp)	{ m_exp = setExp;}
	void		Damage(float damage);

private:

	int			m_baseLv;				//  ���_Lv
	float		m_hp;					//  ���_Hp
	float		m_exp;					//  ���݂̌o���l��
	bool		m_hitMouseFlag;			//  �}�E�X���������Ă��邩�ۂ�
	bool		m_lvUpTiming;			//  ���x���A�b�v�̃^�C�~���O�t���O
	float		m_invincibleTime;		//	���G����
	float		m_difRedioHp;			//  ���X�Ɍ���HP�̕\���Ɏg�p

	std::unique_ptr<DirectX::Model> m_baseModel;	//  ���_��3D���f��

	//===��ŏ����e�X�g�p�ϐ�
	std::unique_ptr<GeometricPrimitive> m_testBox;	//  ���u���l�p���f��

	// ���_���f��
	std::unique_ptr<DirectX::Model> m_baseModel_Towor;

	std::unique_ptr<DirectX::Model> m_baseModel_Pillar;

};