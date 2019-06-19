#include "Observable.h"

Observable::Observable()
{
	observers = {};
}

void Observable::addObserver(Observer* observer)
{
	observers.push_back(observer);
}

void Observable::addObservers(std::vector<Observer*> observers)
{
	for (auto observer : observers)
	{
		this->observers.push_back(observer);
	}
	//this->observers.insert(this->observers.end(), observers.begin(), observers.end());
}

void Observable::addObservers(std::vector<Observer*> observers, GameObject* object)
{
	for (auto observer : observers) {
		
		observer->setObject(object);
	}
	this->addObservers(observers);
}

void Observable::notify(float dt)
{
	for (auto observer : this->observers)
	{
		observer->update(dt);
	}
}