#ifndef line_h_defined
#define line_h_defined

#include "DrawableBase.h"

class Line : public DrawableBase
{
	public:
		Line(glProgram& program, glm::vec2 start, glm::vec2 end, bool initialize = true);
		Line(glProgram& program, glm::vec2 start, glm::vec2 end, glm::vec3 color, bool initialize = true);

	protected:
		Line();
		virtual void MainDraw();
};

#endif