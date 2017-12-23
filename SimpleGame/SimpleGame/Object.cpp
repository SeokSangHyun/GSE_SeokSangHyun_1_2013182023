#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"


Rect::Rect()
{
	spin_pos = {0, 0};
	radian = 0.0f;
	back_pos = {5.0f, 5.0f};
	back_excel = {0.2f, 0.2f};

	m_pos =		{0.f,0.f};
	m_dir =		{0.f,0.f};
	m_speed =	{0.f,0.f};

	sumTime = 0;
	m_flag = false;
	m_state = non;
	m_AniCnt[0] = 0;
	m_AniTime = 0.0f;
	m_colAni = 0;

	m_texImg = NULL;
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
	radian = 0.0f;
	if (m_state == OBJ_ARROW)
	{
		spin_pos = {0,0};
		m_aiNum = rand() % 2;
	}
}


void Rect::SetTextImage(Renderer *renderer, char *name)
{
	if(m_texImg == NULL)
		m_texImg = renderer->CreatePngTexture(name);
}

void Rect::SetCollideTextImgage(Renderer * renderer, char * name)
{
	m_colTextImg = renderer->CreatePngTexture(name);
}


void Rect::SetAniCntDir(int aniDir)
{
	m_AniCnt[1] = aniDir;
}


void Rect::Draw(Renderer * renderer)
{
	//
	if (m_flag == true) {
		if (m_state == OBJ_ARROW)
		{
			if(m_aiNum == Ai::normal)
				renderer->DrawSolidRect(m_pos.x, m_pos.y, 0, m_width,
					m_color[0], m_color[1], m_color[2], m_color[3], m_level);
			else if (m_aiNum == Ai::spin)
				renderer->DrawSolidRect(m_pos.x +spin_pos.x, m_pos.y+ spin_pos.y, 0, m_width,
					m_color[0], m_color[1], m_color[2], m_color[3], m_level);
		}
		if (m_state == OBJ_BUILDING || m_state == OBJ_CHARACTER) {
			double num = CalGauge();
			renderer->DrawSolidRectGauge(m_pos.x, m_pos.y + m_height*0.8, 0, m_width, GaugeHeight,
				m_color[0], m_color[1], m_color[2], m_color[3], num, m_level);
		}
		if (m_state == OBJ_BULLET) {

			renderer->DrawParticle(m_pos.x, m_pos.y, 0, m_width, 1,1,1,1,
				-m_dir.x, -m_dir.y, m_texImg, sumTime, m_level);
		}
	}
	//
}

void Rect::DrawImg(Renderer * renderer)
{
	if (m_flag && m_state != OBJ_CHARACTER)
	{
		renderer->DrawTexturedRectXY(m_pos.x, m_pos.y, 0, m_width, m_height,
			m_color[0], m_color[1], m_color[2], m_color[3],
			m_texImg, m_level);

	}
}

void Rect::DrawAnimation(Renderer * renderer)
{
	if(m_state == OBJ_CHARACTER)
		renderer->DrawTexturedRectSeq(m_pos.x, m_pos.y, 0, m_width,
			1,1,1,1, m_texImg, m_AniCnt[0], m_AniCnt[1],3,4, m_level);
	else if (m_state == OBJ_BUILDING && m_colFlag)
		renderer->DrawTexturedRectSeq(m_pos.x, m_pos.y, 0, m_width,
			1, 1, 1, 1, m_colTextImg, m_colAni, 0, 9, 1, m_level);
}


bool Rect::CollideObject(Rect * col)
{
	if ((m_colFlag == false) && (m_team != col->GetTeam()))
	{ 
		if ((m_pos.x - (m_width*0.5) <= col->GetPosition()->x && col->GetPosition()->x <= m_pos.x + (m_width*0.5)) &&
			(m_pos.y - (m_height*0.5) <= col->GetPosition()->y && col->GetPosition()->y <= m_pos.y + (m_height*0.5)))
		{
			if (m_state == OBJ_CHARACTER && col->GetState() == OBJ_BULLET)
			{
				back_excel = {col->GetDir().x, col->GetDir().y};
				back_pos = { rand() % 10 + 15.f, rand() % 10 + 15.f };
			}
			SetColFlagTrue();
			col->SetColFlagTrue();
			return true;
		}
	}
	return false;
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

	if (m_state == OBJ_CHARACTER)
	{
		if (m_pos.x >= WIN_WIDTH*0.5f)
		{
			m_AniCnt[1] = LEFT;
			m_pos.x = WIN_WIDTH*0.5 - 2.f;
			m_dir.x *= -1;
		}
		else if (m_pos.x <= -WIN_WIDTH*0.5)
		{
			m_AniCnt[1] = RIGHT;
			m_pos.x = 2 - WIN_WIDTH*0.5;
			m_dir.x *= -1;
		}

		if (m_pos.y >= WIN_HEIGHT*0.5)
		{
			m_AniCnt[1] = DOWN;
			m_pos.y = WIN_HEIGHT*0.5 - 2;
			m_dir.y *= -1;
		}
		else if (m_pos.y <= -WIN_HEIGHT*0.5)
		{
			m_AniCnt[1] = UP;
			m_pos.y = 2 - WIN_HEIGHT*0.5;
			m_dir.y *= -1;
		}
	}
	else if (m_state == OBJ_ARROW || m_state == OBJ_BULLET)
	{
		if (m_pos.x >= WIN_WIDTH*0.5 || m_pos.x <= -WIN_WIDTH*0.5)
			Delete();
		else if (m_pos.y >= WIN_HEIGHT*0.5 || m_pos.y <= -WIN_HEIGHT*0.5)
			Delete();
	}

	if (m_state == OBJ_ARROW && m_aiNum == Ai::spin)
	{
		radian += 0.5f;
		spin_pos.x = cos(radian)*m_width;
		spin_pos.y = sin(radian)*m_height;
	}

	if (m_colFlag == false)
	{
		m_pos.x += (m_dir.x*m_speed.x*(tnow*0.001f));
		m_pos.y += (m_dir.y*m_speed.y*(tnow*0.001f));
	}
	else if (m_colFlag == true && m_state == OBJ_CHARACTER)
	{
		m_pos.x += (back_excel.x*back_pos.x*(tnow*0.001));
		m_pos.y += (back_excel.y*back_pos.y*(tnow*0.001));
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


Point* Rect::GetPosition()
{
	return &m_pos;
}

void Rect::Delete()
{
	m_flag = false;
	m_colFlag = false;
	m_iLifeTime = 0;
	actTime = 0;
	m_texImg = NULL;
}


void Rect::Update(float time)
{
	if (m_flag) {
		sumTime += time*0.001;
		AddPosition(time);
		m_AniCnt[0] = (m_AniCnt[0] + 1) % 3;

		if(m_colFlag && m_state == OBJ_BUILDING)
			m_colAni = (m_colAni + 1) % 9;

	}
}


void Rect::Release(void)
{
	sumTime = 0;
	m_flag = false;
	m_state = non;
	m_AniCnt[0] = 0;
	m_AniTime = 0.0f;
	m_colAni = 0;
}