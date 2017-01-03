#include "Trajectory.h"

Trajectory::Trajectory() { }

Trajectory::Trajectory(glProgram& program, glm::vec2* vData, unsigned int vSize)
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
			glm::vec3 color = (colorLow * (1.0f - vel)) + (colorHi * vel);

			Arrow* tmp = new Arrow(program, last, current, color);
			Renderer::Get()->AddToRender(tmp);

			UpdateBounds(vData[i]);
		}
	}
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

void Trajectory::UpdateBounds(glm::vec2 check)
{
	if (check.x < _low.x)
		_low.x = check.x;
	else if (check.x > _hi.x)
		_hi.x = check.x;

	if (check.y < _low.y)
		_low.y = check.y;
	else if (check.y > _hi.y)
		_hi.y = check.y;
}

glm::vec3 Trajectory::RandomColor()
{
	float randMaxFloat = (float)RAND_MAX;
	float r = (float)rand() / randMaxFloat;
	float g = (float)rand() / randMaxFloat;
	float b = (float)rand() / randMaxFloat;
	
	return glm::vec3(r, g, b);
}

glm::vec2 Trajectory::GetLow() { return _low; }
glm::vec2 Trajectory::GetHi() { return _hi; }
glm::vec2 Trajectory::GetRange() { return _hi - _low; }