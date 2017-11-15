#pragma once

#include "targetver.h"

#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <tchar.h>
#include "Renderer.h"

#define WIN_WIDTH 500
#define WIN_HEIGHT 500

#define RECTSIZE 20
#define BULLETSIZE 10


#define MAX_OBJECTSCOUNT 10
#define MAX_BULLETCOUNT 100
#define	MAX_ARROW		10

#define OBJ_SPEED 200
#define OBJ_LIFE 30

	enum {OBJ_BUILDING = 10,
	OBJ_CHARACTER,
	OBJ_BULLET,
	OBJ_ARROW};