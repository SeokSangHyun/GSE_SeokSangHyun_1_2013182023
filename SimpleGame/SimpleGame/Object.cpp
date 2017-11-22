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

	m_team			= non;
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
	m_coolTime		= 0;

	if (m_state == OBJ_CHARACTER)
	{
		m_shotObj = new ShootObj[MAX_ARROW];
		for (int i = 0; i < MAX_ARROW; ++i)
		{
			m_shotObj[i].dir = { 0,0 };
			m_shotObj[i].flag = false;
			m_shotObj[i].speed = { 0,0 };
			m_shotObj[i].state = OBJ_ARROW;
						
			m_shotObj[i].color[0] = m_color[0];
			m_shotObj[i].color[1] = m_color[1];
			m_shotObj[i].color[2] = m_color[2];
			m_shotObj[i].color[3] = m_color[3];
		}
	}
	else if (m_state == OBJ_BUILDING)
	{
		m_shotObj = new ShootObj[MAX_BULLETCOUNT];
		for (int i = 0; i < MAX_BULLETCOUNT; ++i)
		{
			m_shotObj[i].dir = { 0,0 };
			m_shotObj[i].flag = false;
			m_shotObj[i].speed = { 0,0 };
			m_shotObj[i].state = OBJ_BULLET;
						
			m_shotObj[i].color[0] = m_color[0];
			m_shotObj[i].color[1] = m_color[1];
			m_shotObj[i].color[2] = m_color[2];
			m_shotObj[i].color[3] = m_color[3];
		}
	}
}

Rect::~Rect()
{}


void Rect::SetShotObj(int type, float r, float g, float b,
	float cooltime, float time)
{
	int type_num;
	if (m_state == OBJ_CHARACTER)		type_num = MAX_ARROW;
	else if (m_state == OBJ_BUILDING)	type_num = MAX_BULLETCOUNT;

	actTime += (time*0.001f);
	for (int i = 0; i < type_num; ++i)
	{
		if (BCoolTime(cooltime, actTime) && m_shotObj[i].flag == false)
		{
			m_shotObj[i].pt.x = m_pos.x;
			m_shotObj[i].pt.y = m_pos.y;
			m_shotObj[i].speed.x = rand() % 100 + 200;
			m_shotObj[i].speed.y = rand() % 100 + 200;
			m_shotObj[i].dir.x = ((rand() % 100 + 1)* 0.01) - 0.5;
			m_shotObj[i].dir.y = ((rand() % 100 + 1)* 0.01) - 0.5;
			m_shotObj[i].state = type;
			m_shotObj[i].flag = true;

			m_shotObj[i].color[0] = r;
			m_shotObj[i].color[1] = g;
			m_shotObj[i].color[2] = b;
			m_shotObj[i].color[3] = m_color[3];
			actTime = rand()%10 *0.1;
			return;
		}
	}
}

void Rect::SetTextImage(Renderer *renderer, char *name)
{
	m_texCharacter = renderer->CreatePngTexture(name);
}

void Rect::SetRect(float x, float y, float width, float height,
	float spdX, float spdY, float dirX, float dirY,
	float r, float g, float b, float a, int life, int type, int team)
{
	m_pos.x			= x;
	m_pos.y			= y;
	m_width			= width;
	m_height		= height;

	m_team			= team;
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
	m_coolTime		= 0;
}



void Rect::Draw(Renderer * renderer)
{
	int type_num;
	if (m_state == OBJ_CHARACTER)	type_num = MAX_ARROW;
	else if (m_state == OBJ_BUILDING)	type_num = MAX_BULLETCOUNT;

	renderer->DrawSolidRect(m_pos.x, m_pos.y, 0,
		m_width,
		m_color[0], m_color[1], m_color[2], m_color[3]);

	for (int i = 0; i < type_num; ++i)
	{
		if (m_shotObj[i].flag)
		{
			renderer->DrawSolidRect(m_shotObj[i].pt.x, m_shotObj[i].pt.y, 0,
				BULLETSIZE, m_shotObj[i].color[0], m_shotObj[i].color[1],
				m_shotObj[i].color[2], m_shotObj[i].color[3]);
		}
	}
}

void Rect::DrawImg(Renderer * renderer)
{
	renderer->DrawTexturedRect(m_pos.x, m_pos.y, 0, m_width,
		m_color[0], m_color[1], m_color[2], m_color[3], m_texCharacter);
}

bool Rect::CollideObject(Rect * col)
{
	if ((m_pos.x - (m_width*0.5) <= col->GetPosition().x
		&& col->GetPosition().x  <= m_pos.x + (m_width*0.5)) &&
		(m_pos.y - (m_height*0.5) <= col->GetPosition().y
		&& col->GetPosition().y <= m_pos.y + (m_height*0.5)))
	{
		return true;
	}
	return false;
}

bool Rect::CollideShotObject(Point * col)
{
	if ((m_pos.x - (m_width*0.5) <= col->x
		&& col->x <= m_pos.x + (m_width*0.5)) &&
		(m_pos.y - (m_height*0.5) <= col->y
			&& col->y <= m_pos.y + (m_height*0.5)))
	{
		return true;
	}
	return false;
}

void Rect::AddPosition(float tnow)
{
	if (m_flag == true)
	{
		m_pos.x += (m_dir.x * m_speed.x*tnow*0.001);
		m_pos.y += (m_dir.y * m_speed.y*tnow*0.001);


		if (m_pos.x >= WIN_WIDTH*0.5 || m_pos.x <= -WIN_WIDTH*0.5)
			m_dir.x *= -1;

		if (m_pos.y >= WIN_HEIGHT*0.5 || m_pos.y <= -WIN_HEIGHT*0.5)
			m_dir.y *= -1;
	}

}

void Rect::AddShotObjPosition(float tnow)
{
	if (m_flag == true)
	{
		int type_num;
		if (m_state == OBJ_CHARACTER)		type_num = MAX_ARROW;
		else if (m_state == OBJ_BUILDING)	type_num = MAX_BULLETCOUNT;

		for (int i = 0; i < type_num; ++i)
		{
			if (m_shotObj[i].flag)
			{
				m_shotObj[i].pt.x += (m_shotObj[i].dir.x * m_shotObj[i].speed.x*tnow*0.001);
				m_shotObj[i].pt.y += (m_shotObj[i].dir.y * m_shotObj[i].speed.y*tnow*0.001);

				if (m_shotObj[i].pt.x >= WIN_WIDTH*0.5 || m_shotObj[i].pt.x <= -WIN_WIDTH*0.5)
					m_shotObj[i].dir.x *= -1;

				if (m_shotObj[i].pt.y >= WIN_HEIGHT*0.5 || m_shotObj[i].pt.y <= -WIN_HEIGHT*0.5)
					m_shotObj[i].dir.y *= -1;
			}
		}
	}
}

void Rect::SuperArmer(float cooltime, float time)
{
	m_coolTime += (time*0.001f);
	if (BCoolTime(cooltime, m_coolTime))
		SetColFlagFalse();
}


Point Rect::GetPosition()
{
	return m_pos;
}


void Rect::Delete()
{
	int type_num;
	if (m_state == OBJ_CHARACTER)		type_num = MAX_ARROW;
	else if (m_state == OBJ_BUILDING)	type_num = MAX_BULLETCOUNT;

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
	for (int i = 0; i < type_num; ++i)
	{
		m_shotObj[i].pt = { WIN_WIDTH + 100, WIN_HEIGHT + 100 };
		m_shotObj[i].dir = { 0,0 };
		m_shotObj[i].flag = false;
		m_shotObj[i].speed = { 0,0 };
		m_shotObj[i].state = OBJ_ARROW;
	}
}

void Rect::DeleteShotObj(int n)
{
	m_shotObj[n].pt = { WIN_WIDTH + 100, WIN_HEIGHT + 100 };
	m_shotObj[n].dir = { 0,0 };
	m_shotObj[n].flag = false;
	m_shotObj[n].speed = { 0,0 };
	m_shotObj[n].state = OBJ_ARROW;
}

void Rect::Update(float time)
{
	//플레이어 업데이트
	if (m_state == OBJ_CHARACTER)
	{
		AddPosition(time);
		AddShotObjPosition(time);
	}
	//화살 업데이트
	else if (m_state == OBJ_BUILDING)
	{
		AddShotObjPosition(time);
	}
}
