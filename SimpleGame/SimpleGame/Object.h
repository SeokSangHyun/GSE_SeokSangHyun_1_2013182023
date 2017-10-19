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

	float m_width;
	float m_height;
	float m_color[4];

	clock_t st;

public:
	Rect();
	Rect(float x, float y, float width, float height, float r, float g, float b, float a);
	~Rect();

	void SetRect(float x, float y, float width, float height, float r, float g, float b, float a);
	void SetPoint(float x, float y) { m_pos.x = x; m_pos.y = y; }
	void SetSpDr(int speedX, int speedY, int dirX, int dirY) { m_speed.x = speedX; m_speed.y = speedY; m_dir.x = dirX; m_dir.y = dirY; }

	void AddPositionK(Point add_ponit, Point add_dir);
	void AddPosition();

	Point GetPosition();
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
	float* GetColor() { return m_color; }

	clock_t culTime(clock_t st);
};

