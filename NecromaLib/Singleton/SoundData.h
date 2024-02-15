#pragma once
//--------------------------------------------------------------------------------------
// File: SoundData.h
//
// BGM��SE�𗬂��ׂ̃N���X
// 
//
// Date: 2023.9.13
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#include "NecromaLib/GameData/Audio/BGMs.h"
#include "NecromaLib/GameData/Audio/SEs.h"
#include "NecromaLib/GameData/Audio/SystemSE.h"

#include "NecromaLib/GameData/Animation.h"

class SoundData
{

public:
	~SoundData() = default;

	SoundData(const SoundData&) = delete;
	SoundData& operator=(const SoundData&) = delete;

	static void Create();
	static void Destroy();

	static SoundData& GetInstance() { return *instance; }

	void SoundLoad(DirectX::AudioEngine* audioEngine);

	// BGM�𗬂��܂�
	void PlayBGM(XACT_WAVEBANK_BGMS name, bool stop);
	// �S�Ă�BGM���~�߂܂�
	void StopBGM();

	// SE���Đ�
	void PlaySE(XACT_WAVEBANK_SES name);

	// SE���~�߂�
	void StopSE(XACT_WAVEBANK_SES name);

	// �V�X�e��SE���Đ�
	void PlaySystemSE(XACT_WAVEBANK_SYSTEMSE name);

	// �V�X�e��SE���Đ�(���ݖ��Ă���V�X�e��SE���~�߁A�V��������)
	void PlaySystemSE_Auto(XACT_WAVEBANK_SYSTEMSE name);

	// �V�X�e��SE�̒�~
	void StopSystemSE(XACT_WAVEBANK_SYSTEMSE name);

	// BGM�̉��ʐݒ�
	void SetBGMVol(float vol, float max)		{ m_bgmVol = vol; m_bgmVolMax = max; }

	// SE�̉��ʐݒ�
	void SetSEVol(float vol, float max)			{ m_seVol = vol; m_seVolMax = max; }

	// �V�X�e��SE�̉��ʐݒ�
	void SetSystemSEVol(float vol, float max)	{ m_systemVol = vol; m_systemVolMax = max;}

private:
	SoundData();
	static SoundData* instance;

	std::unique_ptr<DirectX::WaveBank> m_BGMBank;
	std::unique_ptr<SoundEffectInstance> m_BGMInstance[XACT_WAVEBANK_BGMS_ENTRY_COUNT];

	std::unique_ptr<DirectX::WaveBank> m_SEBank;
	std::unique_ptr<SoundEffectInstance> m_SEInstance[XACT_WAVEBANK_SES_ENTRY_COUNT];

	std::unique_ptr<DirectX::WaveBank> m_SystemSEBank;
	std::unique_ptr<SoundEffectInstance> m_SystemSEInstance[XACT_WAVEBANK_SYSTEMSE_ENTRY_COUNT];


	float m_bgmVol,m_bgmVolMax;			// BGM�̃{�����[��
	float m_seVol, m_seVolMax;			// SE �̃{�����[��
	float m_systemVol, m_systemVolMax;	// System�̃{�����[��(�N���b�N����)
	AnimationData m_timer;

};