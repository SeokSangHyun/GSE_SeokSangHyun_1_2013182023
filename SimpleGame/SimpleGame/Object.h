#pragma once
#include "Renderer.h"
#include <ctime>
#include <iostream>

struct Point
{
	double x;
	double y;
};

class Rect
{
	int			m_aiNum;//객체의 인공지능을 어떤 것으로 할 것인다.
	Point		spin_pos;//상태가 spin일때 
	float		radian;
	Point		back_pos, back_excel;//충돌하면 뒤로 밀림

	Point		m_pos;
	Point		m_dir;
	Point		m_speed;

	int			m_team;
	int			m_iLifeTime;
	bool		m_flag; // 존재하는지 아닌지
	bool		m_colFlag;

	float		m_width;
	float		m_height;
	int			m_state;

	float		actTime;	//생성시간
	float		m_coolTime; //슈퍼아머 쿨타임

	float		m_AniTime;
	int			m_AniCnt[2];
	int			m_colAni;

	float		sumTime;

	//텍스처
	float		m_color[4];
	GLuint		m_texImg;
	GLuint		m_colTextImg;
	float		m_level;

public:
	Rect();
	~Rect();


	void SetRect(float x, float y, float width, float height, float spdX, float spdY,
		float dirX, float dirY, float r, float g, float b, float a, int life, int state, int team, float level);
	void SetTextImage(Renderer *renderer, char *name);
	void SetCollideTextImgage(Renderer *renderer, char *name);
	void SetAniCntDir(int aniDir);

	//쿨타임
	void SetColFlagTrue()			{ m_colFlag = true; };
	void SetColFlagFalse()			{ m_colFlag = false; };

	//변수 Get / Set
	Point GetPosition();
	GLuint GetTexcharacter()		{ return m_texImg; }
	float GetWidth()				{ return m_width; }
	float GetHeight()				{ return m_height; }
	float* GetColor()				{ return m_color; }
	int GetLife()					{ return m_iLifeTime; }
	Point GetDir()					{ return m_dir; };
	bool GetFlag()					{ return m_flag; }
	bool GetColFlag()				{ return m_colFlag; }
	int	GetState()					{ return m_state; }
	int GetTeam()					{ return m_team; };
	float GetLevel()				{ return m_level; };

	void Draw(Renderer *renderer);
	void DrawImg(Renderer *renderer);
	void DrawAnimation(Renderer *renderer);

	bool CollideObject(Rect *col);
	bool Shot(float cooltime, float time);

	void AddPosition(float tnow);
;	void SuperArmer(float cooltime, float time);
	void ReduceLife(int damage)		{ m_iLifeTime -= damage; }
	double CalGauge();

	void Delete(void);
	void Update(float stime);
	void Release(void);
};

