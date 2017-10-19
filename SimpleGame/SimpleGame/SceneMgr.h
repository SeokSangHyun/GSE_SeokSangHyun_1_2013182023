#pragma once
#include "stdafx.h"
#include "Object.h"

class SceneMgr
{
	Rect *		m_rObject[MAX_OBJECTSCOUNT];
	int			m_iRectCount;
public:
	SceneMgr();
	~SceneMgr();

	void Create(float x, float y, float width, float height,
		float r, float g, float b, float a);
	void Update();
	void Delete();
};

