#ifndef COMMAND
#define COMMAND

#include <iostream>

class OpenGLApp;
class DynamicObject;

class Command
{
public:
	DynamicObject* obj = nullptr;
	bool isStarted;
	bool isCompleted;
	static OpenGLApp* mainApp;
	

public:
	Command();
	Command(DynamicObject* obj);
	~Command();
	virtual void Start();
	virtual void Update(float dt);
	virtual void Render();

};

#endif


