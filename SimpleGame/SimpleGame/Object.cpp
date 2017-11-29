#include "stdafx.h"
#include "Object.h"


Rect::Rect()
{
	m_flag = false;
	m_state = non;
}


Rect::~Rect()
{}

void Rect::SetRect(float x, float y, float width, float height,
	float spdX, float spdY, float dirX, float dirY,
	float r, float g, float b, float a, int life, int state, int team, float level)
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

	m_team = team;
	m_iLifeTime = life;

	m_state = state;
	actTime = 0;
	m_coolTime = 0;

	m_colFlag = false;
	m_flag = true;
	m_level = level;
}


void Rect::SetTextImage(Renderer *renderer, char *name)
{
	m_texImg = renderer->CreatePngTexture(name);
}


void Rect::Draw(Renderer * renderer)
{
	//
	if (m_flag == true) {
		if (m_state != OBJ_BUILDING)
			renderer->DrawSolidRect(m_pos.x, m_pos.y, 0, m_width,
				m_color[0], m_color[1], m_color[2], m_color[3], m_level);

		if (m_state == OBJ_BUILDING || m_state == OBJ_CHARACTER) {
			double num = CalGauge();
			renderer->DrawSolidRectGauge(m_pos.x, m_pos.y + m_height*0.8, 0, m_width, GaugeHeight,
				m_color[0], m_color[1], m_color[2], m_color[3], num, m_level);
		}
	}
	//
}

void Rect::DrawImg(Renderer * renderer)
{
	if (m_flag == true)
	{
		renderer->DrawTexturedRect(m_pos.x, m_pos.y, 0, m_width,
			m_color[0], m_color[1], m_color[2], m_color[3],
			m_texImg, m_level);

	}
}


bool Rect::CollideObject(Rect * col)
{
	if ((m_colFlag == false) && (m_team != col->GetTeam()))
	{ 
		if ((m_pos.x - (m_width*0.5) <= col->GetPosition().x && col->GetPosition().x <= m_pos.x + (m_width*0.5)) &&
			(m_pos.y - (m_height*0.5) <= col->GetPosition().y && col->GetPosition().y <= m_pos.y + (m_height*0.5)))
		{
			SetColFlagTrue();
			col->SetColFlagTrue();
			return true;
		}
		else
			return false;
	}
}


bool Rect::Shot(float cooltime, float time)
{
	actTime += (time*0.001f);
	if (BCoolTime(cooltime, actTime))
	{
		actTime = rand() % 5 * 0.1;
		return true;
	}
	return false;
}

void Rect::AddPosition(float tnow)
{
	m_pos.x += (m_dir.x*m_speed.x*(tnow*0.001));
	m_pos.y += (m_dir.y*m_speed.y*(tnow*0.001));

	if (m_state == OBJ_CHARACTER)
	{
		if (m_pos.x >= WIN_WIDTH*0.5 || m_pos.x <= -WIN_WIDTH*0.5)
			m_dir.x *= -1;
		if (m_pos.y >= WIN_HEIGHT*0.5 || m_pos.y <= -WIN_HEIGHT*0.5)
			m_dir.y *= -1;
	}
	else if (m_state == OBJ_ARROW || m_state == OBJ_BULLET)
	{
		if (m_pos.x >= WIN_WIDTH*0.5 || m_pos.x <= -WIN_WIDTH*0.5)
			Delete();
		else if (m_pos.y >= WIN_HEIGHT*0.5 || m_pos.y <= -WIN_HEIGHT*0.5)
			Delete();
	}
}



void Rect::SuperArmer(float cooltime, float time)
{
	if (m_colFlag == true)
	{
		m_coolTime += (time*0.001f);
		if (BCoolTime(cooltime, m_coolTime))
		{
			SetColFlagFalse();
			m_coolTime = 0;
		}
	}
}


double Rect::CalGauge()
{
	int num;
	if (m_state == OBJ_CHARACTER)	num = OBJ_LIFE;
	else if (m_state == OBJ_BUILDING)	num = OBJ_BUILD_LIFE;

	return (double)m_iLifeTime/ (double)num;
}


Point Rect::GetPosition()
{
	return m_pos;
}

void Rect::Delete()
{
	m_pos.x = WIN_WIDTH + 500;	m_pos.y = WIN_HEIGHT +500;
	m_flag = false;
	m_colFlag = false;
	m_iLifeTime = 0;
	actTime = 0;
}


void Rect::Update(float time)
{
	if(m_flag)
		AddPosition(time);
}
