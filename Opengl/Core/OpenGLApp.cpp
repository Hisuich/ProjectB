#include "OpenGLApp.h"

#include "../Objects/Player.h"
#include "../Objects/Zone.h"
#include "../Objects/GlobalState.h"

OpenGLApp::OpenGLApp()
{
	Init();
}

OpenGLApp::~OpenGLApp()
{
}

bool OpenGLApp::Init()
{
	//GlobalState::save();
	//GlobalState::load();
	eventProcessor = new EventProcessor();
	Command::mainApp = this;
	Observer::mainApp = this;
	DynamicObject::mainApp = this;

	player = new Player((PointXYZ(128, 192, 0)));

	zone = new Zone("Main Hall", player);
	zone->load("Resources/Zones/lvl1.zone");
	zone->activeMap = zone->maps.at(0).at(0);
	currentMap = zone->activeMap;
	playerPosition = player->getPosition();
	

	return true;
}

bool OpenGLApp::Shutdown()
{
	return shutdown;
}

void OpenGLApp::SetupProject(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	
	if (width == 0)
	{
		width = 1;
	}
	GLenum glen = glewInit();
	if (glen != GLEW_OK)
	{
		cout << "GLEW failed";
		exit(1);
	}
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5);

	m_windowWidth = width;
	m_windowHeight = height;
}

void OpenGLApp::KeyboardInputFunction(unsigned char key, int x, int y)
{
	player->playerMovementControl(key, x, y);
}

void OpenGLApp::KeyboardInputFunctionRelease(unsigned char key, int x, int y)
{
	player->playerMovementControlRelease(key, x, y);
}

void OpenGLApp::Update(float dt)
{
	eventProcessor->Update(dt);
	for (auto dyn : currentMap->dynamicsObj)
	{
		dyn->update(dt);
	}

	player->playerMovement(dt);
	player->onStaticColision(currentMap->getTyle(PointXYZ(player->getPosition().x,
												player->getPosition().y, 0)));
	player->onStaticColision(currentMap->getTyle(PointXYZ(player->getPosition().x+ 32 - 1,
												player->getPosition().y, 0)));
	player->onStaticColision(currentMap->getTyle(PointXYZ(player->getPosition().x,
												player->getPosition().y + 32 - 1, 0)));
	player->onStaticColision(currentMap->getTyle(PointXYZ(player->getPosition().x + 32 - 1,
												player->getPosition().y + 32 - 1, 0)));
	if (currentMap->dynamicsObj.size() > 1)
	{
		for (int i = 1; i < currentMap->dynamicsObj.size(); i++)
		{
			player->onDynamicColision(currentMap->dynamicsObj.at(i));
			if (currentMap->dynamicsObj.at(i)->name == "enemy")
			{
				for (auto dyn : currentMap->dynamicsObj)
				{
					DynamicObject* object = currentMap->dynamicsObj.at(i);
					object->onDynamicColision(dyn);
					object->onStaticColision(currentMap->getTyle(PointXYZ(object->getPosition().x,
						object->getPosition().y, 0)));
					object->onStaticColision(currentMap->getTyle(PointXYZ(object->getPosition().x + 32 - 1,
						object->getPosition().y, 0)));
					object->onStaticColision(currentMap->getTyle(PointXYZ(object->getPosition().x,
						object->getPosition().y + 32 - 1, 0)));
					object->onStaticColision(currentMap->getTyle(PointXYZ(object->getPosition().x + 32 - 1,
						object->getPosition().y + 32 - 1, 0)));
				}
			}
		}
	}
	playerPosition = player->getPosition();
	
}

void OpenGLApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(-playerPosition.x, -playerPosition.y, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnd();
	glPushMatrix();
	glTranslatef(m_windowWidth / 2, m_windowHeight / 2, 0);
		currentMap->display();
		for (int i = 0; i < currentMap->dynamicsObj.size(); i++)
			currentMap->dynamicsObj.at(i)->render();	
		currentMap->dynamicsObj.at(0)->render();
	glPopMatrix();

	eventProcessor->Render();

	glutSwapBuffers();
}

void OpenGLApp::ChangeMap(Map* nextMap, int x, int y)
{
	this->currentMap = nextMap;
	zone->activeMap = nextMap;
	this->player->setPosition(x, y, 0);
}

void OpenGLApp::showText(string text)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, 0, 0);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_POLYGON);
	glVertex2i(0,0);
	glVertex2i(m_windowWidth, 0);
	glVertex2i(m_windowWidth, m_windowHeight/4);
	glVertex2i(0, m_windowHeight / 4);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRasterPos2i(m_windowWidth / 5, m_windowHeight / 5);

	string str = text;
	for (auto ch : str)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch);
	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(m_windowWidth, 0);
	glVertex2i(m_windowWidth, m_windowHeight / 4);
	glVertex2i(0, m_windowHeight / 4);
	glEnd();
	glPopMatrix();
}

