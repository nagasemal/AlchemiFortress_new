#include "pch.h"
#include "Particle_2D.h"

#include "NecromaLib/Singleton/DeltaTime.h"
#include "NecromaLib/Singleton/ShareJsonData.h"
#include "NecromaLib/Singleton/ShareData.h"
#include "NecromaLib/Singleton/SpriteLoder.h"
#include "NecromaLib/Singleton/ModelShader.h"
#include "NecromaLib/GameData/Easing.h"

#include <algorithm>
#include <random>

ParticleUtility_2D::ParticleUtility_2D(float life,
	SimpleMath::Vector2 pos,
	SimpleMath::Vector2 velocity,
	SimpleMath::Vector2 accele,
	SimpleMath::Vector2 startScale,
	SimpleMath::Vector2 endScale,
	SimpleMath::Color startColor,
	SimpleMath::Color endColor)
{
	m_life			= life;
	m_position		= pos;
	m_velocity		= velocity;
	m_accele		= accele;
	m_startScale	= startScale;
	m_endScale		= endScale;
	m_startColor	= startColor;
	m_endColor		= endColor;

	m_startLife		= life;
	m_rotate		= 0.0f;
	m_startRotate	= 0.0f;
	m_endRotate		= 0.0f;
}

ParticleUtility_2D::~ParticleUtility_2D()
{
}

bool ParticleUtility_2D::Update()
{
	//�����Ɏg���b���v(1�b��1.0f)���擾����B
	float elapsedTime = DeltaTime::GetInstance().GetDeltaTime();

	// �X�P�[��
	m_nowScale = SimpleMath::Vector2::Lerp(m_startScale, m_endScale, 1.0f - m_life / m_startLife);

	// �F
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, 1.0f - m_life / m_startLife);

	// ���x�̌v�Z
	m_velocity	+= m_accele * elapsedTime;

	// ��]�p
	m_rotate = Easing::Lerp(m_startRotate, m_endRotate, 1.0f - m_life / m_startLife);

	// ���W�̌v�Z
	m_position += m_velocity * elapsedTime;

	m_life		-= elapsedTime;

	// ���C�t���O�Ŏ��g�������Ă��炤
	if (m_life < 0.0f)
	{
		return false;
	}

	return true;
}

Particle_2D::Particle_2D():
	m_particleNum(1),
	m_particleSpawnTime(1),
	m_timer(1),
	m_drawType()
{
}

Particle_2D::~Particle_2D()
{
}

bool Particle_2D::OnShot(std::string tag, SimpleMath::Vector2 pos, bool flag)
{

	UpdateLinerEffect(tag);

	// flase�Ȃ�ʂ��Ȃ�
	if (!flag)
	{
		return false;
	}

	// ��������������
	for (int i = 0; i < m_particleNum; i++)
	{
		m_particleUtility.push_back(CreateEffectParam(tag, pos));
	}

	return true;
}

void Particle_2D::Update(std::string tag,SimpleMath::Vector2 pos, bool flag)
{

	UpdateLinerEffect(tag);

	// flase�Ȃ�ʂ��Ȃ�
	if (!flag) return;

	// ���Ԃ������琶�����s��
	if (m_timer > m_particleSpawnTime)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			m_particleUtility.push_back(CreateEffectParam(tag, pos));
			m_timer = 0.0f;
		}
	}

}

void Particle_2D::UpdateParticle()
{

	float deltaTime = DeltaTime::GetInstance().GetNomalDeltaTime();

	m_timer += deltaTime;

	//Particle�̗��̍X�V�������s��
	for (std::list<ParticleUtility_2D>::iterator ite = m_particleUtility.begin(); ite != m_particleUtility.end(); ite++)
	{
		// �q�N���X����false�ŏ���
		if (!(ite)->Update())
		{
			ite = m_particleUtility.erase(ite);
			if (ite == m_particleUtility.end()) break;
		}
	}

	// ���W�z���������
	m_points.clear();
}

void Particle_2D::Render()
{

	ShareData& pSD = ShareData::GetInstance();
	SpriteLoder::TextureData texData = SpriteLoder::GetInstance().GetNormalParticle();

	// �ʏ�`��
	if (m_drawType == DrawNone)
	{
		pSD.GetSpriteBatch()->Begin(SpriteSortMode_Texture, pSD.GetCommonStates()->NonPremultiplied());
	}
	// ���Z�`��
	else if (m_drawType == Add)
	{
		pSD.GetSpriteBatch()->Begin(SpriteSortMode_Texture, pSD.GetCommonStates()->Additive());
	}

	RECT rect = { 0,0,texData.width,texData.height };
	
	for (std::list<ParticleUtility_2D>::iterator ite = m_particleUtility.begin(); ite != m_particleUtility.end(); ite++)
	{
	
		pSD.GetSpriteBatch()->Draw(texData.tex.Get(),
			ite->GetPosition(),
			&rect,
			ite->GetNowColor(),
			ite->GetRad(),
			SimpleMath::Vector2(static_cast<float>(texData.width / 2), static_cast<float>(texData.height / 2)),
			ite->GetNowScale());
	
	}
	
	pSD.GetSpriteBatch()->End();
}

void Particle_2D::Render(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, RECT rect)
{

	ShareData& pSD = ShareData::GetInstance();
	pSD.GetSpriteBatch()->Begin(SpriteSortMode_Deferred, pSD.GetCommonStates()->NonPremultiplied());

	for (std::list<ParticleUtility_2D>::iterator ite = m_particleUtility.begin(); ite != m_particleUtility.end(); ite++)
	{

		pSD.GetSpriteBatch()->Draw(texture.Get(),
			ite->GetPosition(),
			&rect,
			ite->GetNowColor(),
			ite->GetRad(),
			SimpleMath::Vector2(static_cast<float>(rect.right / 2), static_cast<float>(rect.bottom / 2)),
			ite->GetNowScale());

	}

	pSD.GetSpriteBatch()->End();

}

float Particle_2D::JudgeVal(float val, float max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());

	if (val >= max) return val;

	std::uniform_real_distribution<> dist(val, max);

	return static_cast<float>(dist(engine));
}

SimpleMath::Vector2 Particle_2D::JudgeVal(SimpleMath::Vector2 val, SimpleMath::Vector2 max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());

	SimpleMath::Vector2 out = SimpleMath::Vector2();

	if (val.x >= max.x)
	{
		out.x = val.x;
	}
	else
	{
		std::uniform_real_distribution<> dist(val.x, max.x);
		out.x = static_cast<float>(dist(engine));
	}

	if (val.y >= max.y)
	{
		out.y = val.y;
	}
	else
	{
		std::uniform_real_distribution<> dist(val.y, max.y);
		out.y = static_cast<float>(dist(engine));
	}

	return out;
}

SimpleMath::Color Particle_2D::JudgeVal(SimpleMath::Color val, SimpleMath::Color max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());

	SimpleMath::Color  out = SimpleMath::Color();

	if (val.x >= max.x) out.x = val.x;
	else
	{
		std::uniform_real_distribution<> dist(val.x, max.x);
		out.x = static_cast<float>(dist(engine));
	}

	if (val.y >= max.y) out.y = val.y;
	else
	{
		std::uniform_real_distribution<> dist(val.y, max.y);
		out.y = static_cast<float>(dist(engine));
	}

	if (val.z >= max.z) out.z = val.z;
	else
	{
		std::uniform_real_distribution<> dist(val.z, max.z);
		out.z = static_cast<float>(dist(engine));
	}

	if (val.w >= max.w) out.w = val.w;
	else
	{
		std::uniform_real_distribution<> dist(val.w, max.w);
		out.w = static_cast<float>(dist(engine));
	}

	return out;
}

void Particle_2D::UpdateLinerEffect(std::string tag)
{
	for (std::list<LinerEffectData>::iterator ite = m_linerEffectData.begin(); ite != m_linerEffectData.end(); ite++)
	{
		// ���`���H��G�t�F�N�g
		ite->timer += DeltaTime::GetInstance().GetNomalDeltaTime() * ite->speed * ite->maxCount;

		ite->spawnTime += DeltaTime::GetInstance().GetNomalDeltaTime();

		if (ite->spawnTime > m_particleSpawnTime)
		{
			for (int i = 0; i < m_particleNum; i++)
			{
				m_particleUtility.push_back(CreateEffectParam(tag, ite));
			}

			ite->spawnTime = 0.0f;
		}

		// ���Ԃ�������폜����
		if (ite->timer > 1.0f)
		{
			ite->count++;
			ite->timer = 0.0f;

			// �z��O���w������z��̍Ō�����w��
			ParticleLinerType linerType = ShareJsonData::GetInstance().GetParticle2DPram(tag).linerType;
			if		(linerType == Chain_E)
			{
				ite->first	= ite->first - 1 < 0 ? (int)ite->maxCount - 1: ite->first - 1;
				ite->last   = ite->last  - 1 < 0 ? (int)ite->maxCount - 1: ite->last  - 1;
			}
			// �z��O���w������z��̍Ő�[���w��
			else if (linerType == Chain_F)
			{
				ite->first = ite->first + 1 >= ite->maxCount ? 0 :ite->first + 1;
				ite->last =  ite->last  + 1 >= ite->maxCount ? 0 :ite->last + 1;
			}

			if (ite->count >= ite->maxCount)
			{
				ite = m_linerEffectData.erase(ite);
				if (ite == m_linerEffectData.end()) break;
			}
		}
	}
}

ParticleUtility_2D Particle_2D::CreateEffectParam(std::string type, SimpleMath::Vector2 pos)
{
	Particle2D_Pram parm = ShareJsonData::GetInstance().GetParticle2DPram(type);

	std::random_device seed;
	std::default_random_engine engine(seed());

	// Max�ƋK��l���r���āAMax���K��l�ȉ��Ȃ�Η�����p���Ȃ�
	ParticleUtility_2D outData = parm.praticleData;
	ParticleUtility_2D max = parm.random_Max;

	std::uniform_real_distribution<> directionDist(0, DirectX::XM_2PI);
	float rand = static_cast<float>(directionDist(engine));

	// �ʒu����
	outData.SetPosition(CreatePosition(parm, pos, rand, engine));

	// ���x�̌v�Z
	outData.SetVelocity(CreateVelocity(parm,pos,rand));

	// �����x�̌v�Z
	outData.SetAccele(CreateAccele(parm, pos, rand));

	// �傫���̐ݒ�
	outData.SetStartScale(JudgeVal(outData.GetStartScale(), max.GetStartScale()));
	outData.SetEndScale(JudgeVal(outData.GetEndScale(), max.GetEndScale()));

	// �������Ԃ̐ݒ�
	outData.SetStartLife(JudgeVal(outData.GetStartLife(), max.GetStartLife()));
	outData.SetLife(outData.GetLife());

	// �F�̐ݒ�
	outData.SetStartColor(JudgeVal(outData.GetStartColor(), max.GetStartColor()));
	outData.SetEndColor(JudgeVal(outData.GetEndColor(), max.GetEndColor()));

	// �ʂ̐ݒ�
	m_particleNum = (int)JudgeVal((float)parm.num, (float)parm.maxNum);

	// �����Ԋu�̐ݒ�
	m_particleSpawnTime = parm.time;

	m_drawType = parm.drawType;

	return outData;
}

ParticleUtility_2D Particle_2D::CreateEffectParam(std::string type, std::list<LinerEffectData>::iterator linerData)
{

	Particle2D_Pram parm = ShareJsonData::GetInstance().GetParticle2DPram(type);

	std::random_device seed;
	std::default_random_engine engine(seed());

	// Max�ƋK��l���r���āAMax���K��l�ȉ��Ȃ�Η�����p���Ȃ�

	ParticleUtility_2D outData = parm.praticleData;
	ParticleUtility_2D max = parm.random_Max;

	std::uniform_real_distribution<> directionDist(0, DirectX::XM_2PI);
	float rand = static_cast<float>(directionDist(engine));

	// �ʒu����
	outData.SetPosition(CreatePosition(parm, linerData, rand, engine));

	// ���x�̌v�Z
	outData.SetVelocity(CreateVelocity(parm, linerData->savePos, rand));

	// �����x�̌v�Z
	outData.SetAccele(CreateAccele(parm, linerData->savePos, rand));

	// �傫���̐ݒ�
	outData.SetStartScale(JudgeVal(outData.GetStartScale(), max.GetStartScale()));
	outData.SetEndScale(JudgeVal(outData.GetEndScale(), max.GetEndScale()));

	// �������Ԃ̐ݒ�
	outData.SetStartLife(JudgeVal(outData.GetStartLife(), max.GetStartLife()));
	outData.SetLife(outData.GetLife());

	// ��]�p�̐ݒ�
	outData.SetStateRad(JudgeVal(outData.GetStateRad(), max.GetStateRad()));
	outData.SetEndRad(JudgeVal(outData.GetEndRad(), max.GetEndRad()));

	// �F�̐ݒ�
	outData.SetStartColor(JudgeVal(outData.GetStartColor(), max.GetStartColor()));
	outData.SetEndColor(JudgeVal(outData.GetEndColor(), max.GetEndColor()));

	// �ʂ̐ݒ�
	m_particleNum = (int)JudgeVal((float)parm.num, (float)parm.maxNum);

	// �����Ԋu�̐ݒ�
	m_particleSpawnTime = parm.time;

	return outData;
}

SimpleMath::Vector2 Particle_2D::CreatePosition(Particle2D_Pram pram, SimpleMath::Vector2 pos, float random, std::default_random_engine randomEngine)
{
	SimpleMath::Vector2 outPosition;

	int arraySize = (int)pram.points.size() + (int)m_points.size();

	// �n�_������ꍇ
	if (arraySize > 0)
	{
		for (auto& pointPos : m_points)
		{
			pram.points.push_back(pointPos);
		}

		// �ǂ��Ƃǂ����q���̂������Ō��߂�
		std::uniform_real_distribution<> dist_Num(0, (int)pram.points.size());
		int pointNum = static_cast<int>(dist_Num(randomEngine));

		float ratio = 0.0f;
		SimpleMath::Vector2 linearPos = SimpleMath::Vector2::Zero;

		// �I��n�_����1������������0�ȉ��Ȃ�Δz��O�Q�Ƃ��N�����Ă��܂����߁A�Ō���ɂ���
		int index = pointNum - 1 >= 0 ? pointNum - 1 : (int)pram.points.size() - 1;

		if (arraySize == 2)
		{
			index = 0;
			pointNum = 1;
		}

		// ������g�������������_����
		auto CreateLineData = [=]()
		{
			LinerEffectData effectData;
			effectData.savePos	= pos;
			effectData.speed	= JudgeVal(pram.linerSpeed, pram.maxLinerSpeed);
			effectData.maxCount = arraySize;

			return effectData;
		};

		if (pram.linerType == LinerNone)
		{
			// �o��������`��̊��������߂�
			std::uniform_real_distribution<> dist_ratio(0.0f, 1.0f);

			ratio = static_cast<float>(dist_ratio(randomEngine));
			linearPos = SimpleMath::Vector2::Lerp(pram.points[index], pram.points[pointNum], ratio);
		}

		// ���]
		if (pram.linerType == Start_F)
		{
			LinerEffectData effectData = CreateLineData();
			effectData.first = index;
			effectData.last  = pointNum;

			m_linerEffectData.push_back(effectData);

			linearPos = SimpleMath::Vector2::Lerp(pram.points[effectData.first], pram.points[effectData.last], 0.0f);
		}

		// ���]
		if (pram.linerType == Start_E)
		{
			LinerEffectData effectData = CreateLineData();
			effectData.first = pointNum;
			effectData.last  = index;

			m_linerEffectData.push_back(effectData);

			linearPos = SimpleMath::Vector2::Lerp(pram.points[effectData.first], pram.points[effectData.last], 0.0f);
		}

		// �S�Ă̔z���ʂ� ���]
		if (pram.linerType == Chain_F)
		{
			index = 0;
			pointNum = 1;

			LinerEffectData effectData = CreateLineData();
			effectData.first = index;
			effectData.last  = pointNum;

			m_linerEffectData.push_back(effectData);

			linearPos = SimpleMath::Vector2::Lerp(pram.points[effectData.first], pram.points[effectData.last], 0.0f);
		}

		// �S�Ă̔z���ʂ� ���]
		if (pram.linerType == Chain_E)
		{
			index = 0;
			pointNum = 1;

			LinerEffectData effectData = CreateLineData();
			effectData.first = pointNum;
			effectData.last  = index;

			m_linerEffectData.push_back(effectData);

			linearPos = SimpleMath::Vector2::Lerp(pram.points[effectData.first], pram.points[effectData.last], 0.0f);
		}

		outPosition = pos + linearPos + random * SimpleMath::Vector2(JudgeVal(pram.rage, pram.maxRage), JudgeVal(pram.rage, pram.maxRage));

	}
	// �n�_���Ȃ��ꍇ
	else
	{
		outPosition = pos + random * SimpleMath::Vector2(JudgeVal(pram.rage, pram.maxRage), JudgeVal(pram.rage, pram.maxRage));
	}

	return outPosition;
}

SimpleMath::Vector2 Particle_2D::CreatePosition(Particle2D_Pram pram, std::list<LinerEffectData>::iterator linerData, float random, std::default_random_engine randomEngine)
{
	SimpleMath::Vector2 outPosition;
	randomEngine;

	// �n�_������ꍇ
	if (pram.points.size() + m_points.size() > 0)
	{
		for (auto& pointPos : m_points)
		{
			pram.points.push_back(pointPos);
		}

		SimpleMath::Vector2 linearPos = SimpleMath::Vector2::Zero;

		linearPos = SimpleMath::Vector2::Lerp(pram.points[linerData->first], pram.points[linerData->last], linerData->timer);

		outPosition = linerData->savePos + linearPos + random * SimpleMath::Vector2(JudgeVal(pram.rage, pram.maxRage), JudgeVal(pram.rage, pram.maxRage));

	}

	return outPosition;
}

SimpleMath::Vector2 Particle_2D::CreateVelocity(Particle2D_Pram pram, SimpleMath::Vector2 pos, float random)
{

	SimpleMath::Vector2 outVelocity;

	// �e����悤�ȃG�t�F�N�g
	if (pram.velocityType == Brast)
	{
		SimpleMath::Vector2 randVelo = JudgeVal(pram.praticleData.GetVelocity(), pram.random_Max.GetVelocity());

		SimpleMath::Vector2 vectol = pos - (random * randVelo);
		vectol.Normalize();

		outVelocity = vectol * randVelo;
	}
	// �ʏ�
	else
	{
		outVelocity = random * JudgeVal(pram.praticleData.GetVelocity(), pram.random_Max.GetVelocity());
	}

	return outVelocity;

}

SimpleMath::Vector2 Particle_2D::CreateAccele(Particle2D_Pram pram, SimpleMath::Vector2 pos, float random)
{
	SimpleMath::Vector2 outaccele;

	// �e����悤�ȃG�t�F�N�g
	if (pram.acceleType == Brast)
	{
		SimpleMath::Vector2 vectol = pos - (random * JudgeVal(pram.praticleData.GetAccele(), pram.random_Max.GetAccele()));
		vectol.Normalize();

		outaccele = vectol;
	}
	else
	{
		outaccele = random * JudgeVal(pram.praticleData.GetAccele(), pram.random_Max.GetAccele());
	}

	return outaccele;
}

Particle_2D::ParticleMoveType ParticleData_Change::ChangeMoveType(std::string name)
{
	if (name == "None")		return Particle_2D::ParticleMoveType::MoveNone;
	if (name == "Brast")	return Particle_2D::ParticleMoveType::Brast;

	return Particle_2D::ParticleMoveType::MoveNone;
}

Particle_2D::ParticleLinerType ParticleData_Change::ChangeLinerType(std::string name)
{
	if (name == "None")		return Particle_2D::ParticleLinerType::LinerNone;
	if (name == "Point")	return Particle_2D::ParticleLinerType::Point;
	if (name == "Start_E")	return Particle_2D::ParticleLinerType::Start_E;
	if (name == "Start_F")	return Particle_2D::ParticleLinerType::Start_F;
	if (name == "Chain_E")	return Particle_2D::ParticleLinerType::Chain_E;
	if (name == "Chain_F")	return Particle_2D::ParticleLinerType::Chain_F;

	return Particle_2D::ParticleLinerType::LinerNone;
}

Particle_2D::ParticleNextType ParticleData_Change::ChangeNextType(std::string name)
{
	if (name == "None")		return Particle_2D::ParticleNextType::NextNone;
	if (name == "Division")	return Particle_2D::ParticleNextType::Division;

	return Particle_2D::ParticleNextType::NextNone;
}

Particle_2D::ParticleDrawType ParticleData_Change::ChangeDrawType(std::string name)
{
	if (name == "None")		return Particle_2D::ParticleDrawType::DrawNone;
	if (name == "Add")	return Particle_2D::ParticleDrawType::Add;

	return Particle_2D::ParticleDrawType::DrawNone;
}

