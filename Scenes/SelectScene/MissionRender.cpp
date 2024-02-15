#include "pch.h"
#include "MissionRender.h"

#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/GameData/SpriteCutter.h"

#define KERNING_X 64
#define KERNING_Y 48

#define STRING_TEX_RAGE1_X 128
#define STRING_TEX_RAGE2_X 112
#define STRING_TEX_RAGE_Y 28

#define TEXT_COLOR SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.75f)
#define CLEAR_COLOR SimpleMath::Color(1.0f, 0.0f, 0.0f, 0.85f)

#define MISSION_RAGE_X 190.0f
#define MISSION_RAGE_Y 24.0f

#define LABEL_RAGE_X 360
#define LABEL_RAGE_Y 48

MissionRender::MissionRender(SimpleMath::Vector2 pos, SimpleMath::Vector2 rage)
{

	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	Stage_Data missionData = pSJD.GetStageData();

	m_position	= pos;
	m_rage		= rage;
	m_lineCount = 0;

	UI_Data data = pSJD.GetUIData("MissionText");
	m_alpha = data.option["MaxAlpha"];

	//�@====================[�@���ݐ�,�ڕW���̕`��N���X�@]
	m_number = std::make_unique<Number>(pos,SimpleMath::Vector2(0.35f,0.25f));

	m_missionNum = 0;

	//�@====================[�@�S�~�b�V���������擾����@]
	for (int i = 0; i < MISSION_TYPE::MISSION_NUM; i++)
	{
		m_missionNum += static_cast<int>(missionData.condition[i].size());
	}
}

MissionRender::~MissionRender()
{
}


void MissionRender::Render(Stage_Data data)
{
	m_lineCount = 0;

	// �����x�̏���ݒ�
	ShareJsonData& pSJD = ShareJsonData::GetInstance();
	UI_Data ui_data = pSJD.GetUIData("MissionText");
	if (ui_data.option["MaxAlpha"] <= m_alpha)
	{
		m_alpha = ui_data.option["MaxAlpha"];
	}

	//�@====================[�@�}�V���n�~�b�V�����@]
	Render_MachineMission(data.condition[MISSION_TYPE::SPAWN]);
	Render_AlchemiMission(data.condition[MISSION_TYPE::ALCHEMI]);

	//�@====================[�@�G�l�~�[�n�~�b�V�����@]
	Render_EnemyMission(data.condition[MISSION_TYPE::ENEMY_KILL]);

	//�@====================[�@���\�[�X�n�~�b�V�����@]
	Render_BaseLvMission(data.condition[MISSION_TYPE::BASELV]);
	Render_ResourceMission(data.condition[MISSION_TYPE::RESOURCE]);

	//�@====================[�@���Ԍn�~�b�V�����@]
	Render_TimerMission(data.condition[MISSION_TYPE::TIMER]);

}

void MissionRender::Render_MachineMission(std::vector<Stage_Condition> stageData)
{

	SpriteLoder& pSL = SpriteLoder::GetInstance();

	ContentDraw(stageData, pSL.GetMachineNameTexture().tex.Get(), MISSION_TYPE::SPAWN);

}

void MissionRender::Render_EnemyMission(std::vector<Stage_Condition> stageData)
{

	SpriteLoder& pSL = SpriteLoder::GetInstance();

	ContentDraw(stageData, pSL.GetEnemyNameTexture().Get(), 2);

}

void MissionRender::Render_AlchemiMission(std::vector<Stage_Condition> stageData)
{

	SpriteLoder& pSL = SpriteLoder::GetInstance();

	ContentDraw(stageData, pSL.GetMachineNameTexture().tex.Get(), 3);

}

void MissionRender::Render_DestroyMission(std::vector<Stage_Condition> stageData)
{

	SpriteLoder& pSL = SpriteLoder::GetInstance();

	ContentDraw(stageData, pSL.GetMachineNameTexture().tex.Get(),4);
}

void MissionRender::Render_LvUpMission(std::vector<Stage_Condition> stageData)
{

	SpriteLoder& pSL = SpriteLoder::GetInstance();

	ContentDraw(stageData, pSL.GetMachineNameTexture().tex.Get(), 1);

}

void MissionRender::Render_RepairMission(std::vector<Stage_Condition> stageData)
{

	SpriteLoder& pSL = SpriteLoder::GetInstance();

	ContentDraw(stageData, pSL.GetMachineNameTexture().tex.Get(), 5);

}

void MissionRender::Render_ResourceMission(std::vector<Stage_Condition> stageData)
{
}

void MissionRender::Render_BaseLvMission(std::vector<Stage_Condition> stageData)
{

	// �ڕW�l��1�ȉ��Ȃ�΍X�V����K�v������
	if (stageData[0].value <= 1)	return;

	SimpleMath::Vector2 pos = m_position;

	pos.y += m_lineCount * KERNING_Y;

	SimpleMath::Color color = TEXT_COLOR;

	if (stageData[0].progress >= stageData[0].value) color = CLEAR_COLOR;

	pos.x += KERNING_X;
	m_number->SetPosition(pos);
	m_number->SetColor(color);
	m_number->Render_SelectScene(stageData[0].progress, stageData[0].value);

	m_lineCount++;
}

void MissionRender::Render_TimerMission(std::vector<Stage_Condition> stageData)
{
	stageData;
}

void MissionRender::LineReset()
{
	m_lineCount = 0;
}

const SimpleMath::Vector2 MissionRender::GetPos()
{

	SimpleMath::Vector2 pos = SimpleMath::Vector2();

	pos.x = m_position.x;
	pos.y += m_position.y +  GetRage().y - KERNING_Y;

	return pos;
}

const SimpleMath::Vector2 MissionRender::GetRage()
{
	SimpleMath::Vector2 rage = SimpleMath::Vector2(MISSION_RAGE_X, MISSION_RAGE_Y * (float)m_missionNum);

	return rage;
}

void MissionRender::ContentDraw(std::vector<Stage_Condition> stageData, ID3D11ShaderResourceView* nameTex, int purposeNum)
{

	// �ڕW�l��-1�ȉ��Ȃ�΍X�V����K�v�������@(�d�l��v�f���Ȃ��Ă͂Ȃ�Ȃ��ׂ��̌`�Ŏ������s��)
	if (stageData[0].value <= 0)	return;

	SpriteLoder& pSL = SpriteLoder::GetInstance();
	ShareData& pSD = ShareData::GetInstance();
	auto pSB = pSD.GetSpriteBatch();

	for (int i = 0; i < stageData.size(); i++)
	{

		SimpleMath::Vector2 pos = m_position;

		pos.y += m_lineCount * KERNING_Y;

		SimpleMath::Color color = SimpleMath::Color(1.0f,1.0f,1.0f,m_alpha);

		if (stageData[i].progress >= stageData[i].value) color = SimpleMath::Color(1.0f, 0.0f, 0.0f, m_alpha);

		// �w�ʂɕ`�悷��e�N�X�`��
		LabelDraw(pos);

		// �~�b�V�����`��F�ړI��
		{
			RECT machineNameRect = SpriteCutter(STRING_TEX_RAGE1_X, STRING_TEX_RAGE_Y, (int)ChangeData::ChangeMachine(stageData[i].condition), 0);

			pSB->Draw(nameTex,
				pos,
				&machineNameRect,
				color,
				0.0f,
				DirectX::XMFLOAT2(STRING_TEX_RAGE1_X / 2, STRING_TEX_RAGE_Y / 2),
				m_rage);
		}

		// �~�b�V�����`��F�ڑ���
		{
			RECT letterRect = SpriteCutter(STRING_TEX_RAGE_Y, STRING_TEX_RAGE_Y, 0, 0);

			pos.x += KERNING_X;

			pSB->Draw(pSL.GetLetterTexture().Get(),
				pos,
				&letterRect,
				color,
				0.0f,
				DirectX::XMFLOAT2(STRING_TEX_RAGE_Y / 2, STRING_TEX_RAGE_Y / 2),
				m_rage);
		}

		// �~�b�V�����`��F���e
		{
			RECT missionRect = SpriteCutter(STRING_TEX_RAGE2_X, STRING_TEX_RAGE_Y, purposeNum, 0);

			pos.x += KERNING_X;

			pSB->Draw(pSL.GetMissionTexture().Get(),
				pos,
				&missionRect,
				color,
				0.0f,
				DirectX::XMFLOAT2(STRING_TEX_RAGE2_X / 2, STRING_TEX_RAGE_Y / 2),
				m_rage);
		}

		// �ړI�l�ƌ��ݒl�̐����̕`��
		{
			pos.x += KERNING_X;
			m_number->SetPosition(pos);
			m_number->SetColor(color);
			m_number->Render_SelectScene(stageData[i].progress, stageData[i].value);
		}

		m_lineCount++;
	
	}

}

void MissionRender::LabelDraw(SimpleMath::Vector2 pos)
{

	SpriteLoder& pSL = SpriteLoder::GetInstance();
	ShareData& pSD = ShareData::GetInstance();
	auto pSB = pSD.GetSpriteBatch();


	RECT labelRect = SpriteCutter(LABEL_RAGE_X, LABEL_RAGE_Y, 0, 0);

	pSB->Draw(pSL.GetMissionLabelTexture().Get(),
		pos,
		&labelRect,
		SimpleMath::Color(1.0f,1.0f,1.0f,m_alpha),
		0.0f,
		DirectX::XMFLOAT2(LABEL_RAGE_X / 4, LABEL_RAGE_Y / 2),
		m_rage);

}
