#include "DialogCommand.h"

#include "../Core/OpenGLApp.h"

DialogCommand::DialogCommand()
	: Command::Command()
{
	
}

DialogCommand::~DialogCommand()
{
}

void DialogCommand::Update(float dt)
{
	if (Player::key['a'])
	{
		if (active != 0)
			active--;
	}
	
	if (Player::key['d'])
	{
		if (active != responses.size() - 1)
			active++;
	}

	if (Player::key['e'])
	{
		string str = responses.at(active);
		for (auto var : variants)
		{
			if (var.first == str)
			{
				this->mainApp->eventProcessor->AddCommand(var.second);
			}
		}
		isCompleted = true;
		
	}
}

void DialogCommand::Render()
{
	int m_windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	int m_windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, 0, 0);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2i(0, 0);
	glVertex2i(m_windowWidth, 0);
	glVertex2i(m_windowWidth, m_windowHeight / 4);
	glVertex2i(0, m_windowHeight / 4);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < responses.size(); i++)
	{
	glRasterPos2i(i  *  m_windowWidth / 8, m_windowHeight / 8);
	for (auto ch : responses.at(i))
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch);

	}
		glBegin(GL_LINES);
		glVertex2i(active * m_windowWidth / 8, m_windowHeight / 6);
		glVertex2i((active + 1) * m_windowWidth / 8, m_windowHeight / 6);
		glVertex2i((active + 1) * m_windowWidth / 8, m_windowHeight / 9);
		glVertex2i(active * m_windowWidth / 8, m_windowHeight / 9);
		glVertex2i(active * m_windowWidth / 8, m_windowHeight / 6);
		glEnd();
	

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(m_windowWidth, 0);
	glVertex2i(m_windowWidth, m_windowHeight / 4);
	glVertex2i(0, m_windowHeight / 4);
	glEnd();
	glPopMatrix();
}

void DialogCommand::addResponse(std::string variant)
{
	this->responses.push_back(variant);
}

void DialogCommand::addResponse(std::string variant, Command * action)
{
	addResponse(variant);
	variants.insert({ variant, action });
}


