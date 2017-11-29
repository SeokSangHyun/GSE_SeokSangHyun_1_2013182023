#pragma once
#include "stdafx.h"
#include "Object.h"

class SceneMgr
{
	Renderer *m_rRenderer;

	Rect		*m_rpCharObj[MAX_OBJECTCNT];
	Rect		*m_spShotObj[MAX_SHOTOBJECTCNT];

	double		m_dBlueCreateTime;
	double		m_dCreateTime;
	bool		m_bCreate;

public:
	SceneMgr();
	~SceneMgr();

	void RedCreate(float x, float y, float width, float height, int team);
	void BlueCreate();
	void CreateShoot(int i, float time);
	void Update(float time);
	void Render();
	
	/*
	*/
	void Timer(float time);
	bool Collide(int n);
	bool ShotCollide(int n);
	void DelCheck();
	void Release();
};

