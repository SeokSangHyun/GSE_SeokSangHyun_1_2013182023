#pragma once
#include <ctime>
#include <iostream>


struct Point {
	float x;
	float y;
};

struct Arrow {
	Point pt;
	Point dir;
	Point speed;
	bool flag;
	int state;
};

class Rect
{
	Point		m_pos;
	Point		m_dir;
	Point		m_speed;

	int			m_iLifeTime;
	bool		m_flag; // 존재하는지 아닌지
	bool		m_colFlag;

	float		m_width;
	float		m_height;
	int			m_state;

	Arrow		m_arrow[MAX_ARROW];
	float		actTime;

	//텍스처
	float		m_color[4];
	GLuint		m_texCharacter;
public:
	Rect();
	Rect(float x, float y, float width, float height, float spdX, float spdY,
		float dirX, float dirY, float r, float g, float b, float a, float life, int type);
	~Rect();

	void SetRect(float x, float y, float width, float height, float spdX, float spdY,
		float dirX, float dirY, float r, float g, float b, float a, int life, int type);
	void SetArrow(int type, float time);
	void SetTextImage(Renderer *renderer, char *name);
	void SetPoint(float x, float y) { m_pos.x = x; m_pos.y = y; }
	void SetColor(float *col)		{ m_color[0] = col[0]; m_color[1] = col[1];
									m_color[2] = col[2]; m_color[3] = col[3]; }
	void SetColFlagTrue()			{ m_colFlag = true; };
	void SetColFlagFalse()			{ m_colFlag = false; };


	Point GetPosition();
	Arrow* GetArrow(int n)			{ return &m_arrow[n]; }
	GLuint GetTexcharacter()		{ return m_texCharacter; }
	float GetWidth()				{ return m_width; }
	float GetHeight()				{ return m_height; }
	float* GetColor()				{ return m_color; }
	int GetLife()					{ return m_iLifeTime; }
	bool GetFlag()					{ return m_flag; }
	bool GetColFlag()				{ return m_colFlag; }

	void Draw(Renderer *renderer);
	void DrawImg(Renderer *renderer);
	void ReduceLife(int damage)		{ m_iLifeTime -= damage; }

	void AddPosition(float tnow);
	void AddArrowPosition(float tnow);
	void SuperArmer(float time);

	void Delete();
	void DeleteArrow(int n);
	void Update(float stime);
};

