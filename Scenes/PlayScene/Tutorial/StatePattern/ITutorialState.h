#pragma once

// �O���錾
class TutorialStateContext;
class PlayScene;
class TutorialManager;
class ITutorialState
{
protected:

    TutorialStateContext* m_tutorialContext = nullptr;

public:

    virtual ~ITutorialState() {}

    // �`���[�g���A���R���e�L�X�g���Z�b�g����
    void Set_Context(TutorialStateContext* context) { this->m_tutorialContext = context; }

    // �X�V����
    virtual void Update(TutorialManager* manager) = 0;

    // �`�揈��
    virtual void Render(TutorialManager* manager) = 0;

};

class TutorialStateContext
{

private:
    ITutorialState* m_Tutorialstate;

public:
    TutorialStateContext(ITutorialState* state) : m_Tutorialstate(nullptr) { this->TransitionTo(state); }
    ~TutorialStateContext() { delete m_Tutorialstate;}

    // ���̃X�e�[�g�Ɉڍs����
    void TransitionTo(ITutorialState* state) 
    {
        // ��������Ă���ꍇ�Ɍ���s��
        if (this->m_Tutorialstate != nullptr)
         
        // ���݂̃X�e�[�g������
        delete this->m_Tutorialstate;

        // �V�����X�e�[�g�ɓ���ւ���
        this->m_Tutorialstate = state;
        this->m_Tutorialstate->Set_Context(this);
    }

    void Update(TutorialManager* manager) { this->m_Tutorialstate->Update(manager); }

    void Render(TutorialManager* manager) { this->m_Tutorialstate->Render(manager); }

};