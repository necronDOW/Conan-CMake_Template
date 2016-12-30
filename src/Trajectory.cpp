#include "Trajectory.h"

Trajectory::Trajectory() { }

Trajectory::Trajectory(glProgram& program, glm::vec2* &vData, unsigned int vSize)
{
	_scale = glm::vec2(0.001f);
	float maxLen = 0.0f;

	_colorLow = glm::vec3(1, 0, 0);
	_colorHi = glm::vec3(0, 1, 0);

	for (unsigned int i = 0; i < vSize; i++)
	{
		vData[i] *= _scale;

		if (i != 0)
		{
			float len = glm::length(vData[i] - vData[i - 1]);
			maxLen = len > maxLen ? len : maxLen;
		}
	}

	_offset = -vData[0];

	for (unsigned int i = 1; i < vSize; i++)
	{
		glm::vec2 last = _offset + vData[i - 1];
		glm::vec2 current = _offset + vData[i];

		if (last != current)
		{
			float vel = glm::length(current - last) / maxLen;
			glm::vec3 color = (_colorLow * (1.0f - vel)) + (_colorHi * vel);

			Arrow* tmp = new Arrow(program, last, current, color);
			tmp->SetDraw(true);
			_segments.push_back(tmp);
			Renderer::Get()->AddToRender(tmp);
		}

		UpdateBounds(_offset + vData[i]);
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

void Trajectory::AssignBounds(glm::vec2 value)
{
	_hi = value;
	_low = value;
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

glm::vec2 Trajectory::GetOffset() { return _offset; }
glm::vec2 Trajectory::GetLow() { return _low; }
glm::vec2 Trajectory::GetHi() { return _hi; }
glm::vec2 Trajectory::GetRange() { return _hi - _low; }