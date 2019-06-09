#include "TextCommand.h"


#include "../Core/OpenGLApp.h"

TextCommand::TextCommand(std::string text) : Command()
{
	this->text = text;
	while (text[length] != '\0') length++;
}

void TextCommand::Start() 
{
	isStarted = true;
}

void TextCommand::Update(float dt)
{
	time += dt;
	if (time >= 10.0)
		isCompleted = true;
}

void TextCommand::Render()
{
	mainApp->showText(text);
}