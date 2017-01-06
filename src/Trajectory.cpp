#include "Trajectory.h"

Trajectory::Trajectory() { }

Trajectory::Trajectory(glProgram& program, glm::vec2* vData, unsigned int vSize)
	: DrawableBase(program, glm::vec3(0))
{
	float maxLen = 0.0f;
	glm::vec3 colorHi = RandomColor();
	glm::vec3 colorLow = colorHi * 0.25f;

	for (unsigned int i = 0; i < vSize; i++)
	{
		if (i != 0)
		{
			float len = glm::length(vData[i] - vData[i - 1]);
			maxLen = len > maxLen ? len : maxLen;
		}
	}

	for (unsigned int i = 1; i < vSize; i++)
	{
		glm::vec2 last = vData[i - 1];
		glm::vec2 current = vData[i];

		if (last != current)
		{
			float vel = glm::length(current - last) / maxLen;
			glm::vec3 color = glm::vec3(0.25f) + (colorLow * (1.0f - vel)) + (colorHi * vel);

			Arrow* tmp = new Arrow(program, last, current, color);
			Renderer::Get()->AddToRender(tmp);
		}
	}

	/*CreateVertex(glm::vec3(vData[0].x, vData[0].y, 0), glm::vec3(0));

	for (int i = 1; i < vSize; i++)
	{
		glm::vec3 last = glm::vec3(vData[i - 1].x, vData[i - 1].y, 0);
		glm::vec3 current = glm::vec3(vData[i].x, vData[i].y, 0);

		float vel = glm::length(current - last) / maxLen;
		glm::vec3 color = glm::vec3(0.25f) + (colorLow * (1.0f - vel)) + (colorHi * vel);

		CreateVertex(current, color);
		CreateElement(i - 1, i);
	}

	Initialize();*/
}

float timer = 0.0f;
void Trajectory::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer > 0.1f)
	{
		timer = 0.0f;
	}
}

void Trajectory::MainDraw()
{
	glDrawElements(GL_LINES, _eCount * 2, GL_UNSIGNED_INT, 0);
}

glm::vec3 Trajectory::RandomColor()
{
	float randMaxFloat = (float)RAND_MAX;
	float r = (float)rand() / randMaxFloat;
	float g = (float)rand() / randMaxFloat;
	float b = (float)rand() / randMaxFloat;
	
	return glm::vec3(r, g, b);
}