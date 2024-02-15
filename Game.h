//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "NecromaLib/GameData/Collider.h"
#include "NecromaLib/GameData/Camera.h"

#include "NecromaLib/SceneObject/SceneManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game();

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // UI�f�[�^�̃����[�h���s���܂�
    void ReloadUIData();

    // �p�[�e�B�N���f�[�^�̃����[�h���s���܂�
    void ReloadParticle2D();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    //=== �ǉ� ===
public:
    void SetFullscreenMode(bool value)
    {
        m_deviceResources->SetFullscreenMode(value);
    }

    void QuitFullscreen()
    {
        m_deviceResources->GetSwapChain()->SetFullscreenState(FALSE, nullptr);
    }

private:

    /*===[ �L�[�{�[�h�X�e�[�g�g���b�J�[ ]===*/
    DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

    /*=====[ �}�E�X�X�e�[�g�g���b�J�[ ]=====*/
    DirectX::Mouse::ButtonStateTracker m_mouseTracker;

    /*======[ ���ʃX�e�[�g�̃|�C���^ ]======*/
    std::unique_ptr<DirectX::CommonStates> m_commonStates;

    /*======[ �X�v���C�g�o�b�`�̃|�C���^ ]======*/
    std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;

    /*======[ �G�t�F�N�g�t�@�N�g���[�̃|�C���^ ]======*/
    std::unique_ptr<DirectX::EffectFactory>m_EffectFactory;

    /*====[�@  �@ �J�����N���X�@�@�@ �@]====*/
    std::unique_ptr <Camera> mCamera;

    /*====[�@�V�[���}�l�[�W���[�N���X�@]====*/
    std::unique_ptr<SceneManager> m_SceneManager;

    /*====[�@�I�[�f�B�I�G���W���N���X�@]====*/
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
};
