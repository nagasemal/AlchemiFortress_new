#pragma once

class DrawSlider;
class SelectionBox;

class RenderOption
{
public:
	RenderOption();
	~RenderOption();

	void Initialize();
	void Update();
	void Render();
	void Finalize();

	bool GetHitCancelButton();

private:

	// SE�̑���o�[
	std::unique_ptr<DrawSlider> m_userBar_SE;
	// BGM�̑���o�[
	std::unique_ptr<DrawSlider> m_userBar_BGM;
	// SystemSE�̑���o�[
	std::unique_ptr<DrawSlider> m_userBar_SystemSE;

	// �I�v�V������������߂�
	std::unique_ptr<SelectionBox> m_cancelButton;

};