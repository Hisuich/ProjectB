#ifndef MAIN_GameObject
#define MAIN_GameObject

#include <math.h>

#include <stdlib.h>
#include <glew.h>
#include <freeglut.h>

#include "../Core/PointXYZ.h"
#include "../Graphics/BMP.h"
#include "Direction.h"
#include "../Logic/Observable.h"

class GameObject : public Observable {

protected:
	
	static Direction direction;
	bool Solid;

public:
	BMP* sprite;
	PointXYZ position;

	long id;
	const char* name = "";
	bool interactable = false;
	const char* description = "";

public:
	
	GameObject(string spriteFilePath, PointXYZ position, bool isSolid);
	GameObject(string spriteFilePath, PointXYZ position);
	GameObject(string spriteFilePath);

	GameObject(long id, PointXYZ position);
	GameObject(long id);

	GameObject();
	~GameObject();

	PointXYZ getPosition() { return position; };
	
	void setPosition(PointXYZ* playerPosition) { this->position = *playerPosition; };
	void setPosition(int x, int y, int z) { this->position = PointXYZ(x, y, z); };
	
	int getWidth() { return this->sprite->getWidth(); };
	int getHeight() { return this->sprite->getHeight(); };
	
	bool isSolid() { return this->Solid; };

	void drawGameObject();
	void drawGameObject(PointXYZ position);

	virtual void update(float dt);
	virtual void render();

	void onInteraction(GameObject object);
};

#endif
