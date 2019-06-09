#pragma once

#include "Command.h"
#include <map>
#include <string>
#include "../Objects/Player.h"

class DialogCommand : public Command
{
	
public:
	std::map<std::string, Command*> variants;
	std::vector<string> responses;
	int active = 0;

public:
	DialogCommand();
	~DialogCommand();


	void Update(float dt) override;

	void Render() override;

	void addResponse(string variant);
	void addResponse(string variant, Command* Action);
};