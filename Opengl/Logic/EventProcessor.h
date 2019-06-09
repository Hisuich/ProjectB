#ifndef EVENT_PROCESSOR
#define EVENT_PROCESSOR

#include <iostream>
#include <vector>
#include "Command.h"

class EventProcessor
{
public:
	std::vector<Command*> commandQueue;
	bool userControl = true;

public: 
	EventProcessor();
	~EventProcessor();

	void AddCommand(Command* cmnd);
	void Update(float dt);
	void Render();
};

#endif
