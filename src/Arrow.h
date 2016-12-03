#ifndef arrow_h_defined
#define arrow_h_defined

#include "Line.h"

class Arrow : public Line
{
	public:
		Arrow(glProgram* program, glm::vec3 start, glm::vec3 end, glm::vec3 colorRGB);
		void InitializeVertexBuffer();
		void Draw();

	protected:
		Arrow() { }
};

#endif
