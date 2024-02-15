#include "pch.h"
#include "FieldObjectManager.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/ShareJsonData.h"

#include "Scenes/PlayScene/Enemy/EnemyManager.h"

#include <algorithm>
#include <random>

#include "DirectXHelpers.h"

// ���[���h��Ԃɏo��UI�̑傫������
#define WORLD_UI_SIZE 0.01f

FieldObjectManager::FieldObjectManager():
	m_crystalTomouseFlag()
{
}

FieldObjectManager::~FieldObjectManager()
{
}

void FieldObjectManager::Initialize()
{
	ShareData& pSD = ShareData::GetInstance();

	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(pSD.GetDevice());
	fx->SetDirectory(L"Resources/Models");

	// ���f���̓ǂݍ���
	m_floorModel = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/Ground.cmo", *fx);
	m_crystalModel = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/Crystal.cmo", *fx);
	m_baseModel_Towor = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/Tower_1.cmo", *fx);
	m_baseModel_Pillar = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/Tower_2.cmo", *fx);

	// �������f���̃G�t�F�N�g�̐ݒ�
	m_crystalModel->UpdateEffects([&](IEffect* effect)
		{
			// ����̓��C�g�����~����
			auto lights = dynamic_cast<IEffectLights*>(effect);

			// ���̓�������ύX
			lights->SetAmbientLightColor(SimpleMath::Color(0.4f, 0.4f, 1.f, 0.2f));

		});

	// �G�t�F�N�g�̐ݒ�
	m_baseModel_Towor->UpdateEffects([&](IEffect* effect)
		{
			// ����̓��C�g�����~����
			auto lights = dynamic_cast<IEffectLights*>(effect);

			// �F�ύX
			lights->SetLightDiffuseColor(0, Colors::Gray);
			lights->SetLightDiffuseColor(1, Colors::Gray);
			lights->SetLightDiffuseColor(2, Colors::Gray);

		});

	// ����
	m_field = std::make_unique<Field>();
	m_playerBase = std::make_unique<PlayerBase>();
	m_crystals = std::make_unique<std::list<Crystal>>();

	m_field->Initialize();
	m_playerBase->Initialize();

	CrystalSpawn(30);

	ShareJsonData& pSJD = ShareJsonData::GetInstance();

	for (int i = 0; i < pSJD.GetStageData().crystalPos.size(); i++)
	{
		SimpleMath::Vector2 loadCrysralPos = pSJD.GetStageData().crystalPos[i];

		SimpleMath::Vector3 crystalPos = SimpleMath::Vector3(loadCrysralPos.x,-1.0f, loadCrysralPos.y);

		m_crystals->push_back(*std::make_unique<Crystal>(crystalPos, (float)cos(5)));
	}

	// �N���X�^���̏���������
	for (std::list<Crystal>::iterator it = m_crystals->begin(); it != m_crystals->end(); it++)
	{
		it->Initialize();
	}

	//�@====================[�@�r���{�[�h�`��Ɏg�p�@]
//�@�@|=> �G�t�F�N�g���쐬
	m_effect = std::make_unique<BasicEffect>(ShareData::GetInstance().GetDevice());
	m_effect->SetTextureEnabled(true);
	m_effect->SetVertexColorEnabled(true);
	m_effect->SetLightingEnabled(false);

	//�@�@|=> ���̓��C�A�E�g���쐬
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect(
			ShareData::GetInstance().GetDevice(),
			m_effect.get(),
			VertexPositionColorTexture::InputElements,
			VertexPositionColorTexture::InputElementCount,
			m_inputLayout.ReleaseAndGetAddressOf())
	);

}

void FieldObjectManager::Update(EnemyManager* pEnemyManager)
{

	// ���̍X�V����
	m_field->Update();

	// �v���C���[���_�̍X�V����
	m_playerBase->Update();

	m_crystalTomouseFlag = false;

	m_playerBase->SetExp(pEnemyManager->GetNockDownEnemyExp() + m_playerBase->GetExp());

	// �N���X�^���̍X�V����
	for (std::list<Crystal>::iterator it = m_crystals->begin(); it != m_crystals->end(); it++)
	{
		it->Update();

		// �N���X�^�����}�E�X�ɐG��Ă���
		if (!m_crystalTomouseFlag)
		{
			m_crystalTomouseFlag = it->GetHitMouse();
		}
	}

}

void FieldObjectManager::Draw()
{

	// ���̕`�揈��
	m_field->Render(m_floorModel.get());

	// �v���C���[���_�̕`�揈��
	m_playerBase->Render(m_baseModel_Towor.get());

	// �N���X�^���̕`�揈��
	for (std::list<Crystal>::iterator it = m_crystals->begin(); it != m_crystals->end(); it++)
	{
		it->Render(m_crystalModel.get());
	}

}

void FieldObjectManager::DrawBillboardUI()
{
	ShareData& pSD = ShareData::GetInstance();
	auto status = pSD.GetCommonStates();
	auto camera = ShareData::GetInstance().GetCamera();
	auto context = pSD.GetContext();

	//�@====================[�@�r���{�[�h�s�񐶐��@]
	//�@�@|=>�@�X�N���[�����W��Y�����{�|�t�Ȃ̂�-1��������
	SimpleMath::Matrix invertY = SimpleMath::Matrix::CreateScale(1.0f, -1.0f, 1.0f);

	//�@�@|=> �r���[�s��̉�]��ł������s����쐬����
	SimpleMath::Matrix invView = camera->GetViewMatrix().Invert();
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	//�@�@|=> �G�t�F�N�g�Ƀr���[�s��Ǝˉe�s���ݒ肷��
	m_effect->SetView(camera->GetViewMatrix());
	m_effect->SetProjection(camera->GetProjectionMatrix());


	//�@====================[�@UI�����[���h��Ԃɏo��]
	pSD.GetSpriteBatch()->Begin(SpriteSortMode_Deferred, status->NonPremultiplied(), nullptr, status->DepthNone(), status->CullCounterClockwise(), [=]
		{
			// ���[���h�s��쐬
			SimpleMath::Matrix world =
				SimpleMath::Matrix::CreateScale(WORLD_UI_SIZE) *
				invertY *
				invView *
				SimpleMath::Matrix::CreateTranslation(m_playerBase->GetPos() + SimpleMath::Vector3(0.0f, 8.0f, 0.0f));

			// �G�t�F�N�g��K������
			m_effect->SetWorld(world);
			m_effect->Apply(context);
			// ���̓��C�A�E�g��ݒ肷��
			context->IASetInputLayout(m_inputLayout.Get());
		});

	m_playerBase->RenderBillboardUI();

	pSD.GetSpriteBatch()->End();

}

void FieldObjectManager::WriteDepath()
{
	// ���̕`�揈��
	m_field->WriteDepth(m_floorModel.get());

	// �v���C���[���_�̕`�揈��
	m_playerBase->WriteDepth(m_baseModel_Towor.get());

	// �N���X�^���̕`�揈��
	for (std::list<Crystal>::iterator it = m_crystals->begin(); it != m_crystals->end(); it++)
	{
		it->WriteDepth(m_crystalModel.get());
	}


}

void FieldObjectManager::Finalize()
{
	// ���̍폜����
	m_field->Finalize();
	m_field.reset();

	// �v���C���[���_�̍X�V����
	m_playerBase->Finalize();
	m_playerBase.reset();

	// �N���X�^���̕`�揈��
	for (std::list<Crystal>::iterator it = m_crystals->begin(); it != m_crystals->end(); it++)
	{
		it->Finalize();
	}

	m_crystals.reset();

	delete m_crystals.get();

}

void FieldObjectManager::CrystalSpawn(int num)
{
	num;
}
