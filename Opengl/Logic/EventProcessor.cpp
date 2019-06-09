#include "EventProcessor.h"

EventProcessor::EventProcessor()
{
	commandQueue = {};
}

EventProcessor::~EventProcessor()
{
}

void EventProcessor::AddCommand(Command * cmnd)
{
	commandQueue.push_back(cmnd);
}

void EventProcessor::Update(float dt)
{

	userControl = commandQueue.empty();
	if (!commandQueue.empty())
	{
		if (!commandQueue.front()->isCompleted)
		{
			if (commandQueue.front()->isStarted)
			{
				commandQueue.front()->Update(dt);
			}
			else
			{
				commandQueue.front()->Start();
			}
		}
		else 
		{
			commandQueue.erase(commandQueue.begin());
		}
	}
}

void EventProcessor::Render()
{
	if (!commandQueue.empty())
		commandQueue.front()->Render();
}
