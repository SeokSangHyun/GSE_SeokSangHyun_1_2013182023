
#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_rRenderer = new Renderer{ WIN_WIDTH, WIN_HEIGHT };
	if (!m_rRenderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";

	m_sound = new Sound();
	m_iSoundNum = m_sound->CreateSound("./Dependencies/SoundSamples/Hotel California.mp3");
	m_sound->PlaySoundW(m_iSoundNum, true, 1.0f);

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
		m_rpCharObj[i] = new Rect;
	for (int i = 0; i < MAX_SHOTOBJECTCNT; ++i)
		m_spShotObj[i] = new Rect;


	//캐슬
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
		m_rpCharObj[i+3]->SetRect(WIN_WIDTH*0.25f*(i + 1) - WIN_WIDTH*0.5, WIN_HEIGHT*0.5 - 100, 100, 100,
			0, 0, 0, 0,
			0.0, 0.0, 1.0, 1, OBJ_BUILD_LIFE, OBJ_BUILDING, BlueTeam, 0.1);
		m_rpCharObj[i+3]->SetTextImage(m_rRenderer, "./Resource/building.png");
		m_rpCharObj[i+3]->SetCollideTextImgage(m_rRenderer, "./Resource/collide.png");
	}

	m_pBackground = new Rect;
	m_pBackground->SetRect(80,0, WIN_WIDTH*1.5, WIN_HEIGHT*20,
		0, 0, 0, 0, 1, 1, 1, 1, 0, non, 0, 0.5);
	m_pBackground->SetTextImage(m_rRenderer, "./Resource/background.png");
}

SceneMgr::~SceneMgr()
{}


void SceneMgr::RedCreate(float x, float y, float width, float height, int team)
{
	if (m_bCreate == true)
	{
		for (int i = 0; i < MAX_OBJECTCNT; ++i)
		{
			if (m_rpCharObj[i]->GetFlag() == false)
			{
				m_rpCharObj[i]->SetRect(x, y, width, height,
					rand() % OBJ_SPEED-(OBJ_SPEED/2), rand() % OBJ_SPEED+1 - (OBJ_SPEED / 2),
					(rand() % 100+1) * 0.01, (rand() % 100 + 1) * 0.01, 1, 0, 0, 1, OBJ_LIFE, OBJ_CHARACTER, RedTeam, 0.2);
				m_rpCharObj[i]->SetTextImage(m_rRenderer, "./Resource/char1.png");
				m_bCreate = false;
				m_rpCharObj[i]->SetAniCntDir(rand() % 4);
				return;
			}
		}
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

				switch (temp)
				{
				case OBJ_CHARACTER:
					state = OBJ_ARROW;
					if (m_rpCharObj[i]->GetTeam() == RedTeam) { color[0] = 0.5; color[1] = 0.2; color[2] = 0.7; }
					else if (m_rpCharObj[i]->GetTeam() == BlueTeam) { color[0] = 1.0; color[1] = 1.0; color[2] = 0.0; }
				case OBJ_BUILDING:
					state = OBJ_BULLET;
					if (m_rpCharObj[i]->GetTeam() == RedTeam) { color[0] = 1.0; color[1] = 0.0; color[2] = 0.0; }
					else if (m_rpCharObj[i]->GetTeam() == BlueTeam) { color[0] = 0.0; color[1] = 0.0; color[2] = 1.0; }
				default:
					break;
				}

				m_spShotObj[j]->SetRect(
					m_rpCharObj[i]->GetPosition().x, m_rpCharObj[i]->GetPosition().y,
					BULLETSIZE, BULLETSIZE,
					rand() % BULLET_SPEED - BULLET_SPEED*0.5, rand() % BULLET_SPEED - BULLET_SPEED*0.5,
					(rand() % 100 * 0.01 - 0.55), (rand() % 100 * 0.01 - 0.55),
					color[0], color[1], color[2], 1,
					OBJ_BULLET_LIFE, state, m_rpCharObj[i]->GetTeam(), 0.3 );
				if (m_spShotObj[j]->GetTeam() == RedTeam)	m_spShotObj[j]->SetTextImage(m_rRenderer, "./Resource/Particle.png");
				else m_spShotObj[j]->SetTextImage(m_rRenderer, "./Resource/Particle1.png");
				return;
			}
		}
	}
}




void SceneMgr::Update(float time)
{
	int count = 0;

	for(int i = 0 ; i < MAX_OBJECTCNT ; ++i)
	{
		if (m_rpCharObj[i]->GetFlag())
		{

			for (int j = 0; j < MAX_OBJECTCNT; ++j)
			{
				if (i != j && m_rpCharObj[j]->GetFlag()
					&& m_rpCharObj[i]->GetState() == OBJ_BUILDING
					&& m_rpCharObj[j]->GetState() == OBJ_CHARACTER)
				{
					if ( m_rpCharObj[i]->CollideObject(m_rpCharObj[j]) )
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
		m_fTestcol[i + 2][0] = rand()%100*0.01f;
		m_fTestcol[i + 2][1] = rand()%100*0.01f;
		m_fTestcol[i + 2][2] = rand()%100*0.01f;
		m_fTextpos[i + 2] = rand()%20;
	}
}


void SceneMgr::Render()
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

	for(int i = 0 ; i < 4 ; ++i)
		m_rRenderer->DrawText(WIN_WIDTH / 2 - (i-2)*20 - WIN_WIDTH/2, m_fTextpos[i],
			GLUT_BITMAP_TIMES_ROMAN_24, m_fTestcol[i][0], m_fTestcol[i][1], m_fTestcol[i][2], "AoA");
}


void SceneMgr::Timer(float time)
{
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
	if(BCoolTime(COOLMYCHAR, m_dCreateTime))
	{
		m_bCreate = true;
		m_dCreateTime = 0;
	}


}


bool SceneMgr::ShotCollide(int n)
{
	for (int j = 0; j < MAX_SHOTOBJECTCNT; ++j)
	{
		if (m_spShotObj[j]->GetFlag())
		{
			if (m_rpCharObj[n]->CollideObject(m_spShotObj[j]))
			{
				if (m_rpCharObj[n]->GetColFlag())
				{
					m_rpCharObj[n]->ReduceLife(OBJ_BULLET_LIFE);
					m_spShotObj[j]->Delete();
					return true;
				}
			}
		}
	}
	return false;
}


void SceneMgr::DelCheck()
{
	for (int i = 0; i < MAX_OBJECTCNT; ++i)
	{
		if(m_rpCharObj[i]->GetFlag() && m_rpCharObj[i]->GetLife() < 0)
			m_rpCharObj[i]->Delete();
	}
}


void SceneMgr::Release()
{
	delete[] m_rpCharObj;
	delete[] m_spShotObj;
	delete m_rRenderer;
}
