#pragma once

#include "targetver.h"

#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <tchar.h>
#include "Renderer.h"

#define WIN_WIDTH 500
#define WIN_HEIGHT 800

#define RECTSIZE 20
#define BULLETSIZE 10


#define MAX_OBJECTSCOUNT 10
#define MAX_BULLETCOUNT 100
#define	MAX_ARROW		10

#define OBJ_SPEED 200
#define OBJ_LIFE 20

#define COOLBULLET 5
#define COOLCHAR 5
#define COOLMYCHAR 7
#define COOLARROW 4

	enum {OBJ_BUILDING = 10,
	OBJ_CHARACTER,
	OBJ_BULLET,
	OBJ_ARROW};

	enum {
		non = 0,
		RedTeam = 100,
		BlueTeam = 200
	};

	inline bool BCoolTime(float cool_time, float time) {
		if (cool_time < time) {
			return true;
		}
		return false;
	}