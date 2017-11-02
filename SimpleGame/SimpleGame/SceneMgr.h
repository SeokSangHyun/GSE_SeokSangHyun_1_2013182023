#pragma once
#include "stdafx.h"
#include "Object.h"

class SceneMgr
{
	Renderer *m_rRenderer;

	Rect 		*m_rpObject;
	Rect		*m_bpObject, *m_bbpObject;
	int			m_iRectDelCount, m_iRectCount;
	int			m_iReduceRate;
	int			m_iBulletCount, m_iBulletDelCount;
public:
	SceneMgr();
	~SceneMgr();

	void Create(float x, float y, float width, float height,
		float spdX, float spdY, int dirX, int dirY,
		float r, float g, float b, float a);
	void CreateBullet(float x, float y, float width, float height,
		float spdX, float spdY, int dirX, int dirY,
		float r, float g, float b, float a);
	void Update(float time);
	void Render();
	
	/*
	*/
	void Timer(float time);
	void Collide(int i);
	void Release();
};

