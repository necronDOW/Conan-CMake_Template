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