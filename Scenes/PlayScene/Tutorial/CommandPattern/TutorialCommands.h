#pragma once

#include "ICommand_Tutorial.h"
#include "NecromaLib/GameData/CommonStruct.h"

/// <summary>
/// �������Ȃ��R�}���h
/// </summary>
class Tutorial_None : public ICommand_Tutorial
{
public:
	Tutorial_None();
	~Tutorial_None();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	TutorialManager* m_tutorialManager;	// �Ώۂ̃|�C���^�[
};

/// <summary>
/// �}�V��UI�̃`���[�g���A���R�}���h
/// </summary>
class Tutorial_MachineUI : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �n���ꂽ�}�V���^�C�v��UI��擪�ɂ��܂�
	/// </summary>
	/// <param name="machineType">�擪�ɂ���}�V���^�C�v</param>
	/// <param name="selectType">flase : �I�����Ȃ��Ă��ǂ�		true : �I���Ŏ��̃`���[�g���A���֌�����</param>
	Tutorial_MachineUI(MACHINE_TYPE machineType,bool selectFlag);
	~Tutorial_MachineUI();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	TutorialManager* m_tutorialManager;	// �Ώۂ̃|�C���^�[

	MACHINE_TYPE m_machineType;			// �Ή�����}�V���^�C�v

	bool m_selectFlag;

};

/// <summary>
/// �B���{�^���̃`���[�g���A���R�}���h
/// </summary>
class Tutorial_AlchemiUI : public ICommand_Tutorial
{
public:
	Tutorial_AlchemiUI(MACHINE_TYPE machineType,int maxCount);
	~Tutorial_AlchemiUI();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	TutorialManager* m_tutorialManager;	// �Ώۂ̃|�C���^�[

	MACHINE_TYPE m_machineType;			// �Ή�����}�V���^�C�v

	// �B���ɐ���������
	int m_alchemiCount;

};

/// <summary>
/// �G�l�~�[�̖��@�w���w��
/// </summary>
class Tutorial_EnemySpawn : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �G�l�~�[�̖��@�w�ɒ����_�����킹��
	/// </summary>
	/// <param name="time"></param>
	Tutorial_EnemySpawn(float time);
	~Tutorial_EnemySpawn();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	TutorialManager* m_tutorialManager;	// �Ώۂ̃|�C���^�[

	float m_maxTime;

};

/// <summary>
/// �w��}�V������(�ϋv�l��0�ɂ���)
/// </summary>
class Tutorial_MachineBreak : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �󂷃}�V�������肷��
	/// </summary>
	/// <param name="machineType">�󂷃}�V���^�C�v</param>
	Tutorial_MachineBreak(MACHINE_TYPE machineType);
	~Tutorial_MachineBreak();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	TutorialManager* m_tutorialManager;	// �Ώۂ̃|�C���^�[

	MACHINE_TYPE m_machineType;			// �Ή�����}�V���^�C�v

};

/// <summary>
/// �w��}�V�����C�U����(�ϋv�l��MAX�ɂ���)
/// </summary>
class Tutorial_MachineRepia : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �����}�V�������肷��
	/// </summary>
	/// <param name="machineType">�����}�V���^�C�v</param>
	Tutorial_MachineRepia(MACHINE_TYPE machineType);
	~Tutorial_MachineRepia();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	TutorialManager* m_tutorialManager;	// �Ώۂ̃|�C���^�[

	MACHINE_TYPE m_machineType;			// �Ή�����}�V���^�C�v

};

/// <summary>
/// �u���ꏊ���v���O�������Ō��߂�R�}���h_Upper�p
/// </summary>
class Tutorial_UppperSelect : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �A�^�b�J�[�}�V�����A�b�p�[�}�V���͈̔͂Ɏ��߂�K�؂Ȉʒu��������
	/// </summary>
	Tutorial_UppperSelect(int spawnNum);
	~Tutorial_UppperSelect();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	const float PARTICLE_TIME = 2.0f;

	TutorialManager* m_tutorialManager;					// �Ώۂ̃|�C���^�[

	// �p�[�e�B�N�����o�������鎞��
	float m_particleTime;

	int m_spawnNum;

};

/// <summary>
/// �u���ꏊ���v���O�������Ō��߂�R�}���h_�S��
/// </summary>
class Tutorial_NoneSelect : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �}�V����ݒu����ӏ����p�[�e�B�N���Œm�点��
	/// </summary>
	Tutorial_NoneSelect(int spawnNum);
	~Tutorial_NoneSelect();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	const float PARTICLE_TIME = 2.0f;

	// �Ώۂ̃|�C���^�[
	TutorialManager* m_tutorialManager;

	// �p�[�e�B�N�����o�������鎞��
	float m_particleTime;

	// �������鐔
	int m_spawnNum;

};

/// <summary>
/// �}�V��UI�̈ړ����b�N���s��
/// </summary>
class Tutorial_LockMachineUI : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �}�V���̐ݒu���C�������߂�
	/// </summary>
	Tutorial_LockMachineUI(bool activeFlag);
	~Tutorial_LockMachineUI();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	// �Ώۂ̃|�C���^�[
	TutorialManager* m_tutorialManager;

	bool m_activeFlag;

};

/// <summary>
/// �B���{�^���̘B�����b�N���s��
/// </summary>
class Tutorial_LockAlchemi : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �B���{�^���̃��b�N���s��
	/// </summary>
	Tutorial_LockAlchemi(bool activeFlag);
	~Tutorial_LockAlchemi();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	// �Ώۂ̃|�C���^�[
	TutorialManager* m_tutorialManager;

	bool m_activeFlag;

};

/// <summary>
/// �`���[�g���A���̃e�L�X�g��i�߂�������܂�
/// </summary>
class Tutorial_TextArrow : public ICommand_Tutorial
{
public:
	/// <summary>
	/// �}�V���̐ݒu���C�������߂�
	/// </summary>
	Tutorial_TextArrow(int type);
	~Tutorial_TextArrow();

	// �������J�n�����ۂɒʂ�����
	void Initialize() override;
	// �������s�֐�
	void Execute() override;
	// �������I�������ۂɒʂ�����
	void Finalize() override;
	// �������̓��e���L�q
	void Reset() override;

	void SetTutorialManagerPtr(TutorialManager* object) override { m_tutorialManager = object; }

private:

	// �Ώۂ̃|�C���^�[
	TutorialManager* m_tutorialManager;

	// �ǂ̂悤�ȏ������s����
	int m_type;

};