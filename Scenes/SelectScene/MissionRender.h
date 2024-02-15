//--------------------------------------------------------------------------------------
// File: MissionRender.h
//
//�@�~�b�V�������e��\������N���X
// 
// Date: 2023.8.10
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------
#pragma once
#include "Scenes/PlayScene/UI/Number.h"

class SpriteLoder;
class MissionAnimation;
class DrawMissionLabel;
struct Stage_Data;
struct Stage_Condition;

class MissionRender
{
public:

	MissionRender(SimpleMath::Vector2 pos,SimpleMath::Vector2 rage);
	~MissionRender();

	void Render(Stage_Data data);

	// �}�V���n�̃~�b�V�������e��`��
	void Render_MachineMission(std::vector<Stage_Condition> stageData);

	// �G�l�~�[�n�̃~�b�V�������e��`��
	void Render_EnemyMission(std::vector<Stage_Condition> stageData);

	// �B���n�̃~�b�V�������e��`��
	void Render_AlchemiMission(std::vector<Stage_Condition> stageData);

	// �j��n�̃~�b�V�������e��`��
	void Render_DestroyMission(std::vector<Stage_Condition> stageData);

	// �����n�̃~�b�V�������e��`��
	void Render_LvUpMission(std::vector<Stage_Condition> stageData);

	// �C�U�n�̃~�b�V�������e��`��
	void Render_RepairMission(std::vector<Stage_Condition> stageData);

	// ���\�[�X�m�یn�~�b�V�������e��`��
	void Render_ResourceMission(std::vector<Stage_Condition> stageData);

	// ���_Lv�̃~�b�V�������e��`��
	void Render_BaseLvMission(std::vector<Stage_Condition> stageData);

	// �^�C�}�[�n�̃~�b�V�������e��`��
	void Render_TimerMission(std::vector<Stage_Condition> stageData);

	// �s�̕ϐ���0�ɂ���
	void LineReset();

	// ���C���̃J�E���^�[��Ԃ�
	const int GetLineCount() const  { return m_lineCount; }

	const SimpleMath::Vector2 GetPos()  ;
	const SimpleMath::Vector2 GetRage() ;

	void SetPos(SimpleMath::Vector2 pos) { m_position = pos; }
	void SetRage(SimpleMath::Vector2 rage) { m_rage = rage; }

	// �����x��ݒ肷��
	void SetAlpha(float newAlpha) { m_alpha = newAlpha; }
	// �����x��Ԃ�
	const float GetAlpha() { return m_alpha; }

private:

	void ContentDraw(std::vector<Stage_Condition> stageData, ID3D11ShaderResourceView* nameTex,int purposeNum);
	void LabelDraw(SimpleMath::Vector2 pos);

private:

	std::unique_ptr<Number> m_number;

	SimpleMath::Vector2 m_position;
	SimpleMath::Vector2 m_rage;

	float m_alpha;

	int m_lineCount;
	int m_missionNum;

};