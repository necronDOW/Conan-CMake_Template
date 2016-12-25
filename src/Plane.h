#ifndef plane_h_defined
#define plane_h_defined

#include "DrawableBase.h"

class Plane : public DrawableBase
{
public:
	Plane(glProgram& program, glm::vec3 position, glm::vec2 dimensions, unsigned int sizeX = 1, unsigned int sizeY = 1, bool initialize = true);

protected:
	Plane();
	virtual void MainDraw();
};

#endif