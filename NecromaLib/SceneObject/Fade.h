#pragma once

#include "StepTimer.h"
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <CommonStates.h>

class Fade
{

private:

	int   mScreenW;
	int   mScreenH;

	float mSpeed;
	float mTime;

	bool mInFlag,mNowFlag,mOutFlag;

	std::unique_ptr<DirectX::SpriteBatch>   mSpriteBatch;
	//std::unique_ptr<DirectX::SpriteFont>    mSpriteFont;
	//std::unique_ptr<DirectX::CommonStates>  mCommonState;

	// �t�F�[�h�̍ۂɎg���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mFadeTexture;


	//--	�V���O���g���ɐݒ�	--//

	Fade();

	static Fade* instance;

public:
	~Fade() = default;


	//--	�V���O���g���ɐݒ�	--//

	//	�R�s�[�R���X�g���N�^�̃f���[�g
	Fade(const Fade&) = delete;
	Fade& operator=(const Fade&) = delete;

	//	�C���X�^���X�̊m��
	static Fade* GetInstance() { return instance; }

	//	�C���X�^���X�̐���
	static void Create() { if (instance == nullptr) instance = new Fade; }

	//	�C���X�^���X�̍폜
	static void Destroy()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}


	//�@�֐�

	void Initialize(int screenWidth, int screenHeight);
	void Render();
	void Finalize();

	void SetFadeSpeed(float speed) { mSpeed = speed; }

	void Update(DX::StepTimer const& timer);
	void FadeInUpdate(DX::StepTimer const& timer);
	void FadeOutUpdate(DX::StepTimer const& timer);

	void StartFadeIn() { mInFlag = true; }
	void StartFadeOut() { mOutFlag = true; }

	bool ProcessCheckFadeIn() { return mInFlag; }
	bool ProcessCheckFadeOut() { return mOutFlag; }
	bool ProcessCheckFadeNow() { return mNowFlag; }

};