#ifndef DYNAMIC_OBJECT
#define DYNAMIC_OBJECT
#include "GameObject.h"
class OpenGLApp;

class DynamicObject : public GameObject
{
protected:
	int speed = 20;

	bool solidVsDynamic = true;
	bool solidVsStatic = true;

public:
	float xVelocity = 0;
	float yVelocity = 0;

	static OpenGLApp* mainApp;

public:

	DynamicObject(string filePath, PointXYZ position);
	DynamicObject(string filePath);

	DynamicObject(long long id, PointXYZ position);
	DynamicObject(long long id);

	DynamicObject();

	virtual void onDynamicInteraction(DynamicObject* dObj);
	virtual void onStaticInteraction(GameObject* obj);

	virtual void onStaticColision(GameObject* obj);
	virtual bool onDynamicColision(DynamicObject* obj);

	virtual void update(float dt) override;
};

#endif
