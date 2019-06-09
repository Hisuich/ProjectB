#include "Animation.h"

Animation::Animation()
{

}

Animation::~Animation()
{
}

void Animation::addSprite(BMP* bmp)
{
	sprites.push_back(bmp);
}

void Animation::addSprite(string bmp)
{
	sprites.push_back(new BMP(bmp));
}

BMP* Animation::getCurrentSprite()
{
	return sprites.at(currentSprite);
}

BMP* Animation::runAnimation(float dt)
{
	time += dt;
	if (time > 1.0f)
	{
		time = 0;
		currentSprite = (currentSprite + 1) % sprites.size();
	}
	return sprites.at(currentSprite);
}