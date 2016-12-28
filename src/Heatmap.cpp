#include "Heatmap.h"

Heatmap::Heatmap() { }

Heatmap::Heatmap(glProgram& program, glm::vec2* &vData, unsigned int vSize, bool initialize)
	: DrawableBase(program, glm::vec3(-2.3f, 0, 0))
{
	glm::vec2 last;

	for (unsigned int i = 0; i < vSize; i++)
	{
		CreateVertex(glm::vec3(vData[i].x, vData[i].y, 0));
	}

	if (initialize)
		Initialize();
}

void Heatmap::MainDraw()
{
	glDrawArrays(GL_POINTS, 0, _vCount);
}