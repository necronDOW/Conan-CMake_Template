#include "Trajectory.h"

Trajectory::Trajectory() { }

Trajectory::Trajectory(glProgram& program, Renderer* renderer, glm::vec2* &vData, int vSize)
{
	glm::vec2 last;
	_scale = glm::vec2(0.001f);

	for (unsigned int i = 0; i < vSize; i++)
	{
		vData[i] = (vData[i] * _scale);

		if (i == 0)
			_offset = -vData[i];

		vData[i] += _offset;

		if (i > 0)
		{
			if (last != vData[i])
			{
				glm::vec2 diff = vData[i] - last;
				glm::vec2 tVec = last + (diff * 2.0f);

				renderer->AddToRender(new Arrow(program, last, tVec));
			}
		}

		UpdateBounds((vData[i]));

		last.x = vData[i].x;
		last.y = vData[i].y;
	}
}

Trajectory::Trajectory(glProgram& program, Renderer* renderer, glm::vec2* &vData, int vSize, std::vector<std::string> cData)
{
	
}

void Trajectory::Update()
{

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