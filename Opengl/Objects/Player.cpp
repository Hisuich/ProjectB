#include "Player.h"

#include "../Logic/RemoveObjectCommand.h"
#include "../Logic/PlayerTakeItemCommand.h"

std::string pathToPlayer = "Resources/Player/";
bool* Player::key = new bool[256];

Player::Player(PointXYZ position)
	: DynamicObject::DynamicObject(pathToPlayer + "character.bmp", position)
{
	left = new Animation();
	left->addSprite(pathToPlayer + "character_left_1.bmp");
	left->addSprite(pathToPlayer + "character_left_2.bmp");
	left->addSprite(pathToPlayer + "character_left_1.bmp");
	left->addSprite(pathToPlayer + "character_left_3.bmp");
	right = new Animation(); 
	right->addSprite(pathToPlayer + "character_right_1.bmp"); 
	right->addSprite(pathToPlayer + "character_right_2.bmp");
	right->addSprite(pathToPlayer + "character_right_1.bmp");
	right->addSprite(pathToPlayer + "character_right_3.bmp");
	up = new Animation();
	up->addSprite(pathToPlayer + "character_up_1.bmp");
	up->addSprite(pathToPlayer + "character_up_2.bmp");
	up->addSprite(pathToPlayer + "character_up_1.bmp");
	up->addSprite(pathToPlayer + "character_up_3.bmp");
	down = new Animation();
	down->addSprite(pathToPlayer + "character_down_1.bmp");
	down->addSprite(pathToPlayer + "character_down_2.bmp");
	down->addSprite(pathToPlayer + "character_down_1.bmp");
	down->addSprite(pathToPlayer + "character_down_3.bmp");
	this->currentAnimation = down;
	inventory = new Inventory();
	eventProcessor = nullptr;
	this->name = "player";
	solidVsDynamic = true;
	solidVsStatic = true;
}

Player::Player()
	:  Player::Player(PointXYZ(0,0,0))
{
}

void Player::playerMovementControl(unsigned char key, int x, int y)
{
	
	if(eventProcessor->userControl)
	switch (key)
	{
	case 'a':
		direction = LEFT;
		isStay = false;
		break;
	case 'w':
		direction = UP;
		isStay = false;
		break;
	case 'd':
		direction = RIGHT;
		isStay = false;
		break;
	case 's':
		direction = DOWN;
		isStay = false;
		break;
	case 'e':
		xVelocity = 0;
		yVelocity = 0;
		this->eventProcessor->AddCommand(new InteractCommand(this, direction));
		break;
	case 'c':
		this->showInventory = true;
		break;
	default:
		break;
	}
	this->key[key] = true;
}

void Player::onStaticColision(GameObject* object)
{
	if (this->solidVsStatic)
	{
		if (object->isSolid())
		{
			if (this->xVelocity < 0)
			{
				if (object->getPosition().x + object->getWidth() >= this->getPosition().x)
				{

					this->position.x = object->getPosition().x + object->getWidth();

					this->xVelocity = 0;
				}
			}
			else if (this->xVelocity > 0)
			{
				if (object->getPosition().x <= this->getPosition().x + this->getWidth())
				{
					this->position.x = object->getPosition().x - object->getWidth();

					this->xVelocity = 0;
				}
			}
			else if (this->yVelocity < 0)
			{
				if (object->getPosition().y + object->getHeight() >= this->getPosition().y)
				{
					this->position.y = object->getPosition().y + object->getHeight();

					this->yVelocity = 0;
				}
			}
			else if (this->yVelocity > 0)
			{
				if (object->getPosition().y <= this->getPosition().y + this->getHeight())
				{
					this->position.y = object->getPosition().y - object->getHeight();

					this->yVelocity = 0;
				}
			}

		}
	}
}

void Player::playerMovementControlRelease(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if (direction == LEFT) {
			xVelocity = 0;
			isStay = true;
		}
		break;
	case 'd':
		if (direction == RIGHT) {
			xVelocity = 0;
			isStay = true;
		}
		break;
	case 's':
		if (direction == DOWN) {
			yVelocity = 0;
			isStay = true;
		}
		break;
	case 'w':
		if (direction == UP) {
			yVelocity = 0;
			isStay = true;
	}
		break;
	case 'c':
		this->showInventory = !this->showInventory;
		break;
	default:
		break;
	}
	this->key[key] = false;
}

void Player::playerMovement(float dt)
{
	this->setAnimation();
	if (!isStay) {
		this->runAnimation(dt);
		xVelocity = (direction == LEFT ? -speed : direction == RIGHT ? speed : 0) * dt;
		yVelocity = (direction == DOWN ? -speed : direction == UP ? speed : 0) * dt;

		position.x += xVelocity;
		position.y += yVelocity;
	}
	
	//this->setPosition(newPosition);
}

void Player::setAnimation()
{
	switch (direction)
	{
	case LEFT:
		this->currentAnimation = left;
		break;
	case RIGHT:
		this->currentAnimation = right;
		break;
	case UP:
		this->currentAnimation = up;
		break;
	case DOWN:
		this->currentAnimation = down;
		break;
	default:
		break;
	}
	this->sprite = this->currentAnimation->getCurrentSprite();
}

void Player::runAnimation(float dt)
{
	this->sprite = this->currentAnimation->runAnimation(dt);
}

void Player::onStaticInteraction(GameObject* object)
{

	if (object->name == "Item")
	{
		DialogCommand* dialog = new DialogCommand();
		dialog->addResponse("take", new PlayerTakeItemCommand((Item*)object));
		dialog->addResponse("not to do anything");
		eventProcessor->AddCommand(dialog);
		return;
	}
	else if (object->name == "Teleport")
	{
		return;
	}
	else
	{
		eventProcessor->AddCommand(new TextCommand(ID::getObjectDescription(object->id)));

	}
}

void Player::takeItem(Item * item)
{
	this->inventory->addItem(item);
	this->inventory->getItems();
	this->eventProcessor->AddCommand(new RemoveObjectCommand(item));
}

void Player::update(float dt)
{
	DynamicObject::update(dt);
}

void Player::render()
{
	drawGameObject();
	if (this->showInventory)
	{
		this->inventory->display();
	}
}

bool Player::hasItem(Item * item)
{
	for (auto it : this->inventory->items) 
	{
		if (it->id == item->id)
			return true;
	}
	return false;
}

