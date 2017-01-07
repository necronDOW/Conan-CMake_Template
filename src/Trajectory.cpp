#include "Trajectory.h"

Trajectory::Trajectory() { }

Trajectory::Trajectory(glProgram& program, glm::vec2* vData, unsigned int vSize)
	: DrawableBase(program, glm::vec3(0))
{
	_colorHi = RandomColor();
	_colorLow = _colorHi * 0.1f;
	for (unsigned int i = 0; i < vSize; i++)
	{
		if (i != 0)
		{
			float len = glm::length(vData[i] - vData[i - 1]);
			_maxLen = len > _maxLen ? len : _maxLen;
		}
	}

	/*for (unsigned int i = 1; i < vSize; i++)
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
	}*/

	for (int i = 0; i < vSize - 1; i++)
	{
		glm::vec3 current = glm::vec3(vData[i].x, vData[i].y, 0);
		glm::vec3 next = glm::vec3(vData[i + 1].x, vData[i + 1].y, 0);

		CreateArrow(current, next, 0.5f, i);
	}

	Initialize();
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

void Trajectory::CreateArrow(glm::vec3 start, glm::vec3 end, float t, unsigned int index)
{
	glm::vec3 diff = end - start;
	float len = glm::length(end - start);

	glm::vec3 tVec = start + glm::vec3(diff * t);

	float headSize = len * 4;
	glm::vec3 headRad = diff * headSize;

	float vel = len / _maxLen;
	glm::vec3 color = glm::vec3(0.25f) + (_colorLow * (1.0f - vel)) + (_colorHi * vel);

	if (index == 0)
		CreateVertex(start, color);

	index *= 4;
	CreateVertex(tVec, color); // +1
	CreateVertex(tVec - headRad + glm::vec3(-diff.y, diff.x, 0) * headSize, color); // +2
	CreateVertex(tVec - headRad + glm::vec3(diff.y, -diff.x, 0) * headSize, color); // +3
	CreateVertex(end, color); // +4

	CreateElement(index, index + 4); // start -> end
	CreateElement(index + 1, index + 2);
	CreateElement(index + 1, index + 3);
}