
#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_SceCnt = 0;
	m_earthquake = false;
	g_iGameState = gamestate::logIn;
	m_num = 50;
	m_texdir = 1;
	stageNext = false;

	m_rRenderer = new Renderer{ WIN_WIDTH, WIN_HEIGHT };
	if (!m_rRenderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";
	tex_mouse = m_rRenderer->CreatePngTexture("./Resource/mouse.png");

	m_sound = new Sound();
	m_iBreak = new Sound();
	m_iCreate = new Sound();
	m_soundEnd = new Sound();
	if(rand()%2 == 0)
		m_iSoundNum = m_sound->CreateSound("./Dependencies/SoundSamples/DINOSAUR.mp3");
	else
		m_iSoundNum = m_sound->CreateSound("./Dependencies/SoundSamples/BABE.mp3");
	m_sound->PlaySoundW(m_iSoundNum, false, 1.0f);

	m_iBreakNum = m_iBreak->CreateSound("./Dependencies/SoundSamples/explosion.mp3");
	m_iCreateNum = m_iCreate->CreateSound("./Dependencies/SoundSamples/click.wav");
	m_soundEndNum = m_soundEnd->CreateSound("./Dependencies/SoundSamples/end.wav");

	for (int i = -2; i <= 2; ++i)
	{
		m_fTestcol[i + 2][0] = 1;
		m_fTestcol[i + 2][1] = 1;
		m_fTestcol[i + 2][2] = 1;
		m_fTextpos[i + 2] = WIN_WIDTH / 2;
	}


	m_bCreate = false;
	m_dBlueCreateTime = 0;
	m_dCreateTime = 0;


	//////
	for (int i = 0; i < MAX_OBJECTCNT; ++i)
		m_rpCharObj[i] = new Rect();
	for (int i = 0; i < MAX_SHOTOBJECTCNT; ++i)
		m_spShotObj[i] = new Rect();

	//캐슬

	m_pBackground = new Rect;
	m_pBackground->SetRect(0,0, WIN_WIDTH*1.25, WIN_WIDTH*1.55,
		0, 0, 0, 0, 1, 1, 1, 1, 0, non, 0, 0.6);
	m_pBackground->SetTextImage(m_rRenderer, "./Resource/background.png");

	m_sumTime = 0;
	whetherText = m_rRenderer->CreatePngTexture("./Resource/whether.png");
	//
	mou_pt = {0,0};
	g_alphaCnt = 1.00f;
	tex_logIn = m_rRenderer->CreatePngTexture("./Resource/logIn.png");
	tex_Name = m_rRenderer->CreatePngTexture("./Resource/GameName.png");
	tex_End = m_rRenderer->CreatePngTexture("./Resource/end.png");
}

SceneMgr::~SceneMgr()
{}


void SceneMgr::RedCreate(float x, float y, float width, float height, int team)
{
	switch (g_iGameState)
	{
	case gamestate::logIn:
		{
				stageNext = true;
		}
		break;
	case gamestate::inGame:
		{
			if (m_bCreate == true)
			{
				for (int i = 0; i < MAX_OBJECTCNT; ++i)
				{
					if (m_rpCharObj[i]->GetFlag() == false)
					{
						m_rpCharObj[i]->SetRect(x, y, width, height,
							rand() % OBJ_SPEED - (OBJ_SPEED / 2), rand() % OBJ_SPEED + 1 - (OBJ_SPEED / 2),
							(rand() % 100 + 1) * 0.01, (rand() % 100 + 1) * 0.01, 1, 0, 0, 1, OBJ_LIFE, OBJ_CHARACTER, RedTeam, 0.2);
						m_rpCharObj[i]->SetTextImage(m_rRenderer, "./Resource/char1.png");
						m_bCreate = false;
						m_rpCharObj[i]->SetAniCntDir(rand() % 4);
						m_iCreate->PlaySound(m_iCreateNum, false, 1.0f);
						return;
					}
				}
			}
		}
		break;
	case gamestate::end:
		{
			stageNext = false;
			g_alphaCnt = 1.0f;
			m_SceCnt = 0.0f;
			g_iGameState = gamestate::logIn;
		}
	break;
	}
}

void SceneMgr::BlueCreate()
{
	for (int i = 0; i < MAX_OBJECTCNT; ++i)
		if (m_rpCharObj[i]->GetFlag() == false)
		{
			m_rpCharObj[i]->SetRect(rand() % WIN_WIDTH - WIN_WIDTH*0.5, rand() % (int)(WIN_HEIGHT*0.5), RECTSIZE, RECTSIZE,
				rand() % OBJ_SPEED - OBJ_SPEED*0.5, rand() % OBJ_SPEED - OBJ_SPEED*0.5,
				(rand() % 100 * 0.01 - 0.55), (rand() % 100 * 0.01 - 0.55), 0, 0, 1, 1, OBJ_LIFE, OBJ_CHARACTER, BlueTeam, 0.2);
			m_rpCharObj[i]->SetTextImage(m_rRenderer, "./Resource/char2.png");
			m_rpCharObj[i]->SetAniCntDir(rand() % 4);
			m_iCreate->PlaySound(m_iCreateNum, false, 1.0f);
			return;
		}
}

void SceneMgr::CreateShoot(int i, float time)
{
	if(m_rpCharObj[i]->GetFlag() && m_rpCharObj[i]->Shot(COOLBULLET, time))
	{
		for (int j = 0; j < MAX_SHOTOBJECTCNT; ++j)
		{
			if (m_spShotObj[j]->GetFlag() == false)
			{
				int temp = m_rpCharObj[i]->GetState();
				float color[3];
				int state;
				char tex[30];
				float dir[2];
				int speed;

				switch (temp)
				{
				case OBJ_CHARACTER:
					state = OBJ_ARROW;
					dir[0] = rand()%100 * 0.01f - 0.55f;
					dir[1] = rand()%100 * 0.01f - 0.55f;
					speed = ARROW_SPEED;
					if (m_rpCharObj[i]->GetTeam() == RedTeam) { color[0] = 0.5; color[1] = 0.2; color[2] = 0.7; }
					else if (m_rpCharObj[i]->GetTeam() == BlueTeam) { color[0] = 1.0; color[1] = 1.0; color[2] = 0.0; }
					break;
				case OBJ_BUILDING:
					state = OBJ_BULLET;
					speed =BULLET_SPEED;
					dir[0] = (((rand() % WIN_WIDTH) * 3 / 5 - WIN_WIDTH / 2) - m_rpCharObj[i]->GetPosition()->x)*0.01f;
					dir[1] = (m_rpCharObj[i]->GetPosition()->y)*(-0.01f);
					if (m_rpCharObj[i]->GetTeam() == RedTeam) { color[0] = 1.0; color[1] = 0.0; color[2] = 0.0; }
					else if (m_rpCharObj[i]->GetTeam() == BlueTeam) { color[0] = 0.0; color[1] = 0.0; color[2] = 1.0; }
					break;
				default:
					break;
				}
		

				m_spShotObj[j]->SetRect(
					m_rpCharObj[i]->GetPosition()->x, m_rpCharObj[i]->GetPosition()->y,
					BULLETSIZE, BULLETSIZE,
					rand()%speed+50, rand() % speed+50,
					dir[0], dir[1],
					color[0], color[1], color[2], 1,
					OBJ_BULLET_LIFE, state, m_rpCharObj[i]->GetTeam(), m_rpCharObj[i]->GetLevel());
				if (state == OBJ_BULLET) {
					if (m_spShotObj[j]->GetTeam() == RedTeam)	m_spShotObj[j]->SetTextImage(m_rRenderer, "./Resource/Particle.png");
					else if (m_spShotObj[j]->GetTeam() == BlueTeam) m_spShotObj[j]->SetTextImage(m_rRenderer, "./Resource/Particle1.png");
				}
				return;
			}
		}
	}
}

void SceneMgr::KeyInput(const char k)
{
	switch (g_iGameState)
	{
	case gamestate::logIn:
	{
	}
	break;
	case gamestate::inGame:
	{
		if (k == 'r')
		{
			m_earthquake = true;
			for (int i = 0; i < MAX_OBJECTCNT; ++i)
			{
				if (m_rpCharObj[i]->GetState() != OBJ_BUILDING)
					m_rpCharObj[i]->Delete();
			}
			for (int i = 0; i < MAX_SHOTOBJECTCNT; ++i)
				m_spShotObj[i]->Delete();
		}
	}
	break;
	case gamestate::end:
	{
	}
	break;
	}
}




void SceneMgr::Update(float time)
{
	switch (g_iGameState)
	{
	case gamestate::logIn:
		{
			if (stageNext)
			{
				g_alphaCnt -= 0.01f;
				m_num += 5.f;
			}
		}
		break;
	case gamestate::inGame:
		{

			for (int i = 0; i < MAX_OBJECTCNT; ++i)
			{
				if (m_rpCharObj[i]->GetFlag())
				{

					for (int j = 0; j < MAX_OBJECTCNT; ++j)
					{
						if (i != j && m_rpCharObj[j]->GetFlag()
							&& m_rpCharObj[i]->GetState() == OBJ_BUILDING
							&& m_rpCharObj[j]->GetState() == OBJ_CHARACTER)
						{
							if (m_rpCharObj[i]->CollideObject(m_rpCharObj[j]))
							{
								if (m_rpCharObj[i]->GetColFlag()) {
									m_rpCharObj[i]->ReduceLife(m_rpCharObj[j]->GetLife());
									m_rpCharObj[j]->Delete();
									break;
								}
							}
						}
					}
					ShotCollide(i);
				}
				m_rpCharObj[i]->Update(time);
				m_rpCharObj[i]->SuperArmer(COOLSPARMER, time);
			}

			for (int i = 0; i < MAX_OBJECTCNT; ++i)
			{
				m_spShotObj[i]->Update(time);
			}
			//체력 0 미만시 삭제
			DelCheck();
			//
			for (int i = -2; i <= 2; ++i)
			{
				m_fTestcol[i + 2][0] = rand() % 100 * 0.01f;
				m_fTestcol[i + 2][1] = rand() % 100 * 0.01f;
				m_fTestcol[i + 2][2] = rand() % 100 * 0.01f;
				m_fTextpos[i + 2] = rand() % 20;
			}
			//
			int teamCount[2] = { 0,0 };
			for (int i = 0; i < 6; ++i)
			{
				if (m_rpCharObj[i]->GetState() == OBJ_BUILDING) {
					if (m_rpCharObj[i]->GetTeam() == RedTeam)
						teamCount[0]++;
					if (m_rpCharObj[i]->GetTeam() == BlueTeam)
						teamCount[1]++;
				}
			}
			if (teamCount[0] == 0 || teamCount[1] == 0) {
				m_soundEnd->PlaySound(m_soundEndNum, false, 1.0f);
				m_num = 50.f;
				g_iGameState = gamestate::end;
			}
			//
		}
		break;
	case gamestate::end:
		{
			m_num += m_texdir;
		}
		break;
	}
}


void SceneMgr::Render()
{
	switch (g_iGameState)
	{
	case gamestate::logIn:
		{
			m_rRenderer->DrawTexturedRectXY(0,0,0, WIN_WIDTH*1.25, WIN_WIDTH*1.55
				, 1,1,1, g_alphaCnt, tex_logIn, 0.2);
			m_rRenderer->DrawTexturedRectXY(0, m_num, 0, 280, 300
				, 1, 1, 1, g_alphaCnt, tex_Name, 0.1);
		}
		break;
	case gamestate::inGame:
		{
			m_pBackground->DrawImg(m_rRenderer);
			for (int i = 0; i < MAX_OBJECTCNT; ++i)
		{
			m_rpCharObj[i]->Draw(m_rRenderer);
			m_rpCharObj[i]->DrawImg(m_rRenderer);
			m_rpCharObj[i]->DrawAnimation(m_rRenderer);
		}
			//
			for (int i = 0; i < MAX_SHOTOBJECTCNT; ++i)
		{
			m_spShotObj[i]->Draw(m_rRenderer);
		}

			for (int i = 0; i < 4; ++i)
				m_rRenderer->DrawText(WIN_WIDTH / 2 - (i - 2) * 20 - WIN_WIDTH / 2, m_fTextpos[i],
					GLUT_BITMAP_TIMES_ROMAN_24, m_fTestcol[i][0], m_fTestcol[i][1], m_fTestcol[i][2], "AoA");
			m_rRenderer->DrawParticleClimate(0, 0, 0, 5, 1, 1, 1, 1,
				-0.1, -0.1, whetherText, m_sumTime, 0.02);
			if(m_earthquake == true)
				m_rRenderer->SetSceneTransform(rand()%20, rand()%20, 1, 1);
			else
				m_rRenderer->SetSceneTransform(0, 0, 1, 1);
		}
		break;
	case gamestate::end:
		{
			m_rRenderer->DrawTexturedRectXY(0, m_num, 0, 280, 300
				, 1, 1, 1, g_alphaCnt, tex_End, 0.1);
		}
		break;
	}
	m_rRenderer->DrawParticle(mou_pt.x, mou_pt.y, 0, 10, 1, 1, 1, 1,
		0, 0, tex_mouse, m_sumTime, 0.01);
}


void SceneMgr::Timer(float time)
{
	switch (g_iGameState)
	{
	case gamestate::logIn:
		{
			if (stageNext == true)
			{

				if (g_alphaCnt <= 0.05f)
				{
					stageNext = false;
					g_alphaCnt = 1.0f;
					for (int i = 0; i < 3; ++i)
					{
						m_rpCharObj[i]->SetRect(WIN_WIDTH*0.25f*(i + 1) - WIN_WIDTH*0.5, -WIN_HEIGHT*0.5 + 100, 100, 100,
							0, 0, 0, 0,
							1.0, 0.0, 0.0, 1, OBJ_BUILD_LIFE, OBJ_BUILDING, RedTeam, 0.1);
						m_rpCharObj[i]->SetTextImage(m_rRenderer, "./Resource/building1.png");
						m_rpCharObj[i]->SetCollideTextImgage(m_rRenderer, "./Resource/collide.png");
					}
					for (int i = 0; i < 3; ++i)
					{
						m_rpCharObj[i + 3]->SetRect(WIN_WIDTH*0.25f*(i + 1) - WIN_WIDTH*0.5, WIN_HEIGHT*0.5 - 100, 100, 100,
							0, 0, 0, 0,
							0.0, 0.0, 1.0, 1, OBJ_BUILD_LIFE, OBJ_BUILDING, BlueTeam, 0.1);
						m_rpCharObj[i + 3]->SetTextImage(m_rRenderer, "./Resource/building.png");
						m_rpCharObj[i + 3]->SetCollideTextImgage(m_rRenderer, "./Resource/collide.png");
					}
					g_iGameState = gamestate::inGame;

				}
			}
			else
			{
				m_num = rand() % 10 + 50;
			}
		}
		break;
	case gamestate::inGame:
		{
			m_sumTime += time*0.001;
			for (int i = 0; i < MAX_OBJECTCNT; ++i)
			{
				CreateShoot(i, time);
			}
			//적 플레이어 생성
			m_dBlueCreateTime += time * 0.001f;
			if (BCoolTime(COOLCHAR, m_dBlueCreateTime))
			{
				BlueCreate();
				m_dBlueCreateTime = 0;
			}
			//마우스 
			m_dCreateTime += time*0.001f;
			if (BCoolTime(COOLMYCHAR, m_dCreateTime))
			{
				m_bCreate = true;
				m_dCreateTime = 0;
			}
			if (m_earthquake == true)
			{
				m_earthTimer += time*0.001f;
				if (BCoolTime(4, m_earthTimer))
				{
					m_earthTimer = 0;
					m_earthquake = false;
				}
			}
		}
		break;
	case gamestate::end:
		m_SceCnt += time*0.001;
		g_alphaCnt = rand() % 100*0.01f;
		if (m_num > 100.f)
			m_texdir *= -1;
		else if(m_num < 0.f)
			m_texdir *= -1;
		
		if (BCoolTime(10, m_SceCnt)) {
			g_alphaCnt = 1.0f;
			m_SceCnt = 0.0f;
			g_iGameState = gamestate::logIn;
		}
		break;
	}
}


bool SceneMgr::ShotCollide(int n)
{
	for (int j = 0; j < MAX_SHOTOBJECTCNT; ++j)
	{
		if (m_spShotObj[j]->GetFlag() && m_rpCharObj[n]->GetColFlag()==false)
		{
			if (m_rpCharObj[n]->CollideObject(m_spShotObj[j]))
			{
				m_rpCharObj[n]->ReduceLife(OBJ_BULLET_LIFE);
				m_spShotObj[j]->Delete();
				return true;
			}
		}
	}
	return false;
}


void SceneMgr::DelCheck()
{
	for (int i = 0; i < MAX_OBJECTCNT; ++i)
	{
		if (m_rpCharObj[i]->GetFlag() && m_rpCharObj[i]->GetLife() < 0)
		{
			if(m_rpCharObj[i]->GetState() == OBJ_BUILDING)
				m_iBreak->PlaySound(m_iBreakNum, false, 1.0f);
			m_rpCharObj[i]->Delete();
		}
	}
}


void SceneMgr::Release()
{
	delete[] m_rpCharObj;
	delete[] m_spShotObj;
	delete m_rRenderer;
}
