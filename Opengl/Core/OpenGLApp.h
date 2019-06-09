#ifndef OPEN_GL_APP
#define OPEN_GL_APP

#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>

#include <glew.h>
#include <freeglut.h>

#include "../Logic/EventProcessor.h"
#include "../Objects/Teleport.h"
#include "PointXYZ.h"
#include "../Logic/Observer.h"
#include "../Objects/ID.h"

class Player;
class Map;
class Zone;

struct BitmapStruct {
public:
	GLint xPos;
	GLint yPos;
};

class OpenGLApp {
public:
	int m_windowHeight = 600;
	int m_windowWidth = 800;

	bool shutdown = false;

	Player* player = nullptr;
	PointXYZ playerPosition;
	

public:
	EventProcessor* eventProcessor;
	Map* currentMap = nullptr;
	Zone* zone = nullptr;

public:

	OpenGLApp();
	virtual ~OpenGLApp();

	bool Init();
	bool Shutdown();

	void SetupProject(int width, int height);

	void KeyboardInputFunction(unsigned char key, int x, int y);	
	void KeyboardInputFunctionRelease(unsigned char key, int x, int y);

	void Update(float dt);
	void Render();

	void ChangeMap(Map* nextMap, int x, int y);
	void showText(string text);

};

#endif
