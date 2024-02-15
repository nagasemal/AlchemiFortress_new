#pragma once

class TutorialManager;

enum UI_TYPE : int
{
	UI_ALCHEMI,
	UI_GAUGE,
	UI_EXPLANATION
};

class ICommand_Tutorial
{
protected:

	bool m_initializeFlag = false;	// �������������I���������Ƃ�m�点��t���O
	bool m_completion = false;		// �R�}���h���I���������Ƃ�m�点��t���O

public:
	virtual void Reset() = 0;

	// �������J�n�����ۂɒʂ�����
	virtual void Initialize() = 0;
	// �������s�֐�
	virtual void Execute() = 0;
	// �������I�������ۂɒʂ�����
	virtual void Finalize() = 0;

	virtual ~ICommand_Tutorial() = default;

	virtual void SetTutorialManagerPtr(TutorialManager* object) = 0;

	bool GetCompletion() { return  m_completion; }

	void SetCompletion(bool flag) { m_completion = flag; }

};