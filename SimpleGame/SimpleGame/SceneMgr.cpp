#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_iRectCount = 0;
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Create(float x, float y, float width, float height, float r, float g, float b, float a)
{
	for (int i = 0; i < m_iRectCount; ++i) {
		m_rObject[i]->SetRect(x, y, width, height,
			r, g, b, 0);
		m_rObject[i]->SetSpDr(rand()%5, rand()%5, rand()%2-2, rand()%2-2);
	}
}

void SceneMgr::Update()
{
	for (int i = 0; i < m_iRectCount; ++i) {
		m_rObject[i]->AddPosition();
	}
}

void SceneMgr::Delete()
{
}
