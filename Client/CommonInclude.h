#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>
#include <bitset>
#include <assert.h>

#include "framework.h"
#include "skMath.h"

#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

namespace sk::enums
{
	enum class eLayerType
	{
		Background,
		FirstBossCutScene,
		Middleground,
		Floor,
		SecondBossCutScene,
		Ladder,
		Monster,
		Npc,
		Player,
		Attack,
		MonsAtt,
		Projectile,
		Defend,
		Effect,
		CutScene,
		FrontBackground,
		Portal,//나중에위로
		Wall,//나중에위로
		DownSpace,
		UI,
		ClearScene,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		Rigidbody,
		End,
	};

	enum class eDir
	{
		Right,
		Left,
		None,
	};
}