#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_rpObject				= new Rect[MAX_OBJECTSCOUNT];
	m_cpObject				= new Rect;
	m_bpObject				= new Rect[100];
	m_iRectCount			= 0;
	m_iRectDelCount			= 0;
	m_iBulletCount			= 0;
	m_iBulletDelCount		= 0;

	m_rRenderer				= new Renderer{ 500, 500 };
	if (!m_rRenderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";

	m_cpObject->SetRect(0, 0, 50, 50,
		0, 0, 0, 0,
		1.0, 1.0, 0.0, 0, 100, OBJ_CHARACTER);
}

SceneMgr::~SceneMgr()
{}

void SceneMgr::Create(float x, float y, float width, float height,
	float spdX, float spdY, int dirX, int dirY, float r, float g, float b, float a)
{

	if (m_iRectCount < MAX_OBJECTSCOUNT) {
		m_rpObject[m_iRectCount].SetRect(x, y, width, height,
			spdX, spdY, dirX, dirY,
			r, g, b, 0, OBJ_LIFE, OBJ_CHARACTER);

		++m_iRectCount;
	}
	else if (m_iRectDelCount > 0) {
		for (int i = 0; i < MAX_OBJECTSCOUNT; ++i)
			if (m_rpObject[i].GetFlag() == false) {
				m_rpObject[i].SetRect(x, y, width, height,
					spdX, spdY, dirX, dirY,
					r, g, b, 0, OBJ_LIFE, OBJ_CHARACTER);
				--m_iRectDelCount;
			}
	}
}

void SceneMgr::CreateBullet(float x, float y, float width, float height, float spdX, float spdY, int dirX, int dirY, float r, float g, float b, float a)
{
	if (m_iBulletCount < MAX_BULLETCOUNT) {
		m_bpObject[m_iBulletCount].SetRect(x, y, width, height,
			spdX, spdY, dirX, dirY,
			r, g, b, 0, 1, OBJ_BULLET);

		++m_iBulletCount;
	}
	else if (m_iBulletCount > 0) {
		for (int i = 0; i < MAX_BULLETCOUNT; ++i)
			if (m_bpObject[i].GetFlag() == false) {
				m_bpObject[i].SetRect(x, y, width, height,
					spdX, spdY, dirX, dirY,
					r, g, b, 0, 1, OBJ_BULLET);
				--m_iBulletDelCount;
			}
	}
}

void SceneMgr::Update(float time)
{
	std::cout << m_cpObject->GetLife() << std::endl;
//	std::cout << m_cpObject->GetLife() << std::endl;

	for (int i = 0; i < m_iBulletCount; ++i)
		m_bpObject[i].Update(time);
			
	for (int i = 0; i < m_iRectCount; ++i) {
		if (m_rpObject[i].GetFlag()) {
			CollidePBtwP(i);
			CollidePBtwB(i);
			CollidePBtwC(i);
			m_rpObject[i].Update(time);
		}
	}
}

void SceneMgr::Render()
{
	for (int i = 0; i < m_iBulletCount; ++i) {
		if(m_bpObject[i].GetFlag())
			m_bpObject[i].Draw(m_rRenderer);
	}
	if (m_cpObject->GetFlag())
		m_cpObject->Draw(m_rRenderer);
	
	for (int i = 0; i < m_iRectCount; ++i)
		if (m_rpObject[i].GetFlag()) {
			m_rpObject[i].Draw(m_rRenderer);
		}

}

void SceneMgr::Timer(float time)
{
	m_iReduceRate += (double)(time*0.001);
	if (m_iReduceRate >= 5) {
		CreateBullet(0, 0, 10, 10, 300, 300,
			(rand() % 3 -3), (rand() % 3 -3),
			1.0, 0, 0, 0);
		++m_iBulletCount;
		m_iReduceRate = 0;
	}
}

void SceneMgr::CollidePBtwP(int i)
{
	float col[2][4];
	col[0][0] = 1.0f; col[0][1] = 0.0f; col[0][2] = 0.0f; col[0][3] = 1.0f;
	col[1][0] = 1.0f; col[1][1] = 1.0f; col[1][2] = 1.0f; col[1][3] = 1.0f;

	for (int j = 0; j < m_iRectCount; ++j)
	{
		if (i != j && m_rpObject[j].GetFlag() == true
			&& m_rpObject[i].CollideObject(&m_rpObject[j]))
		{
			m_rpObject[i].SetColor(col[0]);
			if (m_rpObject[i].GetLife() <= 0) {
				m_rpObject[i].Delete();
				++m_iRectDelCount;
			}
			return;
		}
		else
		{
			m_rpObject[i].SetColor(col[1]);
		}


	}
}

void SceneMgr::CollidePBtwB(int i)
{
	for (int j = 0; j < m_iBulletCount; ++j)
	{
		if (i != j && m_bpObject[j].GetFlag() == true
			&& m_bpObject[i].CollideObject(&m_bpObject[j]))
		{
			m_rpObject[i].ReduceLife(5);
			m_iBulletDelCount++;
			m_bpObject->Delete();
			if (m_rpObject[i].GetLife() <= 0) {
				m_rpObject[i].Delete();
				++m_iRectDelCount;
			}
			return;
		}
	}
}

void SceneMgr::CollidePBtwC(int i)
{
		if (m_rpObject[i].GetFlag() == true
			&& m_rpObject[i].CollideObject(m_cpObject))
		{
			m_iRectDelCount++;
			m_rpObject->Delete();
			m_cpObject->ReduceLife(5);
			if (m_cpObject->GetLife() <= 0)
			{
				m_cpObject->Delete();
			}
			return;
		}
	
}


void SceneMgr::Release()
{
	delete[]m_rpObject;
	delete[]m_bpObject;
	delete m_cpObject;
	delete m_rRenderer;
}
