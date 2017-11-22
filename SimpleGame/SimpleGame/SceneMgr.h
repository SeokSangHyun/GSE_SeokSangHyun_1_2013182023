#pragma once
#include "stdafx.h"
#include "Object.h"

class SceneMgr
{
	Renderer *m_rRenderer;
	float col[2][4];

	Rect 		*m_rpRedObject[MAX_OBJECTSCOUNT], *m_cpRedObject[3];
	Rect		*m_rpBlueObject[MAX_OBJECTSCOUNT], *m_cpBlueObject[3];

	double		m_dBlueCreateTime;
	double		m_dCreateTime;
	bool		m_bCreate;

public:
	SceneMgr();
	~SceneMgr();

	void RedCreate(float x, float y, float width, float height, int team);
	void BlueCreate();
	void CreateShoot(int i, float time);
	void CreateArrow(int i, float time);
	void Update(float time);
	void Render();
	
	/*
	*/
	void Timer(float time);
	bool Collide(Rect *temp,Rect *col);
	bool CollideShotObj(Rect * temp, Rect * col);
	void Release();
};

