#pragma once

#include <iostream>
#include <vector>
#include "Observer.h"

class Observable
{
protected:
	std::vector<Observer*> observers;

public:
	Observable();
	void addObserver(Observer* observer);
	void addObservers(std::vector<Observer*> observers);
	void addObservers(std::vector<Observer*> observers, GameObject* object);
	virtual void notify(float dt);

};
