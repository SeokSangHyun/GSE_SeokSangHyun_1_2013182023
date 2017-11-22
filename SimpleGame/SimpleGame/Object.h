#pragma once
#include <ctime>
#include <iostream>


struct Point {
	float x;
	float y;
};

struct ShootObj {
	Point pt;
	Point dir;
	Point speed;
	bool flag;
	int state;
	float color[4];
};

class Rect
{
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

	ShootObj	*m_shotObj;
	float		actTime;	//생성시간
	float		m_coolTime; //슈퍼아머 쿨타임


	//텍스처
	float		m_color[4];
	GLuint		m_texCharacter;
public:
	Rect();
	Rect(float x, float y, float width, float height, float spdX, float spdY,
		float dirX, float dirY, float r, float g, float b, float a, float life, int type);
	~Rect();

	void SetRect(float x, float y, float width, float height, float spdX, float spdY,
		float dirX, float dirY, float r, float g, float b, float a, int life, int type, int team);
	void SetShotObj(int type, float r, float g, float b, float cooltime, float time);
	void SetTextImage(Renderer *renderer, char *name);
	void SetPoint(float x, float y) { m_pos.x = x; m_pos.y = y; }
	void SetColor(float *col)		{ m_color[0] = col[0]; m_color[1] = col[1];
									m_color[2] = col[2]; m_color[3] = col[3]; }
	void SetColFlagTrue()			{ m_colFlag = true; };
	void SetColFlagFalse()			{ m_colFlag = false; };


	Point GetPosition();
	Point GetShotPosition(int i)	{ return m_shotObj[i].pt; };
	ShootObj* GetShotObj(int n)		{ return &m_shotObj[n]; }
	GLuint GetTexcharacter()		{ return m_texCharacter; }
	float GetWidth()				{ return m_width; }
	float GetHeight()				{ return m_height; }
	float* GetColor()				{ return m_color; }
	int GetLife()					{ return m_iLifeTime; }
	bool GetFlag()					{ return m_flag; }
	bool GetShotFlag(int i)			{ return m_shotObj[i].flag; }
	bool GetColFlag()				{ return m_colFlag; }
	int	GetState()					{ return m_state; };

	void Draw(Renderer *renderer);
	void DrawImg(Renderer *renderer);
	void ReduceLife(int damage)		{ m_iLifeTime -= damage; }

	bool CollideObject(Rect *col);
	bool CollideShotObject(Point *col);

	void AddPosition(float tnow);
	void AddShotObjPosition(float tnow);
	void SuperArmer(float cooltime, float time);

	void Delete();
	void DeleteShotObj(int n);
	void Update(float stime);
};

