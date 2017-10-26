#pragma once
#include "stdafx.h"
#include "Object.h"

class SceneMgr
{
	Renderer *m_rRenderer;


	Rect 		*m_rpObject;
	int			m_iRectCount;

	int			m_iReduceRate;
public:
	SceneMgr();
	~SceneMgr();

	void Create(float x, float y, float width, float height,
		float spdX, float spdY, int dirX, int dirY,
		float r, float g, float b, float a);
	void Update(float time);
	void Render();

	void Timer(float time);
	void Release();
};

