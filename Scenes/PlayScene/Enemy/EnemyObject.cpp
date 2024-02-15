#include "pch.h"
#include "EnemyObject.h"
#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/ModelShader.h"

#include "NecromaLib/GameData/Easing.h"

#include "Scenes/PlayScene/Enemy/EnemyManager.h"

// �R�}���h�p�^�[��
#include "Scenes/PlayScene/Enemy/EnemyList/EnemyCommander.h"

// �X�e�[�g�p�^�[��
#include "Scenes/PlayScene/Enemy/State/IEnemyState.h"
#include "Scenes/PlayScene/Enemy/State/EnemyState.h"

// ������d��
#define GRAVITY 1.2f

// �L�k�F��
#define ELASTICITY_MIN 0.25f
// �L�k�F��
#define ELASTICITY_MAX 0.3f

// ���f���̑傫��
#define MODEL_RAGE 4.5f

EnemyObject::EnemyObject(ENEMY_TYPE type, SimpleMath::Vector3 startPos, int lv, float spawnTime) :
	m_power(1),
	m_hp(10),
	m_lv(lv),
	m_accele(),
	m_lengthVec(),
	m_exp(),
	m_stopFlag(),
	m_enemyType(type),
	m_rotation(),
	m_moveVec(),
	m_aliveTimer(spawnTime),
	m_targetPos(),
	m_element(ELEMENT::NOMAL),
	m_gravityScale(),
	m_moveType(),
	m_dethFlag(false)
{

	m_data.pos = startPos;
	m_data.rage = SimpleMath::Vector3(ELASTICITY_MIN);
	
}

EnemyObject::~EnemyObject()
{
}

void EnemyObject::Initialize()
{
	// �ҋ@��Ԃ�����
	m_stateContext = std::make_shared<EnemyStateContext>(new Enemy_IdlingState());
}

void EnemyObject::Update()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime() * 1.3f;

	// �g�k�A�j���[�V����
	m_data.rage.y = Easing::EaseInCirc(ELASTICITY_MIN, ELASTICITY_MAX, sinf(m_aliveTimer));
	m_data.rage.x = Easing::EaseInCirc(ELASTICITY_MIN, ELASTICITY_MAX, cosf(m_aliveTimer));
	m_data.rage.z = Easing::EaseInCirc(ELASTICITY_MIN, ELASTICITY_MAX, cosf(m_aliveTimer));

	// �������擾�����K������
	m_lengthVec = GetTargetPos() - GetData().pos;
	m_lengthVec.Normalize();

	// �����x�ɏd�͂�K������
	m_gravityScale += GRAVITY * deltaTime;

	// ���g�̃|�C���^�[���R�}���h�ɓn��
	for (auto& command : m_moveCommands)
	{
		command->SetEnemyPtr(*this);
	}

	// ���g�̃|�C���^�[���X�e�[�g�ɓn���čX�V�����𑖂点��
	m_stateContext->Update(this);

	// ���W�̌v�Z
	m_data.pos += m_lengthVec * m_accele * deltaTime;

	// �d�͂ƒ���̌v�Z
	m_data.pos.y -= m_gravityScale * deltaTime;
	m_data.pos.y += m_accele.y * deltaTime;

	// Y���W�����l
	if (m_data.pos.y <= 0.0f)
	{
		m_data.pos.y	= 0.0f;
		m_gravityScale	= 0.0f;
	}

	m_stopFlag = false;

	// ������
	m_lengthVec = SimpleMath::Vector3();
	m_accele = SimpleMath::Vector3();

	m_modelMatrix =
		SimpleMath::Matrix::CreateFromQuaternion(GetRotate())
		* SimpleMath::Matrix::CreateScale(GetRage() * MODEL_RAGE)
		* SimpleMath::Matrix::CreateTranslation(GetPos());

}

void EnemyObject::Draw()
{
	m_stateContext->RenderIcon(this);
}

void EnemyObject::Render(Model* model)
{
	model->UpdateEffects([&](IEffect* effect)
		{
			// ����̓��C�g�����~����
			auto lights = dynamic_cast<IEffectLights*>(effect);
			// �F�ύX
			lights->SetLightDiffuseColor(0, m_color);
			lights->SetLightDiffuseColor(1, m_color);
			lights->SetLightDiffuseColor(2, m_color);

		});

	m_stateContext->Render(this,model);
}

void EnemyObject::Finalize()
{
	for (auto& command : m_moveCommands)
	{
		delete command;
	}

	m_moveCommands.clear();
}

void EnemyObject::HitMachine(bool flag)
{
	// true�Ȃ�Ώ������Ȃ�
	if (m_stopFlag == true) return;

	m_stopFlag = flag;

}

void EnemyObject::Bouns()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	m_data.pos -= (m_lengthVec * (m_accele * 2.0f)) * deltaTime;

}

void EnemyObject::SetEnemyData(Enemy_Data data, EnemyManager* manager)
{
	// lv�ɉ����ăp�����[�^���㏸����
	m_hp		= data.hp		+ (data.hp		* m_lv - 1) / 2;
	m_exp		= data.exp		+ (data.exp		* m_lv - 1) / 2;
	m_power		= data.power	+ (data.power	* m_lv - 1) / 2;
	m_enemyType = data.type;

	if (data.moveType == "ALL") m_moveType = true;
	if (data.moveType == "ONE") m_moveType = false;

	m_element = data.element;
	m_color = ShareJsonData::GetInstance().GetElementColor(m_element);

	// �R�}���h���e�𓮂����N���X
	m_commander = std::make_unique<EnemyCommander>();

	for (auto& moveData : data.moveData)
	{
		// �󂯎�肽�������̓������R�}���h�N���X���擾����
		ICommand_Enemy* command = manager->CreateEnemyMoveCommand(moveData.moveName);
		// �l�擾
		MoveParameter moveParam = MoveParameter();
		moveParam.delay = moveData.delay;
		moveParam.time	= moveData.time;
		moveParam.value = moveData.value;
		// �R�}���h�N���X�Ƀp�����[�^������
		command->SetParam(moveParam);
		// �v�f�����Ԃɓ����
		m_moveCommands.push_back(command);
	}

	// �R�}���_�[�N���X�ɃR�}���h��o�^����
	for (auto& command : m_moveCommands)
	{
		m_commander->AddCommand(command);
	}

}

void EnemyObject::HitBullet(SimpleMath::Vector3 vectol,int power)
{
	// �s����ԂɌ��菈�����s��
	if (m_stateContext->GetState() == IEnemyState::Moveing)

	// �̗͂����炷
	m_hp -= (int)power;
	m_stateContext->TransitionTo(new Enemy_KnockBackState(vectol, (float)power));

}
