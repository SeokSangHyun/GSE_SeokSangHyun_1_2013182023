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

bool mouse_click = false;


void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);


	g_manager->Render();
	glutSwapBuffers();
}

/////////////////////////////////////
void Update(float time)
{
	g_manager->Update(time);
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
		if (state == GLUT_DOWN) {
			mouse_click = true;
		}
		else if (state == GLUT_UP && mouse_click == true) {
			
			g_manager->Create(x - (WIN_WIDTH*0.5), (WIN_HEIGHT*0.5) - y,
				RECTSIZE, RECTSIZE,
				rand() % OBJ_SPEED, rand() % OBJ_SPEED,
				rand() % 2 - 2, rand() % 2 - 2,
				1,1,1,0);

			mouse_click = false;
		}
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	/*if (key == GLUT_KEY_RIGHT) {
		dir.x -= -1;
		dir.y = 0;
	}
	if (key == GLUT_KEY_LEFT) {
		dir.x -= 1;
		dir.y = 0;
	}
	if (key == GLUT_KEY_UP)
	{
		dir.x = 0;
		dir.y -= -1;
	}
	if (key == GLUT_KEY_DOWN) {
		dir.x = 0;
		dir.y -= 1;
	}*/

	RenderScene();
}

void TimerFunc(int timer)
{
	//rect.AddPosition(pt, dir);
}


int main(int argc, char **argv)
{

	// Initialize GL things
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
	glutSpecialFunc(SpecialKeyInput);

	glutTimerFunc(1000, TimerFunc, 1);
	glutMainLoop();


	g_manager->Release();
    return 0;
}

