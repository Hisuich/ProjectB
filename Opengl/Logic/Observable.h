#pragma once

#include <vector>
#include "Observer.h"

class Observable
{
protected:
	std::vector<Observer*> observers;

public:
	Observable();
	void addObserver(Observer* observer);
	virtual void notify(float dt);

};
