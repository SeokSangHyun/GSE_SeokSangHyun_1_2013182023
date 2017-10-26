#include "stdafx.h"
#include "Object.h"


Rect::Rect()
{
}

Rect::Rect(float x, float y, float width, float height, float spdX, float spdY, int dirX, int dirY, float r, float g, float b, float a)
{
	m_pos.x = x;
	m_pos.y = y;

	m_width = width;
	m_height = height;

	m_speed.x = spdX;
	m_speed.y = spdY;

	m_dir.x = dirX;
	m_dir.y = dirY;

	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_color[3] = a;

	m_iLifeTime = 50;
}


Rect::~Rect()
{
}

void Rect::SetRect(float x, float y, float width, float height, float spdX, float spdY, int dirX, int dirY, float r, float g, float b, float a)
{
	m_pos.x = x;
	m_pos.y = y;

	m_width = width;
	m_height = height;

	m_speed.x = spdX;
	m_speed.y = spdY;

	m_dir.x = dirX;
	m_dir.y = dirY;

	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_color[3] = a;

	m_iLifeTime = 50;
}


void Rect::AddPosition(float tnow)
{
	m_pos.x += (m_dir.x * m_speed.x*tnow*0.001);
	m_pos.y += (m_dir.y * m_speed.y*tnow*0.001);


	if (m_pos.x >= 300 || m_pos.x <= -300)
		m_dir.x *= -1;

	if (m_pos.y >= 300 || m_pos.y <= -300)
		m_dir.y *= -1;

}

void Rect::SetDir(Point dir)
{
	m_dir.x = dir.x;
	m_dir.y = dir.y;
}


Point Rect::GetPosition()
{
	return m_pos;
}

void Rect::CollideObject(Rect * obj)
{
	float col[2][4];
	col[0][0] = 1.0f; col[0][1] = 0.0f; col[0][2] = 0.0f; col[0][3] = 1.0f;
	col[1][0] = 1.0f; col[1][1] = 1.0f; col[1][2] = 1.0f; col[1][3] = 1.0f;

	
	/*if (m_pos.x - m_width <= obj->GetPosition().x
		&& obj->GetPosition().x <= m_pos.x + m_width) {

		if (m_pos.y + m_height <= obj->GetPosition().y - obj->GetHeight()) {
			m_dir.y *= -1;
			SetColor(&col[0][0]);
		}
		else if (m_pos.y - m_height <= obj->GetPosition().y + obj->GetHeight())
		{
			m_dir.y *= -1;
			SetColor(&col[0][0]);
		}
	}
	if (m_pos.y - m_height <= obj->GetPosition().y
		&& obj->GetPosition().y <= m_pos.y + m_height) {

		if (m_pos.y + m_height <= obj->GetPosition().y - obj->GetHeight()) {
			m_dir.x *= -1;
			SetColor(&col[0][0]);
		}
		else if (m_pos.x - m_height <= obj->GetPosition().y + obj->GetHeight()) {
			m_dir.x *= -1;
			SetColor(&col[0][0]);
		}
	}
	SetColor(&col[1][0]);*/
	if (m_pos.x - (2*m_width) <= obj->GetPosition().x && obj->GetPosition().x <= m_pos.x + (2 * m_width)
		&& m_pos.y - (2 * m_height) <= obj->GetPosition().y && obj->GetPosition().y <= m_pos.y + (2 * m_height)) {
		SetColor(&col[0][0]);
	}
	else
		SetColor(&col[1][0]);
}
