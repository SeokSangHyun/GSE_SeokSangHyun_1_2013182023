#pragma once
#include <ctime>
#include <iostream>


struct Point {
	float x;
	float y;
};

class Rect
{
	Point m_pos;
	Point m_dir;
	Point m_speed;

	int m_iLifeTime;

	float m_width;
	float m_height;
	float m_color[4];


public:
	Rect();
	Rect(float x, float y, float width, float height, float spdX, float spdY, int dirX, int dirY, float r, float g, float b, float a);
	~Rect();

	void Rect::SetRect(float x, float y, float width, float height, float spdX, float spdY, int dirX, int dirY, float r, float g, float b, float a);
	void SetPoint(float x, float y) { m_pos.x = x; m_pos.y = y; }
	void SetSpDr(int speedX, int speedY, int dirX, int dirY) { m_speed.x = speedX; m_speed.y = speedY; m_dir.x = dirX; m_dir.y = dirY; }
	void SetDir(Point dir);
	void SetColor(float *col) { m_color[0] = col[0]; m_color[1] = col[1]; m_color[2] = col[2]; m_color[3] = col[3]; }

	Point GetPosition();
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
	Point GetDir() { return m_dir; }
	float* GetColor() { return m_color; }


	void ReduceLife(int damage) { m_iLifeTime -= damage; }
	void AddPosition(float tnow);

	void CollideObject(Rect* obj);
};

