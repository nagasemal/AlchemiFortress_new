#include "pch.h"
#include "ParticleUtility.h"
#include "NecromaLib/Singleton/DeltaTime.h"

ParticleUtility::ParticleUtility(float life,
	SimpleMath::Vector3 pos,
	SimpleMath::Vector3 velocity,
	SimpleMath::Vector3 accele,
	SimpleMath::Vector3 startScale, SimpleMath::Vector3 endScale,
	SimpleMath::Color startColor, SimpleMath::Color endColor)
{
	m_startLife = m_life = life;

	m_position = pos;
	m_velocity = velocity;
	m_accele = accele;

	m_startScale = m_nowScale = startScale;
	m_endScale = endScale;


	m_startColor = m_nowColor = startColor;
	m_endColor = endColor;

	m_quaternion = SimpleMath::Quaternion();
	m_rotate = SimpleMath::Vector3();
}

ParticleUtility::~ParticleUtility()
{
}

bool ParticleUtility::Update()
{
	//�����Ɏg���b���v(1�b��1.0f)���擾����B
	float elapsedTime = DeltaTime::GetInstance().GetDeltaTime();

	// ��]�̌v�Z
	SimpleMath::Quaternion q;

	// ���[�@
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(m_rotate.x));

	// �s�b�`
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(m_rotate.y));

	// ���[��
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(m_rotate.z));

	// �p���ɉ�]��������
	m_quaternion = q * m_quaternion;

	// �X�P�[��
	m_nowScale = SimpleMath::Vector3::Lerp(m_startScale, m_endScale, 1.0f - m_life / m_startLife);
	// �F
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, 1.0f - m_life / m_startLife);
	// ���x�̌v�Z
	m_velocity += m_accele * elapsedTime;
	// ���W�̌v�Z
	m_position += m_velocity * elapsedTime;
	// ��]�̉��Z
	m_position += m_quaternion.ToEuler() * elapsedTime;

	m_life -= elapsedTime;

	// ���C�t���O�Ŏ��g�������Ă��炤
	if (m_life < 0.0f)
	{
		return false;
	}

	return true;
}
