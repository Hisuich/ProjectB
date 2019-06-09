#pragma once

#include "../Graphics/BMP.h"

class Animation
{
public:
	std::vector<BMP*> sprites;
	int currentSprite;
	float time = 0.0;

public:
	Animation();
	~Animation();

	void addSprite(BMP* sprite);
	void addSprite(string sprite);

	BMP* getCurrentSprite();
	BMP* runAnimation(float dt);
};