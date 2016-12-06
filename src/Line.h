#ifndef line_h_defined
#define line_h_defined

#include "DrawableBase.h"

class Line : public DrawableBase
{
	public:
		Line(glProgram& program, glm::vec3 start, glm::vec3 end, bool initialize = true);
		Line(glProgram& program, glm::vec3 start, glm::vec3 end, glm::vec3 color, bool initialize = true);

	protected:
		Line();
		virtual void MainDraw();
};

#endif