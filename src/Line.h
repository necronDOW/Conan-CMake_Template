#ifndef line_h_defined
#define line_h_defined

#include "DrawableBase.h"

class Line : public DrawableBase
{
	public:
		Line(glProgram* program, glm::vec3 start, glm::vec3 end, glm::vec3 colorRGB);
		void InitializeVertexBuffer();
		virtual void Draw();

	protected:
		Line() { }
};

#endif