#include "Command.h"

OpenGLApp* Command::mainApp = nullptr;

Command::Command()
{
	isStarted = false;
	isCompleted = false;
}

Command::Command(DynamicObject * obj)
{
	this->obj = obj;
	isStarted = false;
	isCompleted = false;
}


Command::~Command()
{
	delete obj;
}

void Command::Start()
{
	isStarted = true;
}

void Command::Update(float dt)
{
}

void Command::Render()
{
}
