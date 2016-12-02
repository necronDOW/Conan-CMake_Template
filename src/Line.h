#ifndef line_h_defined
#define line_h_defined

#include "DrawableBase.h"

class Line : protected DrawableBase
{
	public:
		Line(glProgram* program, glm::vec3 start, glm::vec3 end);
		void InitializeVertexBuffer();
		void Draw();

	protected:
		Line() { }
};

#endif