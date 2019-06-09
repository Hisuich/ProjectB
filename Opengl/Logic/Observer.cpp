#include "Observer.h"

OpenGLApp* Observer::mainApp = nullptr;

Observer::Observer()
{
	this->obj = nullptr;
}

Observer::Observer(GameObject* object)
{
	this->obj = object;
}

void Observer::update(float dt)
{

}