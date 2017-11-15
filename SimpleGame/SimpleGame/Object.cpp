#include "stdafx.h"
#include "Object.h"


Rect::Rect()
{}

Rect::Rect(float x, float y, float width, float height,
	float spdX, float spdY, float dirX, float dirY,
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
	m_flag			= false;
	m_iLifeTime		= life;
	m_state			= type;
	actTime			= 0;

	for (int i = 0; i < MAX_ARROW; ++i)
	{
		m_arrow[i].dir = {0,0};
		m_arrow[i].flag = false;
		m_arrow[i].speed = {0,0};
		m_arrow[i].state = OBJ_ARROW;
	}
}

Rect::~Rect()
{}


void Rect::SetArrow(int type, float time)
{
	if (m_state == OBJ_CHARACTER)
	{
		for (int i = 0; i < MAX_ARROW; ++i)
		{
			actTime += (time*0.001f);

			if (actTime > 6 && m_arrow[i].flag == false)
			{
				m_arrow[i].pt.x = m_pos.x;
				m_arrow[i].pt.y = m_pos.y;
				m_arrow[i].speed.x = rand() % 100+200;
				m_arrow[i].speed.y = rand() % 100+200;
				m_arrow[i].dir.x = ((rand() % 100 + 1)* 0.01) - 0.5;
				m_arrow[i].dir.y = ((rand() % 100 + 1)* 0.01) - 0.5;
				m_arrow[i].state = type;
				m_arrow[i].flag = true;

				actTime = 0;
				return;
			}
		}
	}
}

void Rect::SetRect(float x, float y, float width, float height,
	float spdX, float spdY, float dirX, float dirY,
	float r, float g, float b, float a, int life, int type)
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
	//화살 그리기
	if (m_state == OBJ_CHARACTER)
	{
		for (int i = 0; i < MAX_ARROW; ++i)
		{
			if (m_arrow[i].flag)
			{
				renderer->DrawSolidRect(m_arrow[i].pt.x, m_arrow[i].pt.y, 0,
					BULLETSIZE, 1, 1, 0, 1);
			}
		}
	}
}

void Rect::AddPosition(float tnow)
{
	m_pos.x += (m_dir.x * m_speed.x*tnow*0.001);
	m_pos.y += (m_dir.y * m_speed.y*tnow*0.001);


	if (m_pos.x >= 250 || m_pos.x <= -250)
		m_dir.x *= -1;

	if (m_pos.y >= 250 || m_pos.y <= -250)
		m_dir.y *= -1;

}

void Rect::AddArrowPosition(float tnow)
{
	for (int i = 0; i < MAX_ARROW; ++i)
	{
		if (m_arrow[i].flag)
		{
			m_arrow[i].pt.x += (m_arrow[i].dir.x * m_arrow[i].speed.x*tnow*0.001);
			m_arrow[i].pt.y += (m_arrow[i].dir.y * m_arrow[i].speed.y*tnow*0.001);

			if (m_arrow[i].pt.x >= 250 || m_arrow[i].pt.x <= -250)
				m_arrow[i].dir.x *= -1;

			if (m_arrow[i].pt.y >= 250 || m_arrow[i].pt.y <= -250)
				m_arrow[i].dir.y *= -1;
		}
	}
}

void Rect::SuperArmer(float time)
{
	if (time > 2)
		SetColFlagFalse();
}



Point Rect::GetPosition()
{
	return m_pos;
}


void Rect::Delete()
{
	m_pos.x	= WIN_WIDTH+100;	m_pos.y	= WIN_HEIGHT+100;
	m_width	= 0;				m_height = 0;
	m_speed.x = 0;				m_speed.y = 0;
	m_dir.x	= 0;				m_dir.y	= 0;
	m_color[0]	= 0; m_color[1]	= 0; m_color[2]	= 0; m_color[3]	= 1;
	m_flag	= false;
	m_colFlag = false;
	m_iLifeTime= 0;
	actTime = 0;
	//
	for (int i = 0; i < MAX_ARROW; ++i)
	{
		m_arrow[i].pt = { WIN_WIDTH + 100, WIN_HEIGHT + 100 };
		m_arrow[i].dir = { 0,0 };
		m_arrow[i].flag = false;
		m_arrow[i].speed = { 0,0 };
		m_arrow[i].state = OBJ_ARROW;
	}
}

void Rect::DeleteArrow(int n)
{
	m_arrow[n].pt = { WIN_WIDTH + 100, WIN_HEIGHT + 100 };
	m_arrow[n].dir = { 0,0 };
	m_arrow[n].flag = false;
	m_arrow[n].speed = { 0,0 };
	m_arrow[n].state = OBJ_ARROW;
}

void Rect::Update(float time)
{
	//플레이어 업데이트
	AddPosition(time);
	
	//화살 업데이트
	if(m_state == OBJ_CHARACTER)
		AddArrowPosition(time);
}
