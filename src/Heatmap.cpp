#include "Heatmap.h"

Heatmap::Heatmap() { }

Heatmap::Heatmap(glProgram& program, Renderer* renderer, glm::vec2* &vData, int vSize, Trajectory* trajectory)
{
	Plane* p = new Plane(program, glm::vec2(0), trajectory->GetRange() * 2.0f, glm::vec3(0.1f), 100, 100, -0.001f, false);



	p->Initialize();
	renderer->AddToRender(p);
}

void Heatmap::ClampToPlane(glm::vec2& position, Plane* p)
{
	position.x = (int)((position.x / p->GetCellSize().x) + 0.5f);
	position.y = (int)((position.y / p->GetCellSize().y) + 0.5f);
}