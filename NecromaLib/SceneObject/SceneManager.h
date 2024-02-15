#pragma once

#include <GeometricPrimitive.h> // �����́A���A�e�B�[�|�b�g�Ȃ�
#include <Effects.h>        // ���_�̍ʐF�A���C�e�B���O�A�e�N�X�`���Ȃ�

#include "StepTimer.h"
#include "NecromaLib/Singleton/InputSupport.h"
#include "NecromaLib/Singleton/ShareData.h"

#include "Fade.h"
#include "SceneObj.h"
#include "Scenes/DataManager.h"

class MouseStaging;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

    void Initialize();
    void Update(const DX::StepTimer& timer);
    void Render();
    void Finalize();

    // �V�[���֌W����
    // �V�[���̍쐬
    void CreateScene();

    // �V�[���̍폜
    void DeleteScene();

private:

    // ���̃V�[���ԍ�
    GAME_SCENE m_NextScene;

    // �V�[��
    SceneObj* m_Scene;

    Fade* m_Fade;

    // ���L����ϐ��̊Ǘ�
    DataManager* m_DataManager;

    // �X�v���C�g�o�b�`
    std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;

    // �X�v���C�g�t�H���g
    std::unique_ptr<DirectX::SpriteFont> m_SpriteFont;


    // �}�E�X�̉��o����
    std::unique_ptr<MouseStaging> m_mouseStaging;

};