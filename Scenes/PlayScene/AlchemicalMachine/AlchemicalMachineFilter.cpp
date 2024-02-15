#include "pch.h"
#include "AlchemicalMachineFilter.h"
#include "AM_None.h"
#include "AM_Attacker.h"
#include "AM_Defenser.h"
#include "AM_Mining.h"
#include "AM_Recovery.h"
#include "AM_Upper.h"

#include "NecromaLib/GameData/CommonStruct.h"

AlchemicalMachineFilter::AlchemicalMachineFilter():
	m_model{}
{
	// ���f���擾
	ShareData& pSD = ShareData::GetInstance();

	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(pSD.GetDevice());
	fx->SetDirectory(L"Resources/Models");

	for (int i = 0; i < MACHINE_TYPE::NUM; i++)
	{
		// ���f�����O�z��ɉ������t�@�C���p�X��ǂݍ���
		std::wostringstream oss;
		oss << "Resources/Models/AM_" << ChangeData::ChangeMachineString((MACHINE_TYPE)i).c_str() << ".cmo";

		m_model[i] = DirectX::Model::CreateFromCMO(pSD.GetDevice(), oss.str().c_str(), *fx);

	}

	// �T�u���f��
	m_subModel[MACHINE_TYPE::ATTACKER] = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/AM_Ring.cmo", *fx);

	m_subModel[MACHINE_TYPE::UPPER] = DirectX::Model::CreateFromCMO(pSD.GetDevice(), L"Resources/Models/AM_UpperCover.cmo", *fx);

	// �G�t�F�N�g�̐ݒ�
	m_subModel[MACHINE_TYPE::UPPER]->UpdateEffects([&](IEffect* effect)
		{
			// ����̓��C�g�����~����
			auto lights = dynamic_cast<IEffectLights*>(effect);
			// �F�ύX
			lights->SetLightDiffuseColor(0, Colors::BlanchedAlmond);
			lights->SetLightDiffuseColor(1, Colors::BlanchedAlmond);
			lights->SetLightDiffuseColor(2, Colors::BlanchedAlmond);

		});
}

AlchemicalMachineFilter::~AlchemicalMachineFilter()
{

}

Model* AlchemicalMachineFilter::HandOverAMModel(MACHINE_TYPE type)
{
	return m_model[type].get();
}

std::unique_ptr<AlchemicalMachineObject> AlchemicalMachineFilter::HandOverAMClass(MACHINE_TYPE type)
{
	switch (type)
	{
	case MACHINE_TYPE::NONE:
		return std::make_unique<AM_None>();
	case MACHINE_TYPE::ATTACKER:
		return std::make_unique<AM_Attacker>();
	case MACHINE_TYPE::DEFENSER:
		return std::make_unique<AM_Defenser>();
	case MACHINE_TYPE::MINING:
		return std::make_unique<AM_Mining>();
	case MACHINE_TYPE::RECOVERY:
		return std::make_unique<AM_Recovery>();
	case MACHINE_TYPE::UPPER:
		return std::make_unique<AM_Upper>();
	default:
		return std::make_unique<AM_None>();
		break;
	}

}

Model* AlchemicalMachineFilter::GetRingModel(MACHINE_TYPE type)
{
	return m_subModel[type].get();
}

void AlchemicalMachineFilter::Finalize()
{
	// ���\�[�X�̉��
	m_model[MACHINE_TYPE::NONE]		.reset();
	m_model[MACHINE_TYPE::ATTACKER]	.reset();
	m_model[MACHINE_TYPE::DEFENSER]	.reset();
	m_model[MACHINE_TYPE::MINING]	.reset();
	m_model[MACHINE_TYPE::RECOVERY]	.reset();
	m_model[MACHINE_TYPE::UPPER]	.reset();
	
	m_model->reset();
}
