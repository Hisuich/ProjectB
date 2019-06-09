#pragma once

class OpenGLApp;
class GameObject;

class Observer
{
protected:

	GameObject* obj;

public:
	static OpenGLApp* mainApp;

public:

	Observer();
	Observer(GameObject* obj);

	virtual void update(float dt);
};