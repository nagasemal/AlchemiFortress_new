//--------------------------------------------------------------------------------------
// File: AlchemicalMachineFilter.h
//
//�@�󂯎���������ɉ����ă��f����N���X�A�����X�e�[�^�X��n���N���X
// 
// Date: 2023.6.5
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once
#include "Scenes/PlayScene/AlchemicalMachine/AlchemicalMachineObject.h"

class AlchemicalMachineFilter
{
public:
	AlchemicalMachineFilter();
	~AlchemicalMachineFilter();

	/// <summary>
	/// �}�V���^�C�v�ɉ����ă��f����n��
	/// </summary>
	/// <param name="type">�A���P�~�J���}�V���̃^�C�v</param>
	/// <returns></returns>
	DirectX::Model* HandOverAMModel(MACHINE_TYPE type);

	/// <summary>
	/// �}�V���^�C�v�ɉ�����AlchemicalMachineObject���p�������N���X��n��
	/// </summary>
	/// <param name="type">�A���P�~�J���}�V���̃^�C�v</param>
	/// <returns></returns>
	std::unique_ptr<AlchemicalMachineObject> HandOverAMClass(MACHINE_TYPE type);

	//// �{�̂Ƃ͕ʂœ��������O���f����n���܂�
	Model* GetRingModel(MACHINE_TYPE type);

	void Finalize();

private:

	std::unique_ptr<DirectX::Model> m_model[MACHINE_TYPE::NUM];

	std::unique_ptr<DirectX::Model> m_subModel[MACHINE_TYPE::NUM];

};