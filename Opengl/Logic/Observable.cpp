#include "Observable.h"

Observable::Observable()
{
	observers = {};
}

void Observable::addObserver(Observer* observer)
{
	observers.push_back(observer);
}

void Observable::notify(float dt)
{
	for (auto observer : observers)
	{
		observer->update(dt);
	}
}