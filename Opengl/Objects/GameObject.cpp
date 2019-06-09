#include "GameObject.h"
#include "ID.h"

Direction GameObject::direction = NOT_MOVE;

GameObject::GameObject(string spriteFilePath, PointXYZ position, bool Solid)
{
	this->Solid = Solid;
	this->sprite = new BMP(spriteFilePath);
	this->position = position;
}

GameObject::GameObject(string spriteFilePath, PointXYZ position) 
	//: GameObject::GameObject(spriteFilePath, position, false)
{
	this->sprite = new BMP(spriteFilePath);
	this->position = position;
}

GameObject::GameObject(string spriteFilePath) 
	//: GameObject::GameObject(spriteFilePath, PointXYZ(0, 0, 0), false)
{
	this->sprite = new BMP(spriteFilePath);
	this->position = PointXYZ(0, 0, 0);
}

GameObject::GameObject(long id, PointXYZ position)
{
	this->id = id;
	this->sprite = ID::getSprite(id);
	this->position = position;
	if (this->sprite->fileName == "Resources/sprites/empty.bmp")
		this->Solid = true;
	else
		this->Solid = ID::isMapTyleSolid(id);
	this->interactable = ID::isTileInteractable(id);
}

GameObject::GameObject(long id)
	: GameObject::GameObject(id, PointXYZ(0,0,0))
{
}

GameObject::GameObject()
{
	this->position = PointXYZ(0, 0, 0);
}

GameObject::~GameObject()
{
}

void GameObject::drawGameObject()
{
	glRasterPos2i(position.x, position.y);
	glDrawPixels(sprite->getWidth(), sprite->getHeight(),  sprite->hasAlphaChannel() ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, sprite->getPixelsData());
}

void GameObject::drawGameObject(PointXYZ position)
{
	this->position = position;
	drawGameObject();
}

void GameObject::onInteraction(GameObject object)
{
}

void GameObject::update(float dt)
{
	this->notify(dt);
}

void GameObject::render()
{
	drawGameObject();
}

