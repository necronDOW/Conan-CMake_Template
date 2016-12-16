#include "Trajectory.h"

Trajectory::Trajectory() { }

Trajectory::Trajectory(glProgram& program, Renderer* renderer, std::vector<std::string> vData)
{
	glm::vec3 last, current;
	glm::vec3 scale = glm::vec3(0.001f);
	glm::vec3 offset;

	for (unsigned int i = 0; i < vData.size(); i++)
	{
		FindValue(vData[i], 'X', current.x);
		FindValue(vData[i], 'Y', current.y);

		if (i > 0 && last != current)
		{
			glm::vec3 diff = current - last;
			glm::vec3 tVec = last + (diff * 2.0f);

			renderer->AddToRender(new Arrow(program, (last * scale) + offset,
				(tVec * scale) + offset));
		}
		else offset = -(current * scale);

		last.x = current.x;
		last.y = current.y;
	}
}

Trajectory::Trajectory(glProgram& program, Renderer* renderer, std::vector<std::string> vData, std::vector<std::string> cData)
{
	
}

void Trajectory::Update()
{

}

bool Trajectory::FindValue(std::string str, char id, float& out)
{
	unsigned int start, end;

	for (start = 0; start < str.length(); start++)
	{
		if (str[start] == id)
		{
			for (end = start; end < str.length(); end++)
			{
				if (str[end] == ' ')
				{
					std::string tmp = str.substr(start + 2, (end - start) - 2);

					if (IsNum(tmp))
					{
						out = std::stof(tmp);
					}

					return true;
				}
			}
		}
	}

	return false;
}

bool Trajectory::IsNum(std::string str)
{
	for (char c : str)
	{
		if ((c > '-') && (c > '9'))
			return false;
	}

	return true;
}