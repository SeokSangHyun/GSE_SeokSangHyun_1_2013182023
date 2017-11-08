#pragma once
#include <ctime>
#include <iostream>


struct Point {
	float x;
	float y;
};

class Rect
{
	Point		m_pos;
	Point		m_dir;
	Point		m_speed;

	bool		m_colFlag; // 계속 충돌하는 것을 막기위해서
	int			m_iLifeTime;
	bool		m_flag; // 존재하는지 아닌지

	float		m_width;
	float		m_height;
	float		m_color[4];
	int			m_state;
public:
	Rect();
	Rect(float x, float y, float width, float height, float spdX, float spdY,
		int dirX, int dirY, float r, float g, float b, float a, float life);
	~Rect();

	void SetRect(float x, float y, float width, float height, float spdX, float spdY,
			int dirX, int dirY, float r, float g, float b, float a, float life, int type);

	void SetPoint(float x, float y) { m_pos.x = x; m_pos.y = y; }
	void SetSpDr(int speedX, int speedY, int dirX, int dirY) 
									{ m_speed.x = speedX; m_speed.y = speedY;
									m_dir.x = dirX; m_dir.y = dirY; }
	void SetDir(Point dir);
	void SetColor(float *col)		{ m_color[0] = col[0]; m_color[1] = col[1];
									m_color[2] = col[2]; m_color[3] = col[3]; }

	Point GetPosition();
	float GetWidth()				{ return m_width; }
	float GetHeight()				{ return m_height; }
	Point GetDir()					{ return m_dir; }
	float* GetColor()				{ return m_color; }
	bool GetFlag()					{ return m_flag; }
	int GetLife()					{ return m_iLifeTime; }
	bool GetColFlag()				{ return m_colFlag; }

	void Draw(Renderer *renderer);
	void ReduceLife(int damage)		{ m_iLifeTime -= damage; }
	void AddPosition(float tnow);
	bool CollideObject(Rect* obj);
	void SetColFlagTrue() { m_colFlag = true; };
	void SetColFlagFalse() { m_colFlag = false; };
	void Delete();
	void Update(float stime);
};

