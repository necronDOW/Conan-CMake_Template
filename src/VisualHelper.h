#ifndef visualshelper_h_defined
#define visualshelper_h_defined

#include <string>
#include <vector>

#include "SDL.h"

struct MessageBoxOption
{
	char* msg;
	bool* response;

	MessageBoxOption(char* m, bool* r)
	{
		msg = m;
		response = r;

		if (response != NULL)
			*response = false;
	}
};

class DialogTools
{
	public:
		static void ShowMessage(char* title, char* text, std::vector<MessageBoxOption*> options);
};

class Color
{

};

#endif