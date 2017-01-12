#include "VisualHelper.h"

void DialogTools::ShowMessage(char* title, char* text, std::vector<MessageBoxOption*> options)
{
	int buttonSize = options.size();
	SDL_MessageBoxButtonData* buttons = new SDL_MessageBoxButtonData[buttonSize];

	for (int i = 0; i < buttonSize; i++)
	{
		int btnIndex = buttonSize - i - 1;
		buttons[i] = { 0, btnIndex, options[btnIndex]->msg };
	}

	const SDL_MessageBoxData msgBoxData = { SDL_MESSAGEBOX_INFORMATION, NULL,
		title, text, options.size(), buttons };

	int buttonID;
	SDL_ShowMessageBox(&msgBoxData, &buttonID);
	
	if (options[buttonID]->response != NULL)
		*options[buttonID]->response = true;
}

Color* Color::_instance = NULL;

Color* Color::Get()
{
	if (_instance == nullptr)
		_instance = new Color();
	return _instance;
}

glm::vec3 Color::GetColor(Palette choice)
{
	return _palette[(int)choice];
}

glm::vec3 Color::GetColor(unsigned int choice)
{
	if (choice < PALETTE_SIZE)
		return _palette[choice];
}

glm::vec3 Color::CombineColor(glm::vec3 colorA, glm::vec3 colorB, int constant)
{
	if (colorA == glm::vec3(0))
		return colorB;
	else if (colorB == glm::vec3(0))
		return colorA;

	float c = (float)constant;
	return ((colorA * c) + colorB) / (c + 1);
}

glm::vec3 Color::SubtractColor(glm::vec3 colorA, glm::vec3 colorB, int constant)
{
	if (colorB == glm::vec3(0))
		return colorA;

	float c = (float)constant;
	return ((colorA * c) - colorB) / (c - 1);
}

glm::vec3 Color::InvertColor(glm::vec3 color)
{
	return glm::vec3(1) - color;
}