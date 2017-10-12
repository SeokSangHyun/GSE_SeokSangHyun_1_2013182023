#include "stdafx.h"
#include "Object.h"


Rect::Rect()
{
	st = clock();
}

Rect::Rect(float x, float y, float width, float height, float r, float g, float b, float a)
{
	m_pos.x = x;
	m_pos.y = y;

	m_width = width;
	m_height = height;

	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_color[3] = a;

	st = clock();
}


Rect::~Rect()
{
}

void Rect::SetRect(float x, float y, float width, float height, float r, float g, float b, float a)
{
	m_pos.x = x;
	m_pos.y = y;

	m_width = width;
	m_height = height;

	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_color[3] = a;

	st = clock();
}

void Rect::AddPosition(Point add_point, Point add_dir)
{
	clock_t tnow = culTime(st);
	m_pos.x += (add_dir.x * add_point.x*tnow);
	m_pos.y += (add_dir.y * add_point.y*tnow);


	if (m_pos.x >= 300)
		m_pos.x = -300;
	else if (m_pos.x <= -300)
		m_pos.x = 300;

	if (m_pos.y >= 300)
		m_pos.y = -300;
	else if (m_pos.y <= -300)
		m_pos.y = 300;

	st = clock();
}


Point Rect::GetPosition()
{
	return m_pos;
}

clock_t Rect::culTime(clock_t st)
{
	return ((clock() - st)*0.1);
}
