#pragma once


struct Point {
	float x;
	float y;
};

class Rect
{
	Point m_pos;
	float m_width;
	float m_height;
	float m_color[4];

public:
	Rect();
	Rect(float x, float y, float width, float height, float r, float g, float b, float a);
	~Rect();

	void SetPoint(float x, float y) { m_pos.x = x; m_pos.y = y; }

	void AddPosition(Point add_ponit, Point dir);
	
	Point GetPosition();
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
	float* GetColor() { return m_color; }
};

