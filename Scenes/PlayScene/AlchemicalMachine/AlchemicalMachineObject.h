#pragma once
#include "NecromaLib/GameData/GameObject3D.h"

#include "Scenes/PlayScene/Mouse/MousePointer.h"
#include "Scenes/PlayScene/Enemy/EnemyObject.h"
#include "Scenes/PlayScene/AlchemicalMachine/Bullet/Bullet.h"
#include "Scenes/PlayScene/UI/SelectionBox.h"
#include "Scenes/PlayScene/Field/FieldObjectManager.h"
#include <list>
#include <vector>

#include "Scenes/DataManager.h"

#include "NecromaLib/GameData/CommonStruct.h"

class EnemyObject;
class Bullet;
class SelectionBox;

class AlchemicalMachineObject : public GameObjct3D
{
public:

	AlchemicalMachineObject();
	virtual ~AlchemicalMachineObject() {};

	// �I�����̓��ʂȃA�b�v�f�[�g����
	virtual void SelectUpdate() = 0;

	// �I�����A�}�E�X�I���\��UI�̕\���Ɏg�p
	virtual void RenderUI() = 0;

	// ���ʂ��ăA�b�v�f�[�g�������鏈��
	void Update_Common();

	// ���ʂ��ăA�b�v�f�[�g�������鏈��
	void SelectUpdate_Common();

	// ���ʂ��ĕ`�悷��UI�̏���
	void SelectRenderUI_Common();

	// HP�c�ʂ��r���{�[�h�`�悷��
	void RenderHP();

	// �N���b�N�U����`�悷��
	void RenderClickPrompt();

	// ���̃I�u�W�F�N�g���m�̓����蔻��
	void HitToMouse(MousePointer* pMP);

	// ���ʔ͈͓���3D�I�u�W�F�N�g��������
	bool OnCollisionEnter_MagicCircle(GameObjct3D* object);
	
	/// <summary>
	/// ���f���`��n
	/// </summary>
	/// <param name="model">�@�@�@ �x�[�X�̃��f���@</param>
	/// <param name="ring">�@�@�@�@�ǉ��p�[�c</param>
	void ModelRender(DirectX::Model* model,
					 DirectX::Model* ring = nullptr,
					 bool silhouette = false);

	// ����
	void SummonAM(SimpleMath::Vector3 pos);

// �A�N�Z�T
public:

	// ���݂��Ă��邩�ۂ�
	const bool GetActive()									const { return m_active; }

	// �}�E�X���G��Ă��邩�ۂ�
	const bool GetHitMouse()								const { return m_hitMouseFlag;}

	// ����ŏ�����A�j���[�V�������I��������Ƃ�����
	const bool GetDethFlag()								const { return m_hp <= 0.0f && m_dethTime >= 1.0f;}

	// �I�u�W�F�N�g�̖��O
	const std::string GetObjectName()						const { return m_objectName; }

	// �I�u�W�F�N�g�̃^�C�v
	const MACHINE_TYPE GetModelID()							const { return m_machineID;}

	// ���͂�Ԃ��Ă���܂�
	const float GetMachineEffectValue()						const { return m_machineEffectValue; }

	// ���ʔ����܂ł̎���
	const float GetSpan()									const { return m_span;}
	
	// ���݃��x��
	const int	  GetLv()									const { return m_lv; }

	// ����HP
	const int	  GetHP()									const { return m_hp; }

	// ����MAXHP
	const int	  GetMAXHP()								const { return m_maxHp; }

	// ���ʔ͈�
	const Circle GetMagicCircle()							const { return m_magicCircle; }

	// �ۗL���Ă���F���
	// HP��0�Ȃ�΍���Ԃ��܂�
	const SimpleMath::Color GetColor()						const { return m_hp <= 0 ? SimpleMath::Color(0, 0, 0, 1): m_color * (1.0f - m_invincibleTime);}

	// �����̗v���ŕω����󂯂Ă�����
	const bool GetPowerUpFlag()								const { return m_powerUPFlag; }

	// ���݂̑���
	const ELEMENT GetElement()								const { return m_element; }

	// ���݂ǂ̃��C����ɑ��݂��Ă��邩
	const int GetLine()										const { return m_line; }

	// ����LV�ɕK�v�ȃN���X�^���̗�
	const int GetNextLvCrystal();

	// �C�U�ɕK�v�ȃN���X�^���̗�
	const int GetRepairCrystal();

	// ��̂œ�����N���X�^���̗�
	const int GetDismantlingCrystal();

	// �I������Ă����Ԃ��ۂ�������t����
	const int GetSelectModeFlag() const { return m_selectModeFlag; }

	const float GetPopTextTime() const { return m_popHPTime; }

	// ���݃N���b�N�U����Ԃł��邩
	const bool GetClickPromptFlag() const { return m_clickPromptFlag; }

	void SetLv(int lv)									{ m_lv = lv; }
	void SetHP(int hp)									{ m_hp = hp; }
	void SetMAXHP(int maxHP)							{ m_maxHp = maxHP;}
	void SetPos(SimpleMath::Vector3 pos)				{ m_data.pos = pos; }
	void SetMagicCircle(Circle circle)					{ m_magicCircle = circle;}
	void SetActive(bool flag)							{ m_active = flag; }
	void SetLine(int line)								{ m_line = line; }
	void SetPowerUpFlag(bool flag)						{ m_powerUPFlag = flag; }
	void SetSelectModeFlag(bool flag)					{ m_selectModeFlag = flag;}
	void SetHitMouseFlag(bool flag)						{ m_hitMouseFlag = flag; }
	void SetElement(ELEMENT element)					{ m_element = element; }
	void SetColor(SimpleMath::Color color)				{ m_color = color;}
	void SetClickPromptFlag(bool flag)					{ m_clickPromptFlag = flag; }

public:
	// �V���G�b�g�`��
	void SilhouetteRender(DirectX::Model* model, SimpleMath::Matrix matrix);

	// �ʏ�`��
	void NomalRender(DirectX::Model* model, SimpleMath::Matrix matrix,SimpleMath::Color color = SimpleMath::Color());

	// �������`��
	void TransparentRender(DirectX::Model* model, SimpleMath::Matrix matrix);

	// �V�F�[�_�[�����`��
	void NotShaderRender(DirectX::Model* model, SimpleMath::Matrix matrix);

	// �f�v�X�������ݕ`��
	void WriteDepathRender(DirectX::Model* model,DirectX::Model* secondModel);

private:

	// �o�������o�Ɏg�p���鎞�ԕϐ�
	float m_spawnTime;

	// ���S�����o�Ɏg�p���鎞�ԕϐ�
	float m_dethTime;

protected:

	// Lv�̍ő�l
	static const int MAX_LV = 5;

	// �}�V��ID�@�L�[�Ƃ��ă��f���̎󂯎����s��
	MACHINE_TYPE m_machineID;

	// �}�V���̑ϋv�l
	int m_hp;

	// �}�V���̍ő�ϋv�l
	int m_maxHp;

	// �}�V���̃��x��
	int m_lv;

	// �}�V�����L�̃f�[�^(�U���͂�h�䐫�\�A�̌@���x�Ȃ�)������t����f�[�^
	float m_machineEffectValue;

	// ���̌��ʔ����܂ł̎���
	float m_span;

	// ���G����,���G���
	float m_invincibleTime;
	bool m_invincibleFlag;

	// Y����]�����邽�߂̕ϐ�
	float m_rotateAnimation;

	// HP�����X�Ɍ���悤�ɂ���ϐ�
	float m_difRedioHp;

	// �I�u�W�F�N�g�̃��C���ʒu(�ǂ̉~�`����ɂ��邩)
	int m_line;

	// ���݂��Ă��邩�ۂ�
	bool m_active;

	// ��������̉e���ŋ������󂯂Ă��邩
	bool m_powerUPFlag;

	// �I�����[�h���̃t���O
	bool m_selectModeFlag;

	// �}�E�X���������Ă��邩�ۂ�
	bool m_hitMouseFlag;

	// �I������Ă���Ԃ̎���
	float m_selectModeTime;

	// �N���b�N����悤�ɑ���
	bool m_clickPromptFlag;

	// ���ʔ͈�
	Circle m_magicCircle;

	std::string m_objectName;

	// �I�u�W�F�N�g�̐F
	SimpleMath::Color m_color;

	// �T�u�I�u�W�F�N�g�̐F
	SimpleMath::Color m_subColor;

	// �I�u�W�F�N�g�̑���
	ELEMENT m_element;

	// UI�̈ʒu�����߂�
	SimpleMath::Vector3 m_offsetUIPos;

	// �G�ꂽ��o������HP�o�[UI�p�̎��ԕϐ�
	float m_popHPTime;
};