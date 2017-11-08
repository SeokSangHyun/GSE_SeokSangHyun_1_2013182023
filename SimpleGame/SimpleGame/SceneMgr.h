#pragma once
#include "stdafx.h"
#include "Object.h"

class SceneMgr
{
	Renderer *m_rRenderer;

	Rect 		*m_rpObject;
	Rect		*m_bpObject, *m_cpObject;
	int			m_iRectDelCount, m_iRectCount;
	double		m_iReduceRate;
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
	void CollidePBtwP(int i);
	void CollidePBtwB(int i);
	void CollidePBtwC(int i);
	void Release();
};

