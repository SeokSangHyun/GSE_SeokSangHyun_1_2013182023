#pragma once
#include "stdafx.h"
#include "Object.h"

class SceneMgr
{
	Renderer *m_rRenderer;
	float col[2][4];

	Rect 		*m_rpObject;
	Rect		*m_bpObject, *m_cpObject;
	double		m_iReduceRate;

	int			m_iRectDelCount, m_iRectCount;
	int			m_iBulletCount, m_iBulletDelCount;
	int			m_iArrowCount, m_iArrowDelCount;

public:
	SceneMgr();
	~SceneMgr();

	void Create(float x, float y, float width, float height);
	void CreateShoot();
	void CreateArrow(int i, float time);
	void Update(float time);
	void Render();
	
	/*
	*/
	void Timer(float time);
	bool Collide(Rect *temp,Rect *col);
	void CollideArrow(int i);
	void Release();
};

