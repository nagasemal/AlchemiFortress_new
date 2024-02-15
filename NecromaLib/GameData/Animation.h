//--------------------------------------------------------------------------------------
// File: Animation.h
//
// �f���^�^�C���𓾂�ׂ̃V���O���g���N���X
//
// Date: 2023.4.19
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "Easing.h"

struct AnimationData
{
	enum Type
	{
		STOP = 0,
		LOOP = 1,
	};

	// ����
	float time;
	// �ŏ�
	float min;
	// �ő�
	float max;
	// ����
	float middle;
	// �l�̓�����
	Type type;
	// ���x�J��Ԃ��Ă��邩
	int iterations;
	// ���ۂ̑J�ڒl
	float anim;

	/// <summary>
	/// �A�j���[�V�����ɓ��������\����
	/// ������������l�����݂���A�j���[�V���������Ȃ�L�p
	/// �����I��min,max�̒l�ŃN�����v���������܂��B
	/// </summary>
	/// <param name="time">�J�n����</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <param name="middle">�����l</param>
	/// <param name="type">�l����ꑱ�����ۂ̓���</param>
	AnimationData(float value = 0.0f, float min = 0.0f, float max = 1.0f, float middle = 0.5f, Type type = Type::STOP)
	{
		this->time = value;
		this->min = min;
		this->max = max;
		this->middle = middle;
		this->type = type;
		anim = 0;

		iterations = 0;
	}

	inline bool operator==(const AnimationData& value) const
	{
		return this->time == value.time;
	}

	inline bool operator!=(const AnimationData& value) const
	{
		return this->time != value.time;
	}

	inline AnimationData operator+(const AnimationData& value) const
	{
		return AnimationData(this->time + value.time,min,max);
	}

	inline AnimationData operator+(const float value) const
	{
		return AnimationData(this->time + value, min, max);
	}

	inline AnimationData operator-(const AnimationData& value) const
	{
		return AnimationData(this->time - value.time,min, max);
	}

	inline AnimationData operator*(const AnimationData& value) const
	{
		return AnimationData(this->time * value.time, min, max);
	}

	inline AnimationData operator*(const float value) const
	{
		return AnimationData(this->time * value, min, max);
	}

	inline AnimationData operator/(const AnimationData& value) const
	{
		return AnimationData(this->time / value.time, min, max);
	}

	inline AnimationData operator/(const float value) const
	{
		return AnimationData(this->time / value, min, max);
	}

	inline AnimationData& operator=(const AnimationData& value)
	{
		this->time = value.time;

		return *this;
	}


	inline operator float()
	{
		return time;
	}

	inline AnimationData& operator+=(const AnimationData& value)
	{

		this->time += value.time;

		if (MaxCheck())
		{
			this->time = max;
			iterations++;

			if (type == LOOP) 	this->time = min;
		}
		return *this;
	}

	inline AnimationData& operator-=(const AnimationData& value)
	{
		this->time -= value.time;

		if (MinCheck())
		{

			this->time = min;
			iterations++;

			if (type == LOOP) 	this->time = max;
		}

		return *this;
	}
	
	inline float Clamp()
	{
		return std::min(std::max(time, min), max);
	}

	// time��max�̒l���z����
	inline bool MaxCheck()
	{
		return time >= max;
	}

	// time��min�̒l���������
	inline bool MinCheck()
	{
		return time <= min;
	}

	// time��middle���z����
	inline bool MiddleFlag()
	{
		return time >= middle;
	}

	inline bool ActiveFlag()
	{
		return !MaxCheck() && !MinCheck();
	}

};