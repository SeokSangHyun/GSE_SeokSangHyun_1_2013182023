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

#include "Renderer.h"
#include "Object.h"
#include <random>

#define RECTSIZE 20

using namespace std;

Renderer *g_Renderer = NULL;

Point dir{1, 0};
Point pt{ 2, 2 };
Rect rect(0, 0, 50, 50, 1, 0, 1, 1);
bool mouse_click = false;

int rectCount = 0;
Rect bufRect[100];

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_Renderer->DrawSolidRect(
		rect.GetPosition().x, rect.GetPosition().y, 0,
		rect.GetWidth(),
		rect.GetColor()[0],
		rect.GetColor()[1],
		rect.GetColor()[2],
		rect.GetColor()[3]
	);


	for (int i = 0; i < rectCount; ++i) {
		g_Renderer->DrawSolidRect(
			bufRect[i].GetPosition().x, bufRect[i].GetPosition().y, 0,
			bufRect[i].GetWidth(),
			bufRect[i].GetColor()[0],
			bufRect[i].GetColor()[1],
			bufRect[i].GetColor()[2],
			bufRect[i].GetColor()[3]
		);
		bufRect[i].AddPosition(pt, dir);
	}
	glutSwapBuffers();
}

void Idle(void)
{

	rect.AddPosition(pt, dir);
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
			rectCount++;
			
			bufRect->SetRect(rand()%400-200, rand() % 400-200, RECTSIZE, RECTSIZE,
				rand()%100*0.01, rand() % 100 * 0.01, rand() % 100 * 0.01, 0);

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
	if (key == GLUT_KEY_RIGHT) {
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
	}

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
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	
	glutTimerFunc(1000, TimerFunc, 1);
	glutMainLoop();

	delete g_Renderer;

    return 0;
}

