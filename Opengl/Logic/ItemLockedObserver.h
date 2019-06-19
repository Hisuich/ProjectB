#pragma once

#include "Observer.h"
class Teleport;
class Item;


class ItemLockedObserver : public Observer
{
public:
	bool hasItem = false;
	Teleport* pass = nullptr;
	long long keyId = 0;

public:
	ItemLockedObserver(long long keyID, Teleport* pass);
	ItemLockedObserver(long long keyID);

	void update(float dt) override;
};