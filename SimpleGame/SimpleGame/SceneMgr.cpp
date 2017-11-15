#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_rpObject = new Rect[MAX_OBJECTSCOUNT]{ Rect(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) };
	m_bpObject = new Rect[MAX_BULLETCOUNT]{ Rect(0,0,0,0,  0,0,0,0,  0,0,0,0,0,0) };

	m_cpObject = new Rect;
	m_cpObject->SetRect(0, 0, 80, 80, 0, 0, 0, 0,
		0.0, 1.0, 1.0, 1, 500, OBJ_BUILDING);

	col[0][0] = 1.0f; col[0][1] = 0.0f; col[0][2] = 0.0f; col[0][3] = 1.0f;
	col[1][0] = 1.0f; col[1][1] = 1.0f; col[1][2] = 1.0f; col[1][3] = 1.0f;

	m_iRectCount			= 0;
	m_iRectDelCount			= 0;

	m_iBulletCount			= 0;
	m_iBulletDelCount		= 0;

	m_iArrowCount			= 0;
	m_iArrowDelCount		= 0;

	m_rRenderer				= new Renderer{ 500, 500 };
	if (!m_rRenderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";
}

SceneMgr::~SceneMgr()
{}

void SceneMgr::Create(float x, float y, float width, float height)
{
	if (m_iRectCount < MAX_OBJECTSCOUNT)
	{
		if (m_rpObject[m_iRectCount].GetFlag() == false) {
			m_rpObject[m_iRectCount].SetRect(x, y, width, height,
				rand() % OBJ_SPEED, rand() % OBJ_SPEED,
				(rand() % 2 - 2), (rand() % 2 - 2), 1, 1, 1, 1, OBJ_LIFE, OBJ_CHARACTER);
			m_iRectCount++;
		}
	}
	else if (m_iRectDelCount > 0)
	{
		for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
			if (m_rpObject[i].GetFlag() == false) {
				m_rpObject[i].SetRect(x, y, width, height,
					rand() % OBJ_SPEED, rand() % OBJ_SPEED,
					(rand() % 2 - 2), (rand() % 2 - 2), 1, 1, 1, 1, OBJ_LIFE, OBJ_CHARACTER);
				return;
			}
	}
}

void SceneMgr::CreateShoot()
{
	if (m_iBulletCount < MAX_BULLETCOUNT)
	{
		m_bpObject[m_iBulletCount].SetRect(0, 0, 10, 10, 300, 300,
			((rand() % 100 + 1)* 0.01) - 0.5, ((rand() % 100 + 1)*0.01) - 0.5,
			1, 0, 0, 1, 1, OBJ_BULLET);
		m_iBulletCount++;
	}
	else if (m_iBulletDelCount>0)
	{
		for (int i = 0; i < MAX_BULLETCOUNT; ++i)
		{
			if (m_bpObject[i].GetFlag()==false) {
				m_bpObject[i].SetRect(0, 0, 10, 10, 300, 300,
					((rand() % 100 + 1)* 0.01) - 0.5, ((rand() % 100 + 1)*0.01) - 0.5,
					1, 0, 0, 1, 1, OBJ_BULLET);
				m_iBulletDelCount--;
				return;
			}
		}
	}
}

void SceneMgr::CreateArrow(int i, float time)
{
	m_rpObject[i].SetArrow(OBJ_ARROW + i, time);
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
	for (int i = 0 ; i < MAX_OBJECTSCOUNT; ++i)
	{
		//플레이어
		for (int j = 0 ; j < MAX_OBJECTSCOUNT; ++j)
		{
			if (m_rpObject[i].GetFlag() && m_rpObject[i].GetFlag()
				&& i!=j && m_rpObject[i].GetColFlag() == false)
			{
				if (Collide(&m_rpObject[i], &m_rpObject[j]))
				{
					m_rpObject[i].SetColFlagTrue();
					m_rpObject[i].ReduceLife(1);
				}
			}
		}
		
		//총알
		for (int j = 0; j < MAX_BULLETCOUNT; ++j)
		{
			if ( m_bpObject[j].GetFlag() )
			{
				if (Collide(&m_rpObject[i], &m_bpObject[j]))
				{
					m_rpObject[i].ReduceLife(5);
					m_bpObject[j].Delete();
					m_iBulletDelCount++;
				}
			}
		}
		//화살
		CollideArrow(i);
		//캐슬
		if (m_rpObject[i].GetFlag())
		{
			if (Collide(m_cpObject, &m_rpObject[i])
				&& m_cpObject->GetColFlag() == false) {
				m_cpObject->SetColFlagTrue();
				m_cpObject->ReduceLife(m_rpObject[i].GetLife());
			}
		}


		//슈퍼아머 체크
		m_rpObject[i].SuperArmer(time);
		m_cpObject->SuperArmer(time);


		//업데이트
		if (m_rpObject[i].GetLife() < 0)
		{
			m_rpObject[i].Delete();
			m_iRectDelCount++;
		}
		m_rpObject[i].Update(time);
	}

	for (int i = 0; i < MAX_BULLETCOUNT; ++i)
	{
		if (m_bpObject[i].GetFlag()) {
			m_bpObject[i].Update(time);
			count++;
		}
	}
	
	if (m_cpObject->GetFlag() && m_cpObject->GetLife() < 0)
		m_cpObject->Delete();
}


void SceneMgr::Render()
{
	//불릿
	for (int i = 0; i < MAX_BULLETCOUNT; ++i)
	{
		if (m_bpObject[i].GetFlag())
		{
			m_bpObject[i].Draw(m_rRenderer);
		}
	}

	//플레이어
	for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
	{
		if (m_rpObject[i].GetFlag())
		{
			m_rpObject[i].Draw(m_rRenderer);
		}
	}
	//캐슬
	if (m_cpObject->GetFlag()) 
	{
		m_cpObject->Draw(m_rRenderer);
	}
}


void SceneMgr::Timer(float time)
{
	m_iReduceRate += (time*0.001);
	if (m_iReduceRate > 5) {
		CreateShoot();
		m_iReduceRate = 0;
	}

	//화살생성
	for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
		CreateArrow(i, time);

}



bool SceneMgr::Collide(Rect * temp, Rect * col)
{
	if (temp->GetPosition().x - temp->GetWidth() < col->GetPosition().x
		&& col->GetPosition().x < temp->GetPosition().x + temp->GetWidth())
	{
		if (temp->GetPosition().y - temp->GetHeight() < col->GetPosition().y
			&& col->GetPosition().y < temp->GetPosition().y + temp->GetHeight())
		{
			return true;
		}
		return false;
	}

	return false;
}

void SceneMgr::CollideArrow(int i)
{
	for (int j = 0; j < MAX_OBJECTSCOUNT; ++j)
	{
		if (i != j && m_rpObject[i].GetFlag() && m_rpObject[j].GetFlag())
		{
			for (int a = 0; a < MAX_ARROW; ++a)
			{
				if (m_rpObject[j].GetPosition().x - m_rpObject[j].GetWidth() <= m_rpObject[i].GetArrow(a)->pt.x
					&& m_rpObject[i].GetArrow(a)->pt.x <= m_rpObject[j].GetPosition().x + m_rpObject[j].GetWidth()
					&& m_rpObject[j].GetPosition().y - m_rpObject[j].GetHeight() <= m_rpObject[i].GetArrow(a)->pt.y
					&& m_rpObject[i].GetArrow(a)->pt.y <= m_rpObject[j].GetPosition().y + m_rpObject[j].GetHeight())
				{
					m_rpObject[j].ReduceLife(10);
					m_rpObject[i].DeleteArrow(a);
				}
			}
		}
	}
}



void SceneMgr::Release()
{
	delete[]m_rpObject;
	delete[]m_bpObject;
	delete m_cpObject;
	delete m_rRenderer;
}
