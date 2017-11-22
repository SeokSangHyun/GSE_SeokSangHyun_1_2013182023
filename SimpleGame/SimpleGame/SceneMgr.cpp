#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	col[0][0] = 1.0f; col[0][1] = 0.0f; col[0][2] = 0.0f; col[0][3] = 1.0f;
	col[1][0] = 1.0f; col[1][1] = 1.0f; col[1][2] = 1.0f; col[1][3] = 1.0f;
	m_bCreate = false;
	m_dBlueCreateTime = 0;
	m_dCreateTime = 0;
	m_rRenderer				= new Renderer{ WIN_WIDTH, WIN_HEIGHT };
	if (!m_rRenderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";

	//////

	//플레이어
	for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
	{
		m_rpRedObject[i] = new Rect( 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_CHARACTER);
		m_rpBlueObject[i] = new Rect(0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, OBJ_CHARACTER);
	}

	//캐슬
	for (int i = 0; i < 3; ++i) {
		m_cpRedObject[i] = new Rect{ Rect(0,0,0,0,  0,0,0,0,  0,0,0,0,0,OBJ_BUILDING) };
		m_cpRedObject[i]->SetRect(WIN_WIDTH*0.25f*(i + 1) - WIN_WIDTH*0.5, -WIN_HEIGHT*0.5 + 100, 100, 100,
			0, 0, 0, 0, 1.0, 0.0, 0.0, 1, 500, OBJ_BUILDING, RedTeam);
		m_cpRedObject[i]->SetTextImage(m_rRenderer, "./Img/building1.png");

		m_cpBlueObject[i] = new Rect{ Rect(0,0,0,0,  0,0,0,0,  0,0,0,0,0,OBJ_BUILDING) };
		m_cpBlueObject[i]->SetRect(WIN_WIDTH*0.25f*(i + 1) - WIN_WIDTH*0.5, WIN_HEIGHT*0.5 - 100, 100, 100,
			0, 0, 0, 0, 0.0, 0.0, 1.0, 1, 500, OBJ_BUILDING, BlueTeam);
		m_cpBlueObject[i]->SetTextImage(m_rRenderer, "./Img/building.png");
	}
}

SceneMgr::~SceneMgr()
{}

void SceneMgr::RedCreate(float x, float y, float width, float height, int team)
{
	if (m_bCreate == true)
	{
		for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
			if (m_rpRedObject[i]->GetFlag() == false)
			{
				m_rpRedObject[i]->SetRect(x, y, width, height,
					rand() % OBJ_SPEED - OBJ_SPEED*0.5, rand() % OBJ_SPEED - OBJ_SPEED*0.5,
					(rand() % 2 - 2), (rand() % 2 - 2), 1, 0, 0, 1, OBJ_LIFE, OBJ_CHARACTER, RedTeam);
				m_bCreate = false;
				return;
			}
	}
}

void SceneMgr::BlueCreate()
{
	for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
		if (m_rpBlueObject[i]->GetFlag() == false)
		{
			m_rpBlueObject[i]->SetRect(rand()%WIN_WIDTH - WIN_WIDTH*0.5, rand() % (int)(WIN_HEIGHT*0.5), RECTSIZE, RECTSIZE,
				rand() % OBJ_SPEED - OBJ_SPEED*0.5, rand() % OBJ_SPEED - OBJ_SPEED*0.5,
				(rand() % 2 - 2), (rand() % 2 - 2), 0, 0, 1, 1, OBJ_LIFE, OBJ_CHARACTER, BlueTeam);
			return;
		}
}

void SceneMgr::CreateShoot(int i, float time)
{
	if (m_cpRedObject[i]->GetFlag() == true)
		m_cpRedObject[i]->SetShotObj(OBJ_BULLET,1, 0, 0, COOLBULLET, time);
	if (m_cpBlueObject[i]->GetFlag() == true)
		m_cpBlueObject[i]->SetShotObj(OBJ_BULLET, 0, 0, 1, COOLBULLET, time);
}

void SceneMgr::CreateArrow(int i, float time)
{
	if(m_rpRedObject[i]->GetFlag() == true)
		m_rpRedObject[i]->SetShotObj(OBJ_ARROW, 0.5, 0.2, 0.7, COOLARROW, time);

	if (m_rpBlueObject[i]->GetFlag() == true)
		m_rpBlueObject[i]->SetShotObj(OBJ_ARROW, 1, 1, 0, COOLARROW, time);
}



void SceneMgr::Update(float time)
{
	int count = 0;

	/*
		player -> player	충돌체크
		castle -> plqy		충돌체크
		play   -> arrow		충돌체크
		play   -> bullet	충돌체크
	*/
	//플레이어
	for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
	{

		for (int j = 0; j < MAX_OBJECTSCOUNT; ++j)
		{
			if (m_rpRedObject[i]->GetFlag() == true
				&& m_rpBlueObject[j]->GetFlag() == true)
			{
				//플레이어
				if (m_rpRedObject[i]->GetColFlag() == false
					&& Collide(m_rpRedObject[i], m_rpBlueObject[j]))
				{
					m_rpRedObject[i]->ReduceLife(10);
					m_rpBlueObject[j]->ReduceLife(10);
				}
				//화살
				if (m_rpRedObject[i]->GetColFlag() == false
					&& CollideShotObj(m_rpRedObject[i], m_rpBlueObject[j]))
				{
					m_rpRedObject[i]->ReduceLife(10);
				}
				if (m_rpBlueObject[i]->GetColFlag() == false
					&& CollideShotObj(m_rpBlueObject[i], m_rpRedObject[j]))
				{
					m_rpBlueObject[j]->ReduceLife(10);
				}

			}
		}

		
		for (int j = 0; j < 3; ++j)
		{
			if (m_rpRedObject[i]->GetFlag() == true
				&& m_cpBlueObject[j]->GetFlag() == true)
			{
				//캐슬
				if (m_cpBlueObject[j]->GetColFlag() == false
					&& Collide(m_rpRedObject[i], m_cpBlueObject[j]))
				{
					m_cpBlueObject[j]->ReduceLife(m_rpRedObject[i]->GetLife());
					m_rpRedObject[i]->Delete();
				}
				//화살
				if (CollideShotObj(m_cpBlueObject[j], m_rpRedObject[i]))
				{
					m_cpRedObject[j]->ReduceLife(5);
				}
			}

			//
			if (m_rpBlueObject[i]->GetFlag() == true
				&& m_cpRedObject[j]->GetFlag() == true)
			{
				//캐슬
				if (m_cpRedObject[j]->GetColFlag() == false
					&& Collide(m_rpBlueObject[i], m_cpRedObject[j]))
				{
					m_cpRedObject[j]->ReduceLife(m_rpBlueObject[i]->GetLife());
					m_rpBlueObject[i]->Delete();
				}
				if (CollideShotObj(m_cpRedObject[j], m_rpBlueObject[i]))
				{
					m_cpRedObject[j]->ReduceLife(5);
				}
			}
		}

		//플레이어 이동
		if (m_rpRedObject[i]->GetFlag() == true)
		{
			m_rpRedObject[i]->Update(time);
			if (m_rpRedObject[i]->GetLife() <= 0)
				m_rpRedObject[i]->Delete();
		}
		if (m_rpBlueObject[i]->GetFlag() == true)
		{
			m_rpBlueObject[i]->Update(time);
			if (m_rpBlueObject[i]->GetLife() <= 0)
				m_rpBlueObject[i]->Delete();
		}
	}


	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (m_cpRedObject[i]->GetFlag() == true
				&& m_cpBlueObject[j]->GetFlag() == true)
			{
				if (CollideShotObj(m_cpRedObject[i], m_cpBlueObject[j]))
					m_cpRedObject[i]->ReduceLife(10);
				if(CollideShotObj(m_cpBlueObject[i], m_cpRedObject[j]))
					m_cpBlueObject[i]->ReduceLife(10);
			}
		}
		m_cpRedObject[i]->Update(time);
		m_cpBlueObject[i]->Update(time);
		if (m_cpRedObject[i]->GetLife() <= 0)
			m_cpRedObject[i]->Delete();
		if (m_cpBlueObject[i]->GetLife() <= 0)
			m_cpBlueObject[i]->Delete();
	}

}


void SceneMgr::Render()
{
	//플레이어
	for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
	{
		if (m_rpRedObject[i]->GetFlag()==true)
		{
			m_rpRedObject[i]->Draw(m_rRenderer);
		}
		if (m_rpBlueObject[i]->GetFlag() == true && m_rpBlueObject[i]->GetColFlag() != true)
		{
			m_rpBlueObject[i]->Draw(m_rRenderer);
		}
	}
	//캐슬
	for (int i = 0; i < 3; ++i)
	{
		if (m_cpRedObject[i]->GetFlag()==true)
		{					
			m_cpRedObject[i]->Draw(m_rRenderer);
			m_cpRedObject[i]->DrawImg(m_rRenderer);
		}
		if (m_cpBlueObject[i]->GetFlag()==true)
		{					 
			m_cpBlueObject[i]->Draw(m_rRenderer);
			m_cpBlueObject[i]->DrawImg(m_rRenderer);
		}
	}
}


void SceneMgr::Timer(float time)
{
	for (int i = 0; i < 3; ++i)
	{
		CreateShoot(i, time);
		m_cpRedObject[i]->SuperArmer(2, time);
		m_cpBlueObject[i]->SuperArmer(2, time);
	}

	//화살생성 & obj 슈퍼아머
	for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
	{
		CreateArrow(i, time);
		m_rpRedObject[i]->SuperArmer(2, time);
		m_rpBlueObject[i]->SuperArmer(2, time);
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



bool SceneMgr::Collide(Rect * temp, Rect * col)
{
	if (temp->CollideObject(col))
	{
		temp->SetColFlagTrue();
		col->SetColFlagTrue();
		return true;
	}
	return false;
}

bool SceneMgr::CollideShotObj(Rect * temp, Rect * col)
{
	int type_num;
	if (col->GetState() == OBJ_CHARACTER)		type_num = MAX_ARROW;
	else if (col->GetState() == OBJ_BUILDING)	type_num = MAX_BULLETCOUNT;
	
	for (int i = 0; i < type_num; ++i) {
		if (col->GetShotFlag(i) && temp->CollideShotObject(&col->GetShotPosition(i)))
		{
			temp->SetColFlagTrue();
			col->DeleteShotObj(i);
			return true;
		}
	}
	return false;
}


void SceneMgr::Release()
{
	delete[]m_rpRedObject;
	delete[] m_cpRedObject;
	delete[] m_cpBlueObject;
	delete m_rRenderer;
}
