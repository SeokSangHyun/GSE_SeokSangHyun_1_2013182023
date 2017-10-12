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
	Point dir;

	float m_width;
	float m_height;
	float m_color[4];

	clock_t st;

public:
	Rect();
	Rect(float x, float y, float width, float height, float r, float g, float b, float a);
	~Rect();

	void SetPoint(float x, float y) { m_pos.x = x; m_pos.y = y; }
	void SetDir(int dirX, int dirY) { dir.x = dirX; dir.y = dirY; }

	void AddPosition(Point add_ponit, Point dir);
	
	Point GetPosition();
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
	float* GetColor() { return m_color; }

	clock_t culTime(clock_t st);
};

