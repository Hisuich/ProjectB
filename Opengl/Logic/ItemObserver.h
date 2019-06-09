#pragma once

#include "Observer.h"
class Item;


class ItemObserver : public Observer
{
public:
	bool hasItem = false;

public:
	ItemObserver(Item* obj);

	void update(float dt) override;
};