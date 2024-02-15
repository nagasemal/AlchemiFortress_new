#pragma once
#include "ITutorialState.h"

class TutorialManager;
// ����ӏ���������邱�Ƃ�ҋ@���Ă�����
class Tutorial_IdlingState : public ITutorialState
{
public:
	Tutorial_IdlingState();
	~Tutorial_IdlingState() = default;

	void Update(TutorialManager* manager) override;
	void Render(TutorialManager* manager) override;

private:

};


// ����ӏ��������ꂽ��̈ڍs���
class Tutorial_TransitionState : public ITutorialState
{
public:
	Tutorial_TransitionState();
	~Tutorial_TransitionState() = default;

	void Update(TutorialManager* manager) override;
	void Render(TutorialManager* manager) override;

private:

};

// �`���[�g���A�����I��������
class Tutorial_FinState : public ITutorialState
{
public:
	Tutorial_FinState();
	~Tutorial_FinState() = default;

	void Update(TutorialManager* manager) override;
	void Render(TutorialManager* manager) override;

private:

};

// �}�V�������Ă��܂����I��Ԃ���邽�߂̃X�e�[�g
class Tutorial_BreakMachineState : public ITutorialState
{
public:
	Tutorial_BreakMachineState();
	~Tutorial_BreakMachineState() = default;

	void Update(TutorialManager* manager) override;
	void Render(TutorialManager* manager) override;

private:

};