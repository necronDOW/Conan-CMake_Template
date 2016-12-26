#include "Heatmap.h"

Heatmap::Heatmap() { }

Heatmap::Heatmap(glProgram& program, Renderer* renderer, std::vector<std::string> vData)
{
	Plane* p = new Plane(program, glm::vec3(0), glm::vec2(1), 100, 100, false);

	for (int i = 0; i < vData.size(); i++)
	{
		glm::vec3 v;
		AssetManager::FindValue(vData[i], 'X', v.x);
		AssetManager::FindValue(vData[i], 'Y', v.y);

		glm::vec3 scaledVector = glm::vec3(
			v.x != 0 ? p->GetSize().x / v.x : v.x,
			v.y != 0 ? p->GetSize().y / v.y : v.y, 
			0);

		p->ClampToPlane(scaledVector);
	}

	p->Initialize();
	renderer->AddToRender(p);
}