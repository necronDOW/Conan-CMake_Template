#include "Trajectory.h"

Trajectory::Trajectory() { }

Trajectory::Trajectory(glProgram& program, Renderer* renderer, std::vector<std::string> vData)
{
	glm::vec3 last, current;
	glm::vec3 scale = glm::vec3(0.001f);
	glm::vec3 offset;

	for (unsigned int i = 0; i < vData.size(); i++)
	{
		AssetManager::FindValue(vData[i], 'X', current.x);
		AssetManager::FindValue(vData[i], 'Y', current.y);

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