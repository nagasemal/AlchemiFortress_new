//--------------------------------------------------------------------------------------
// File: SceneObj.h
//
// 
// 
// Date: 2023.4.19
// Author: Kazuma Nagase
//--------------------------------------------------------------------------------------

#pragma once

#include "NecromaLib/Singleton/ShareData.h"

// V[Ìñ
enum class GAME_SCENE : int
{
	NONE,

	TITLE,
	PLAY,
	RESULT,
	SELECT,
	EDIT,
};

class SceneObj
{
public:

	virtual ~SceneObj()				= default;

	// ú»
	virtual void Initialize()		= 0;

	// XV
	virtual GAME_SCENE Update()		= 0;

	// `æ
	virtual void Draw()				= 0;

	// UIn`æ
	virtual void DrawUI()			= 0;

	// I¹
	virtual void Finalize()			= 0;

private:

};