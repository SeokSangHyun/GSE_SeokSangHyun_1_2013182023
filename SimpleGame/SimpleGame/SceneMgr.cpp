#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_rpObject = new Rect[MAX_OBJECTSCOUNT];
	m_iRectCount = 0;

	m_rRenderer = new Renderer{ 500, 500 };
	if (!m_rRenderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Create(float x, float y, float width, float height,
	float spdX, float spdY, int dirX, int dirY, float r, float g, float b, float a)
{
		m_rpObject[m_iRectCount].SetRect(x, y, width, height,
			spdX, spdY, dirX, dirY,
			r, g, b, 0);

		if(m_iRectCount < MAX_OBJECTSCOUNT)
			m_iRectCount++;
}

void SceneMgr::Update(float time)
{
	int i;
	Point dir;
	for (i = 0; i < m_iRectCount; ++i) {
		dir = m_rpObject[i].GetDir();
		for (int j = i+1; j < m_iRectCount; ++j) {
			m_rpObject[i].CollideObject(&m_rpObject[j]);
		}
		m_rpObject[i].AddPosition(time);
	}

}

void SceneMgr::Render()
{
	for (int i = 0; i < m_iRectCount; ++i)
		m_rRenderer->DrawSolidRect(m_rpObject[i].GetPosition().x, m_rpObject[i].GetPosition().y, 0,
			m_rpObject[i].GetWidth(),
			m_rpObject[i].GetColor()[0], m_rpObject[i].GetColor()[1],
			m_rpObject[i].GetColor()[2], m_rpObject[i].GetColor()[3]
			);
}

void SceneMgr::Timer()
{


}

void SceneMgr::Release()
{
	delete m_rRenderer;
}
