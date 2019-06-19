#pragma once

#include "DynamicObject.h"
class Animation;

class Enemy : public DynamicObject
{
public:
	Animation* left = nullptr;
	Animation* right = nullptr;
	Animation* up = nullptr;
	Animation* down = nullptr;
	Animation* currentAnimation = nullptr;

	int speed = 5;
	
public:
	Enemy(long long id, PointXYZ position);
	Enemy(long long id);
	Enemy();

	virtual void behavior(float dt);
	void setAnimation();
	void update(float dt) override;
};