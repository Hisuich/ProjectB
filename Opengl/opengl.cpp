#include <stdlib.h>
#include <glew.h>
#include <freeglut.h>

#include "Core/OpenGLApp.h"

bool exiting = false;
long windowHeight = 600;
long windowWidth = 800;
long windowBits = 32;
bool fullscreen = false;

OpenGLApp *g_glRender = new OpenGLApp();

double oldStartingTime = 0;
double newStartingTime;
float dt = 0.1f;

void Render()
{
	//newStartingTime = glutGet(GLUT_ELAPSED_TIME);
	//dt = (newStartingTime - oldStartingTime)/100;
	//oldStartingTime = newStartingTime;
	g_glRender->Update(dt);
	g_glRender->Render();
	glutPostRedisplay();
	
}

void Update(float delta)
{
	g_glRender->Update(delta);
}

void KeyboardFunction(unsigned char key, int x, int y)
{
	g_glRender->KeyboardInputFunction(key, x, y);
}

void KeyboardFunctionRelease(unsigned char key, int x, int y)
{
	g_glRender->KeyboardInputFunctionRelease(key, x, y);
}

void reshape(int width, int height)
{
	g_glRender->SetupProject(width, height);
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(windowWidth, windowHeight);
	

	glutCreateWindow("MAZAFAKA NIGGA");
	g_glRender->SetupProject(windowWidth, windowHeight);

	glutSetKeyRepeat(1);
	glutKeyboardFunc(KeyboardFunction);
	glutKeyboardUpFunc(KeyboardFunctionRelease);

	glutDisplayFunc(Render);
	glutReshapeFunc(reshape);

	

	glutMainLoop();

	return 1;
}
