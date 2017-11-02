#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_rpObject				= new Rect[MAX_OBJECTSCOUNT];
	m_bpObject				= new Rect;
	m_bbpObject				= new Rect[100];
	m_iRectCount			= 0;
	m_iRectDelCount			= 0;
	m_iBulletCount			= 0;
	m_iBulletDelCount		= 0;

	m_rRenderer				= new Renderer{ 500, 500 };
	if (!m_rRenderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";

	m_bpObject->SetRect(0, 0, 200, 200,
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
	if (m_iBulletCount < 100) {
		m_bbpObject[m_iRectCount].SetRect(x, y, width, height,
			spdX, spdY, dirX, dirY,
			r, g, b, 0, 1, OBJ_BULLET);

		++m_iRectCount;
	}
	else if (m_iBulletCount > 0) {
		for (int i = 0; i < 100; ++i)
			if (m_bbpObject[i].GetFlag() == false) {
				m_bbpObject[i].SetRect(x, y, width, height,
					spdX, spdY, dirX, dirY,
					r, g, b, 0, 1, OBJ_BULLET);
				--m_iBulletDelCount;
			}
	}
}

void SceneMgr::Update(float time)
{
	int i;
//	Point dir;
	for (int i = 0; i < m_iRectCount; ++i) {
		Collide(i);
		m_bbpObject->AddPosition(time);
		/*m_bpObject->CollideObject(&m_rpObject[i]);
		if (m_bpObject->GetLife() <= 0)
			m_bpObject->Delete();*/
	}
			
	for (i = 0; i < m_iRectCount; ++i) {
		if (m_rpObject[i].GetFlag())
			m_rpObject[i].AddPosition(time);
	}
}

void SceneMgr::Render()
{
	for (int i = 0; i < m_iBulletCount; ++i) {
		m_bbpObject[i].Draw(m_rRenderer);
	}
	m_bpObject->Draw(m_rRenderer);
	
	for (int i = 0; i < m_iRectCount; ++i)
		if (m_rpObject[i].GetFlag()) {
			m_rpObject[i].Draw(m_rRenderer);
		}

}

void SceneMgr::Timer(float time)
{
	m_iReduceRate += (time*0.01);
	if (m_iReduceRate >= 5) {
		CreateBullet(0, 0, 20, 20, 300, 300,
			(rand() % 3 -3), (rand() % 3 -3),
			1.0, 0, 0, 0);
		m_iBulletCount++;
		m_iReduceRate = 0;
	}
}

void SceneMgr::Collide(int i)
{
	float col[2][4];
	col[0][0] = 1.0f; col[0][1] = 0.0f; col[0][2] = 0.0f; col[0][3] = 1.0f;
	col[1][0] = 1.0f; col[1][1] = 1.0f; col[1][2] = 1.0f; col[1][3] = 1.0f;

	for (int j = 0; j < m_iRectCount; ++j) {
		if (i != j && m_rpObject[i].GetFlag() == true
			&& m_rpObject[j].GetFlag() == true) {
			if (m_rpObject[i].CollideObject(&m_rpObject[j])) {
				m_rpObject[j].SetColor(col[0]);

				if (m_rpObject[i].GetLife() <= 0) {
					m_rpObject[i].Delete();
					++m_iRectDelCount;
				}
					
				return;
			}
			else {
				m_rpObject[i].SetColor(col[1]);
			}


		}
	}
}

void SceneMgr::Release()
{
	delete[]m_rpObject;
	delete m_rRenderer;
}
