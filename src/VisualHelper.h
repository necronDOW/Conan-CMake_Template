#ifndef visualshelper_h_defined
#define visualshelper_h_defined

#define PALETTE_SIZE 6

#include <string>
#include <vector>

#include "SDL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

const enum Palette
{
	Red, Green, Blue,
	Yellow, Magenta, Cyan
};

class Color
{
	private: static Color* _instance;
	public: static Color* Get();

	public:
		glm::vec3 GetColor(Palette choice);
		glm::vec3 GetColor(unsigned int choice);
		glm::vec3 CombineColor(glm::vec3 colorA, glm::vec3 colorB, int constant);
		glm::vec3 SubtractColor(glm::vec3 colorA, glm::vec3 colorB, int constant);
		glm::vec3 InvertColor(glm::vec3 color);

	private:
		Color() { }

		const glm::vec3 _palette[PALETTE_SIZE] = {
			glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1),
			glm::vec3(1, 1, 0), glm::vec3(1, 0, 1), glm::vec3(0, 1, 1)
		};
};

#endif