#ifndef TEXT_COMMAND
#define TEXT_COMMAND

#include "Command.h"
class TextCommand : public Command
{
public:
	std::string text;
	int length = 0;
	float time = 0;

public:
	TextCommand(std::string text);

	void Start() override;

	void Update(float dt) override;

	void Render() override;
};

#endif // !TEXT_COMMAND
