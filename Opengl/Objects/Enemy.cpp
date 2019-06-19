#include "Enemy.h"
#include "Animation.h"
#include "../Core/OpenGLApp.h"
#include "Player.h"

std::string pathToEnemy = "Resources/Enemies/";
Enemy::Enemy(long long id, PointXYZ position)
	: DynamicObject(id, position)
{
	this->name = "enemy";
	left = new Animation();
	left->addSprite(pathToEnemy + "Enemy_lvl1_1.bmp");
	left->addSprite(pathToEnemy + "Enemy_lvl1_2.bmp");
	left->addSprite(pathToEnemy + "Enemy_lvl1_3.bmp");
	left->addSprite(pathToEnemy + "Enemy_lvl1_4.bmp");
	left->addSprite(pathToEnemy + "Enemy_lvl1_5.bmp");
	left->addSprite(pathToEnemy + "Enemy_lvl1_6.bmp");
	right = left;
	down = left;
	up = left;
	this->currentAnimation = left;
	solidVsDynamic = false;
	solidVsStatic = true;
}

Enemy::Enemy(long long id)
	: Enemy(id, PointXYZ(0, 0, 0))
{
	this->name = "enemy";
}

Enemy::Enemy()
{
	this->name = "enemy";
}

void Enemy::behavior(float dt)
{
	this->xVelocity = 0;
	this->yVelocity = 0;
	Player* player = mainApp->player;
	if (abs(this->position.x - player->position.x) <= 128 &&
		abs(this->position.y - player->position.y) <= 128)
	{ 
		if (this->position.x < player->position.x)
		{
			this->xVelocity = ceil(speed * dt);
		}
		else if (this->position.x > player->position.x)
		{
			this->xVelocity = -ceil(speed * dt);
		}
		else if (this->position.y < player->position.y)
		{
			this->yVelocity = ceil(speed * dt);
		}
		else if (this->position.y > player->position.y)
		{
			this->yVelocity = -ceil(speed * dt);
		}
	}
		setAnimation();
}


void Enemy::update(float dt)
{
	DynamicObject::update(dt);
	this->sprite = this->currentAnimation->runAnimation(dt);
	behavior(dt);
	this->position.x += xVelocity;
	this->position.y += yVelocity;
}

void Enemy::setAnimation()
{
	Player* player = mainApp->player;
	if (this->position.x <= player->position.x)
		currentAnimation = left;
	else if (this->position.x >= player->position.x)
		currentAnimation = right;
	if (this->position.y <= player->position.y)
		currentAnimation = down;
	else if (this->position.y >= player->position.y)
		currentAnimation = up;
}