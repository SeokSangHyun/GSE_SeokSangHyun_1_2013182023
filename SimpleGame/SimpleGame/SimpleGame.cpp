/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"
#include <random>


using namespace std;

SceneMgr *g_manager;
DWORD st = 0, ed;

float temp_time = 0;
bool mouse_click = false;
POINT move_pt = { 0,0 };


void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	g_manager->Render();
	glutSwapBuffers();
}

/////////////////////////////////////
void Update(float time)
{
	g_manager->Update(time);
	g_manager->Timer(time);
}
/////////////////////////////////////

void Idle(void)
{
	ed = timeGetTime() - st;
	st = timeGetTime();

	Update((float)ed);
	RenderScene();

}

void MouseInput(int button, int state, int x, int y)
{
	if ((button ==  GLUT_LEFT_BUTTON))
	{
		//
		if (state == GLUT_DOWN)
		{
				mouse_click = true;
		}
		else if (state == GLUT_UP && mouse_click == true
			&& y > WIN_HEIGHT*0.5) {
			std::cout << x << ", " << y << std::endl;
			std::cout << x - (WIN_WIDTH*0.5) << ", " << (WIN_HEIGHT*0.5) - y << std::endl;
			
			g_manager->RedCreate(x - (WIN_WIDTH*0.5), (WIN_HEIGHT*0.5) - y,
				RECTSIZE, RECTSIZE, BlueTeam);
		}
		//

	}
	RenderScene();
}
void MouseMove(int x, int y)
{
	g_manager->mou_pt.x = x - (WIN_WIDTH*0.5);
	g_manager->mou_pt.y = (WIN_HEIGHT*0.5) - y;
}



void KeyInput(unsigned char key, int x, int y)
{
	g_manager->KeyInput(key);
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

void TimerFunc(int timer)
{
}


int main(int argc, char **argv)
{
	// Initialize GL things
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
		std::cout << " GLEW Version is 3.0\n ";
	else
		std::cout << "GLEW 3.0 not supported\n ";


	g_manager = new SceneMgr;
	
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutPassiveMotionFunc(MouseMove);
	glutSpecialFunc(SpecialKeyInput);

	glutTimerFunc(500, TimerFunc, 1);
	glutMainLoop();


	g_manager->Release();
    return 0;
}

