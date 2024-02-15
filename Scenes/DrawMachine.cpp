#include "pch.h"
#include "MachineDraw.h"
#include "NecromaLib/Singleton/DeltaTime.h"

#include "NecromaLib/Singleton/ShareJsonData.h"

// �~���̈�ԏ������ꍇ�ɂ�����}�V���̍ő吔
#define CIRCLE_MAX_MIN  4

// �~���̍ő僉�C��
#define CIRCLE_MAX_LINE 6

// ���C�����m�̊Ԋu
#define CIRCLE_LINE_DISTANCE 5.5f

MachineDraw::MachineDraw()
{
}

MachineDraw::~MachineDraw()
{
}

void MachineDraw::Initialize()
{

	m_AMFilter = std::make_unique<AlchemicalMachineFilter>();

	SettingAMMachine_Title();

}

void MachineDraw::Initialize(int number)
{
	m_AMFilter = std::make_unique<AlchemicalMachineFilter>();

	SettingAMMachine_Select(number);

}

void MachineDraw::Update()
{
	for (int i = 0; i < m_AMobjects.size(); i++)
	{

		MovingMachine(i);

	}
}

void MachineDraw::Render()
{
	for (int i = 0; i < m_AMobjects.size(); i++)
	{
		//// None�Ȃ�Δ�΂�
		//if (m_AMobjects[i]->GetModelID() == NONE) return;

		// ���f���̕`��			�I�u�W�F�N�g�Ɋ��蓖�Ă�ꂽID�����ƂɃ��f���z�񂩂�f�[�^�����o��
		m_AMobjects[i]->ModelRender(
			m_AMFilter->HandOverAMModel(m_AMobjects[i]->GetModelID()),
			m_AMFilter->GetRingModel(m_AMobjects[i]->GetModelID()));

		m_AMobjects[i]->Draw();
	}
}

void MachineDraw::Finalize()
{
}

void MachineDraw::MovingMachine(int number)
{

	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// 0,0,0�𒆐S�ɉ�]�ړ�
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	matrix *= DirectX::SimpleMath::Matrix::CreateRotationY(XMConvertToRadians(0.1f)) * deltaTime;

	// ��]��̍��W����
  	m_AMobjects[number]->SetPos(DirectX::SimpleMath::Vector3::Transform(m_AMobjects[number]->GetPos(), matrix));

	m_AMobjects[number]->SetColor(DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f));

}

void MachineDraw::SettingAMMachine_Title()
{
	int counter = 0;

	for (int i = 1; i < CIRCLE_MAX_LINE; i++)
	{
		for (int j = 0; j < CIRCLE_MAX_MIN * i; j++)
		{
			// �}�V����ǉ�
			m_AMobjects.push_back(m_AMFilter->HandOverAMClass(MACHINE_TYPE(i)));

			// ����������
			m_AMobjects[counter]->Initialize();

			// ���݂��郉�C������
			m_AMobjects[counter]->SetLine(i);
			m_AMobjects[counter]->SummonAM(SetVelocityCircle(j, CIRCLE_MAX_MIN * i, i * CIRCLE_LINE_DISTANCE));

			m_AMobjects[counter]->SetColor(DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f));
			counter++;
		}
	}
}

void MachineDraw::SettingAMMachine_Select(int number)
{
	number;

	Stage_ClearData clearData = ShareJsonData::GetInstance().GetClearData();

	int counter = 0;

	m_AMobjects.clear();

	for (int i = 0; i < CIRCLE_MAX_LINE; i++)
	{
		for (int j = 0; j < CIRCLE_MAX_MIN * i; j++)
		{
			// �}�V����ǉ�
			m_AMobjects.push_back(m_AMFilter->HandOverAMClass(clearData.machines[counter].type));

			// ����������
			m_AMobjects[counter]->Initialize();

			m_AMobjects[counter]->SetElement(clearData.machines[counter].element);
			// ���݂��郉�C������
			m_AMobjects[counter]->SetLine(i);
			m_AMobjects[counter]->SummonAM(SetVelocityCircle(j, CIRCLE_MAX_MIN * i, i * CIRCLE_LINE_DISTANCE));

			m_AMobjects[counter]->SetColor(DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f));

			counter++;
		}
	}

}
