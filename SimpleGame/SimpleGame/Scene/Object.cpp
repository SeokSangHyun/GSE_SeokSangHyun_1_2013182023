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


Point Rect::GetPosition()
{
	return m_pos;
}

clock_t Rect::culTime(clock_t st)
{
	return ((clock() - st)*0.1);
}

void Rect::AddPositionK(Point add_point, Point add_dir)
{
	clock_t tnow = culTime(st);

	m_pos.x += (add_dir.x * add_point.x *tnow);
	m_pos.y += (add_dir.y * add_point.y *tnow);


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

void Rect::AddPosition()
{
	clock_t tnow = culTime(st);
	m_pos.x += (m_dir.x * m_speed.x*tnow);
	m_pos.y += (m_dir.y * m_speed.y*tnow);


	if (m_pos.x >= 250 || m_pos.x <= -250)
		m_dir.x = -1;

	if (m_pos.y >= 250 || m_pos.y <= -250)
		m_dir.y = -1;

	st = clock();
}