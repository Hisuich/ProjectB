#include "DynamicObject.h"

OpenGLApp* DynamicObject::mainApp = nullptr;

DynamicObject::DynamicObject(string filePath, PointXYZ position)
	: GameObject::GameObject(filePath, position)
{

}

DynamicObject::DynamicObject(string filePath)
	: DynamicObject::DynamicObject(filePath, PointXYZ(0,0,0))
{
}

DynamicObject::DynamicObject(long long id, PointXYZ position)
	: GameObject::GameObject(id, position)
{
}

DynamicObject::DynamicObject(long long id)
	: DynamicObject::DynamicObject(id, PointXYZ(0, 0, 0))
{
}

DynamicObject::DynamicObject()
	: GameObject::GameObject()
{
}

void DynamicObject::onDynamicInteraction(DynamicObject * dObj)
{
}

void DynamicObject::onStaticInteraction(GameObject * obj)
{
}

void DynamicObject::onStaticColision(GameObject* obj)
{
	if (this->solidVsStatic)
	{
		if (obj->isSolid())
		{
			if (this->xVelocity < 0)
			{
				if (obj->getPosition().x + obj->getWidth() >= this->getPosition().x)
				{

					this->position.x = obj->getPosition().x + obj->getWidth();

					this->xVelocity = 0;
				}
			}
			else if (this->xVelocity > 0)
			{
				if (obj->getPosition().x <= this->getPosition().x + 32)
				{
					this->position.x = obj->getPosition().x - obj->getWidth();

					this->xVelocity = 0;
				}
			}
			else if (this->yVelocity < 0)
			{
				if (obj->getPosition().y + obj->getHeight() >= this->getPosition().y)
				{
					this->position.y = obj->getPosition().y + obj->getHeight();

					this->yVelocity = 0;
				}
			}
			else if (this->yVelocity > 0)
			{
				if (obj->getPosition().y <= this->getPosition().y + 32)
				{
					this->position.y = obj->getPosition().y - obj->getHeight();

					this->yVelocity = 0;
				}
			}

		}
	}
}

bool DynamicObject::onDynamicColision(DynamicObject * obj)
{	
	if (this->solidVsDynamic && obj->solidVsDynamic)
	{
		if (this->position.x + 32 > obj->position.x &&
			this->position.x < obj->position.x + obj->getWidth() &&
			this->position.y + 32 > obj->position.y &&
			this->position.y < obj->position.y + obj->getHeight())
		{
			if (this->xVelocity > 0)
			{
				this->position.x = obj->getPosition().x - 32;
			}
			else if (this->xVelocity < 0)
			{
				this->position.x = obj->getPosition().x + 32;
			}

			if (this->position.x + 32 > obj->position.x &&
				this->position.x < obj->position.x + obj->getWidth() &&
				this->position.y + 32 > obj->position.y &&
				this->position.y < obj->position.y + obj->getHeight())
			{
				if (this->yVelocity > 0)
				{
					this->position.y = obj->getPosition().y - 32;
				}
				else if (this->yVelocity < 0)
				{
					this->position.y = obj->getPosition().y + 32;
				}
			}

			return true;
		}
		
	}
	else
	{
		if (this->position.x + 32 > obj->position.x &&
			this->position.x <= obj->position.x + this->getWidth() &&
			this->position.y + 32 > obj->position.y &&
			this->position.y <= obj->position.y + this->getHeight())
		{
			return true;
		}
	}
	return false;
}

void DynamicObject::update(float dt)
{
	GameObject::update(dt);
}
