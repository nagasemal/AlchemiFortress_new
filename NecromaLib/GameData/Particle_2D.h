#pragma once
#include <list>
#include <random>

class ParticleUtility_2D;
struct Particle2D_Pram;
class Particle_2D
{
public:

	// �`��^�C�v
	enum ParticleDrawType : int
	{
		DrawNone = 0,
		Add = 1
	};

	// �p�[�e�B�N���̓�����
	enum ParticleMoveType : int
	{
		MoveNone = 0,	// �Ȃ�
		Brast = 1		// �n�_�𒆐S�ɒe����
	};

	// ���̃p�[�e�B�N�����o���ۂ̋���
	enum ParticleNextType : int
	{
		NextNone = 0,	// �Ȃ�
		Division = 1	// ���􂵂Ȃ��玟�̃p�[�e�B�N�����o��
	};

	// �p�[�e�B�N���̐��`��̓�����
	enum ParticleLinerType : int
	{
		LinerNone = 0,	// �Ȃ�
		Point   = 1,	// �e�_���Ƃɕۊǂ��������_���ɐ���
		Start_F = 2,	// ���`����n�_����I�_�ւȂ���悤�ɐ���(���])
		Start_E = 3,	// ���`����n�_����I�_�ւȂ���悤�ɐ���(���])
		Chain_F = 4,	// ���`���S�Ẵ|�C���g��ʂ�Ȃ���i��
		Chain_E = 5,	// ���`���S�Ẵ|�C���g��ʂ�Ȃ���i��

	};

	// �p�[�e�B�N���̉�]�̎d��
	enum ParticleRotateType : int
	{
		RotateNone	= 0,	// �Ȃ�
		Always		= 1,	// ��ɉ�]
		Direction	= 2,	// �i�s����������
	};

	struct LinerEffectData
	{
		// �O�����H��G�t�F�N�g�����ۂɎg�p���鎞�ԕϐ�
		float timer		= 0.0f;
		// �����Ԋu
		float spawnTime = 0.0f;
		// �O�����H��G�t�F�N�g�̃X�s�[�h
		float speed = 0.0f;
		// �O�����H��G�t�F�N�g�̋N�_�ƂȂ�ʒu
		SimpleMath::Vector2 savePos = SimpleMath::Vector2();

		// �n�_�̔z��ԍ�
		int first		= 0;
		// �I�_�̔z��ԍ�
		int last		= 0;

		// ���݉�
		int count		= 0;
		int maxCount	= 0;

	};

public:
	Particle_2D();
	~Particle_2D();

	// �P���p
	bool OnShot(std::string tag, SimpleMath::Vector2 pos, bool flag);
	// �펞�p
	void Update(std::string tag, SimpleMath::Vector2 pos, bool flag);

	// �p�[�e�B�N���𓮂���/��������
	void UpdateParticle();
	
	void Render();
	void Render(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,RECT rect);


	const SimpleMath::Vector2 GetPointPos(int index)	{ return m_points[index]; }
	void AddPoint(SimpleMath::Vector2 point)			{ m_points.push_back(point); }
	const std::vector<SimpleMath::Vector2> GetPoints()	{ return m_points;}

	float JudgeVal(float val,float max);
	SimpleMath::Vector2 JudgeVal(SimpleMath::Vector2 val, SimpleMath::Vector2 max);
	SimpleMath::Color JudgeVal(SimpleMath::Color val, SimpleMath::Color max);


private:

	void UpdateLinerEffect(std::string tag);

	ParticleUtility_2D CreateEffectParam(std::string tag, SimpleMath::Vector2 pos);
	ParticleUtility_2D CreateEffectParam(std::string tag, std::list<LinerEffectData>::iterator linerData);

	SimpleMath::Vector2 CreatePosition(Particle2D_Pram pram, SimpleMath::Vector2 pos, float random, std::default_random_engine randomEngine);
	SimpleMath::Vector2 CreatePosition(Particle2D_Pram pram, std::list<LinerEffectData>::iterator linerData, float random, std::default_random_engine randomEngine);
	SimpleMath::Vector2 CreateVelocity(Particle2D_Pram pram, SimpleMath::Vector2 pos, float random);
	SimpleMath::Vector2 CreateAccele(Particle2D_Pram pram, SimpleMath::Vector2 pos, float random);

private:

	// �p�[�e�B�N���z��
	std::list<ParticleUtility_2D>	m_particleUtility;

	// ��x�ɏo��Particle�̗�
	int m_particleNum;

	// �����Ԃ̓_�����Ԃ��߂Ɏg��
	std::vector<SimpleMath::Vector2> m_points;
	// �O�����H��G�t�F�N�g�̐ݒ�
	std::list<LinerEffectData> m_linerEffectData;

	// �p�[�e�B�N���̐����Ԋu
	float m_particleSpawnTime;

	float m_timer;

	ParticleDrawType m_drawType;

private:

	////�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	//struct ConstBuffer
	//{
	//	SimpleMath::Matrix		matWorld;
	//	SimpleMath::Matrix		matView;
	//	SimpleMath::Matrix		matProj;
	//	SimpleMath::Vector4		Diffuse;
	//};
	//
	//static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//
	//// �o�b�t�@
	//Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
	//// ���̓��C�A�E�g
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//
	//// �v���~�e�B�u�o�b�`
	//std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	////�R�����X�e�[�g
	//std::unique_ptr<DirectX::CommonStates>							m_states;
	//
	//// ���_�V�F�[�_
	//Microsoft::WRL::ComPtr<ID3D11VertexShader>						m_vertexShader;
	//// �s�N�Z���V�F�[�_
	//Microsoft::WRL::ComPtr<ID3D11PixelShader>						m_pixelShader;
	//// �W�I���g���V�F�[�_
	//Microsoft::WRL::ComPtr<ID3D11GeometryShader>					m_geometryShader;

};

//�@====================[�@�l�̑J�ڂ��v�Z����N���X�@]
class ParticleUtility_2D
{
	//�ϐ�
private:

	//���W
	SimpleMath::Vector2 m_position;

	//���x
	SimpleMath::Vector2 m_velocity;
	//�����x
	SimpleMath::Vector2 m_accele;

	//�X�P�[��
	SimpleMath::Vector2 m_nowScale;
	SimpleMath::Vector2 m_startScale;
	SimpleMath::Vector2 m_endScale;

	//��������
	float m_life;
	float m_startLife;

	//���[�e�[�V����
	float	m_rotate;
	float	m_startRotate;
	float	m_endRotate;

	//�J���[
	SimpleMath::Color m_nowColor;
	SimpleMath::Color m_startColor;
	SimpleMath::Color m_endColor;

	//�֐�
public:
	/// <summary>
	/// �����ݒ�
	/// </summary>
	/// <param name="life">��������</param>
	/// <param name="pos">�����ʒu</param>
	/// <param name="velocity">����</param>
	/// <param name="accele">�����x</param>
	/// <param name="startScale">�����X�P�[��</param>
	/// <param name="endScale">�ŏI�X�P�[��</param>
	/// <param name="startColor">�����J���[</param>
	/// <param name="endColor">�ŏI�J���[</param>
	ParticleUtility_2D(
		float life = 1.0f,
		SimpleMath::Vector2 pos = { 0.0f,0.0f},
		SimpleMath::Vector2 velocity = { 0.0f,0.0f},
		SimpleMath::Vector2 accele = { 0.0f,0.0f},
		SimpleMath::Vector2 startScale = { 1.0f,1.0f}, SimpleMath::Vector2 endScale = { 0.0f,0.0f },
		SimpleMath::Color startColor = { 1.0f,1.0f,1.0f,1.0f }, SimpleMath::Color endColor = { 0.0f,0.0f,0.0f,0.0f });
	//�f�X�g���N�^
	~ParticleUtility_2D();

	// �X�V
	bool Update();

	//getter

	// �|�W�V����
	const SimpleMath::Vector2 GetPosition() { return m_position; }

	// ����
	const SimpleMath::Vector2 GetVelocity() { return m_velocity; }

	// �����x
	const SimpleMath::Vector2 GetAccele() { return m_accele; }

	// �傫�� �F ����
	const SimpleMath::Vector2 GetNowScale() { return m_nowScale; }
	// �傫�� �F �J�n��
	const SimpleMath::Vector2 GetStartScale() { return m_startScale; }
	// �傫�� �F �I����
	const SimpleMath::Vector2 GetEndScale() { return m_endScale; }

	// �������� : ����
	const float GetLife() { return m_life; }
	// �������� : �J�n��
	const float GetStartLife() { return m_startLife; }

	// �F : ����
	const SimpleMath::Color GetNowColor() { return m_nowColor; }
	// �F : �J�n��
	const SimpleMath::Color GetStartColor() { return m_startColor; }
	// �F : �I����
	const SimpleMath::Color GetEndColor() { return m_endColor; }

	// ��]	�F ����
	const float GetRad() { return m_rotate; }
	// ��] : �J�n��
	const float GetStateRad() { return m_startRotate; }
	// ��] : �I����
	const float GetEndRad() { return m_endRotate; }

	// setter

	// �|�W�V����
	void SetPosition(SimpleMath::Vector2 pos)	{ m_position = pos; }
	// ����
	void SetVelocity(SimpleMath::Vector2 vel)	{ m_velocity = vel; }
	// �����x
	void SetAccele(SimpleMath::Vector2 acc)		{ m_accele = acc; }

	// �傫�� �F ����
	void SetNowScale(SimpleMath::Vector2 sca)	{ m_nowScale = sca; }
	// �傫�� �F �J�n��
	void SetStartScale(SimpleMath::Vector2 sca) { m_startScale = sca; }
	// �傫�� �F �I����
	void SetEndScale(SimpleMath::Vector2 sca)	{ m_endScale = sca; }

	// �������� �F ����
	void SetLife(float life)					{ m_life = life; }
	// �������� �F �J�n��
	void SetStartLife(float life)				{ m_startLife = life; }

	// �F �F ����
	void SetNowColor(SimpleMath::Color col)		{ m_nowColor = col; }
	// �F �F �J�n��
	void SetStartColor(SimpleMath::Color col)	{ m_startColor = col; }
	// �F �F �I����
	void SetEndColor(SimpleMath::Color col)		{ m_endColor = col; }

	// ��]�p
	void SetRad(float deg)						{ m_rotate = XMConvertToRadians(deg); }
	// ��] : �J�n��
	void SetStateRad(float deg)					{ m_startRotate = XMConvertToRadians(deg); }
	// ��] : �J�n��	
	void SetEndRad(float deg)					{ m_endRotate = XMConvertToRadians(deg); }
};

// �p�[�e�B�N����StringTo�񋓑̂��T�|�[�g
namespace ParticleData_Change
{

	Particle_2D::ParticleMoveType ChangeMoveType(std::string name);

	Particle_2D::ParticleLinerType ChangeLinerType(std::string name);

	Particle_2D::ParticleNextType ChangeNextType(std::string name);

	Particle_2D::ParticleDrawType ChangeDrawType(std::string name);

}