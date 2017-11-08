#include "stdafx.h"
#include "Object.h"


Rect::Rect()
{
}

Rect::Rect(float x, float y, float width, float height,
	float spdX, float spdY, int dirX, int dirY,
	float r, float g, float b, float a, float life)
{
	m_pos.x			= x;
	m_pos.y			= y;
	m_width			= width;
	m_height		= height;

	m_speed.x		= spdX;
	m_speed.y		= spdY;
	m_dir.x			= dirX;
	m_dir.y			= dirY;

	m_color[0]		= r;
	m_color[1]		= g;
	m_color[2]		= b;
	m_color[3]		= a;

	m_colFlag		= false;
	m_flag			= true;
	m_iLifeTime		= life;
	m_state = OBJ_CHARACTER;
}


Rect::~Rect()
{
}

void Rect::SetRect(float x, float y, float width, float height,
	float spdX, float spdY, int dirX, int dirY,
	float r, float g, float b, float a, float life, int type)
{
	m_pos.x			= x;
	m_pos.y			= y;
	m_width			= width;
	m_height		= height;

	m_speed.x		= spdX;
	m_speed.y		= spdY;
	m_dir.x			= dirX;
	m_dir.y			= dirY;

	m_color[0]		= r;
	m_color[1]		= g;
	m_color[2]		= b;
	m_color[3]		= a;

	m_colFlag		= false;
	m_flag			= true;
	m_iLifeTime		= life;
	m_state			= type;
}


void Rect::Draw(Renderer * renderer)
{
	renderer->DrawSolidRect(m_pos.x, m_pos.y, 0,
		m_width,
		m_color[0], m_color[1], m_color[2], m_color[3]);
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

bool Rect::CollideObject(Rect * obj)
{
	if (m_pos.x - (2*m_width) <= obj->GetPosition().x && obj->GetPosition().x <= m_pos.x + (2 * m_width)
		&& m_pos.y - (2 * m_height) <= obj->GetPosition().y && obj->GetPosition().y <= m_pos.y + (2 * m_height)) {
		if (m_colFlag == false) {
			ReduceLife(1);
		}
		SetColFlagTrue();
		return true;
	}
	else {
		SetColFlagFalse();
		return false;
	}

}

void Rect::Delete()
{
	m_pos.x	= WIN_WIDTH+100;	m_pos.y	= WIN_HEIGHT+100;
	m_width	= 0;				m_height = 0;
	m_speed.x = 0;				m_speed.y = 0;
	m_dir.x	= 0;				m_dir.y	= 0;
	m_color[0]	= 0; m_color[1]	= 0; m_color[2]	= 0; m_color[3]	= 0;
	m_flag	= false;
	m_iLifeTime= 0;
}

void Rect::Update(float time)
{
	AddPosition(time);
}
