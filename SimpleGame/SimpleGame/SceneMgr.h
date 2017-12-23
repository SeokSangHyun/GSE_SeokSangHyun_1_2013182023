#pragma once
#include "stdafx.h"
#include "Sound.h"
#include "Object.h"

class SceneMgr
{
	Renderer	*m_rRenderer;
	GLuint		tex_mouse;

	Sound		*m_sound, *m_iBreak, *m_iCreate, *m_soundEnd;
	int			m_iSoundNum, m_iBreakNum, m_iCreateNum, m_soundEndNum;
	float		m_fsound;
	double		m_SceCnt;
	bool		m_earthquake;
	double		m_earthTimer;

	float		m_fTextpos[5];
	float		m_fTestcol[5][3];

	Rect		*m_rpCharObj[MAX_OBJECTCNT];
	Rect		*m_spShotObj[MAX_SHOTOBJECTCNT];
	Rect		*m_pBackground;

	double		m_dBlueCreateTime;
	double		m_dCreateTime;
	bool		m_bCreate;

	GLuint		whetherText;
	GLuint		cloud;
	float		m_sumTime;

	//씬 넘길 때
	bool		stageNext;
	int			g_iGameState;
	int			m_num;//logIn 때 제목
	int			m_texdir;
	float		g_alphaCnt;
	GLuint		tex_logIn;
	GLuint		tex_Name;
	GLuint		tex_End;
	
public:
	POINT	mou_pt;
	SceneMgr();
	~SceneMgr();

public:
	void RedCreate(float x, float y, float width, float height, int team);
	void BlueCreate();
	void CreateShoot(int i, float time);
	void KeyInput(const char k);

	void Update(float time);
	void Render();
	
	/*
	*/
	void Timer(float time);
	bool ShotCollide(int n);
	void DelCheck();
	void Release();
};

