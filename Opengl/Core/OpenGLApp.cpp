#include "OpenGLApp.h"

#include "../Objects/Player.h"
#include "../Objects/Zone.h"

OpenGLApp::OpenGLApp()
{
	Init();
}

OpenGLApp::~OpenGLApp()
{
}

bool OpenGLApp::Init()
{
	eventProcessor = new EventProcessor();
	Command::mainApp = this;
	Observer::mainApp = this;

	player = new Player((PointXYZ(128, 192, 0)));
	player->eventProcessor = this->eventProcessor;


	Map* hallMap = new Map("hall");
	Map* hallContMap = new Map("hallCont");
	Map* lvl1_main_hall = new Map("lvl1_main_hall");
	Map* lvl1_bigroom = new Map("lvl1_bigroom");
	zone = new Zone("Main Hall", player);
	hallMap->load("Resources/Maps/main_hall.map");
	hallContMap->load("Resources/Maps/main_hall_cont.map");
	lvl1_main_hall->load("Resources/Maps/lvl1_hall_1.map");
	lvl1_bigroom->load("Resources/Maps/lvl1_bigroom_1.map");
	zone->addMap(lvl1_bigroom); zone->addMap(hallMap); zone->addMap(hallContMap); zone->addMapTo(hallMap, hallContMap, RIGHT);
	zone->activeMap = zone->maps.at(0).at(0);
	currentMap = zone->activeMap;
	
	playerPosition = player->getPosition();
	
	//glDisable(GL_DEPTH_TEST);
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
			cout << "interact " << currentMap->dynamicsObj.size();
			if (player->onDynamicColision(currentMap->dynamicsObj.at(i)));
					//currentMap->onInteraction(player, currentMap->dynamicsObj.at(i));
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

