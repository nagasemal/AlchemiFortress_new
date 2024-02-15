#pragma once

class AlchemicalMachineManager;

class Explanation
{
private:

	enum EXPLANATION_TYPE :int
	{
		MACHINE_SELECT		 = 0, // �}�V���@�I��
		MACHINE_INSTALLATION = 1, // �}�V���@�ݒu

		ZOOM				 = 2, // �J�����Y�[��
		MACHINE_LINE		 = 3, // �}�V���ݒu�̃��C������

		ROTATE_STOP			 = 4, // ��]��~
		ROTATE_START		 = 5  // ��]�ĊJ

	};

public:
	Explanation();
	~Explanation();

	void Update();

	void Render(bool selectNowFlag,bool rotateStopFlag);

	SimpleMath::Vector2 RightExplanationPos();
	SimpleMath::Vector2 MiddleExplanationPos();
	SimpleMath::Vector2 LeftExplanationPos();

private:

	void ExplanationRender(SimpleMath::Vector2 pos, int type);

	bool m_mouseSelectButton[3];
	int m_prvMouseValue;

};