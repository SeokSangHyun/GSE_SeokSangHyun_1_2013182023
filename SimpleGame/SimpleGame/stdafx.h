#pragma once

#include "targetver.h"

#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <tchar.h>
#include "Renderer.h"

#define WIN_WIDTH 500
#define WIN_HEIGHT 800

#define RECTSIZE 40
#define BULLETSIZE 10


#define MAX_OBJECTCNT 60
#define MAX_SHOTOBJECTCNT	300

#define OBJ_SPEED 500
#define BULLET_SPEED 500
#define ARROW_SPEED 400
#define OBJ_LIFE 60
#define OBJ_BULLET_LIFE 4
#define OBJ_BUILD_LIFE 300

#define LEV_BUILDING 0.1
#define LEV_CHAR 0.2
#define LEV_BULLET 0.3
#define LEV_ARROW 0.3

#define COOLBULLET 5
#define COOLCHAR 4
#define COOLMYCHAR 2
#define COOLARROW 4
#define COOLSPARMER 1


#define GaugeHeight 5


enum gamestate { logIn = 1000, inGame };
enum Ai { normal = 0, spin };


	enum { DOWN = 0, LEFT = 1, RIGHT = 2, UP = 3};

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