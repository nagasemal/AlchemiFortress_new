//--------------------------------------------------------------------------------------
// File: InputSupport.h
//
//�@�}�E�X����,�L�[�{�[�h���͂��T�|�[�g����V���O���g���N���X
// 
// Date: 2023.05.09
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once
class InputSupport
{
private:

	InputSupport();
	static InputSupport* instance;

	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
	DirectX::Mouse::ButtonStateTracker m_mouseTracker;

	//���[���h��ԍ��W��̃}�E�X
	SimpleMath::Vector3 m_WorldScreenMouse;

	// UI�ɐG���ƁA�ݒ肳��Ă��郌�C���[�̔ԍ�������
	int m_nowLayer;

	bool m_hitUIFlag;

	// �L�[�\���������悤�ɂ���
	bool m_keyDisplayMode;

public:
	~InputSupport() = default;

	InputSupport(const InputSupport&) = delete;
	InputSupport& operator=(const InputSupport&) = delete;

	static void Create();
	static void Destroy();

	static InputSupport& GetInstance() { return *instance; }

	void Update();

	/// <summary>
	/// ���ݐG��Ă���UI���C���[��ݒ肵�܂�
	/// </summary>
	/// <param name="layer">UI���C���[�ԍ�</param>
	void SetLayer(int layer);

	/// <summary>
	/// ���ݐG��Ă���UI���C���[�ԍ���Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	bool GetLayer() { return m_nowLayer; }

	/// <summary>
	/// UI�ɐG��Ă���
	/// </summary>
	void HitUI() { m_hitUIFlag = true; }

	/// <summary>
	/// UI�ɐG��Ă��Ȃ�
	/// </summary>
	void ExitUI() { m_hitUIFlag = false; }

	/// <summary>
	/// UI�ւ̐ڐG����
	/// </summary>
	/// <returns></returns>
	bool GetHitUI() {return m_hitUIFlag;}

	/// <summary>
	/// �L�[�{�[�h�N���X��ݒ�
	/// </summary>
	/// <param name="tracker">���������g���b�J�[</param>
	void SetKeybordState(DirectX::Keyboard::KeyboardStateTracker tracker)	{m_keyboardTracker = tracker; }

	/// <summary>
	/// �L�[�{�[�h�g���b�J�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	DirectX::Keyboard::KeyboardStateTracker GetKeybordState()				{ return m_keyboardTracker; }

	/// <summary>
	/// �}�E�X�N���X��ݒ�
	/// </summary>
	/// <param name="tracker">���������}�E�X�g���b�J�[</param>
	void SetMouseState(DirectX::Mouse::ButtonStateTracker tracker) { m_mouseTracker = tracker; }

	/// <summary>
	/// �}�E�X�g���b�J�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	DirectX::Mouse::ButtonStateTracker GetMouseState() { return m_mouseTracker; }

public:

	// �}�E�X���������ꂽ�u��
	bool LeftButton_Press();
	// �}�E�X���������ꂽ�u��
	bool LeftButton_Release();
	// �}�E�X���������ꑱ���Ă���
	bool LeftButton_Held();

	// �}�E�X�E�������ꂽ�u��
	bool RightButton_Press();
	// �}�E�X�E�������ꂽ�u��
	bool RightButton_Release();
	// �}�E�X�E�������ꑱ���Ă���
	bool RightButton_Held();

	// �}�E�X�z�C�[���������ꂽ�u��
	bool MiddleButton_Press();
	// �}�E�X�z�C�[���������ꂽ�u��
	bool MiddleButton_Release();
	// �}�E�X�z�C�[���������ꑱ���Ă���
	bool MiddleButton_Held();

	// �L�[�\�����[�h�ɂȂ��Ă���
	bool GetKeyDisplayMode();

	// �}�E�X���W(���[���h���)
	SimpleMath::Vector3 GetMousePosWolrd();

	// �}�E�X���W(�X�N���[�����)
	SimpleMath::Vector2 GetMousePosScreen();

};