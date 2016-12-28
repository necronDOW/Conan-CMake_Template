#ifndef arrow_h_defined
#define arrow_h_defined

#include "Line.h"

class Arrow : public Line
{
	public:
		Arrow(glProgram& program, glm::vec2 start, glm::vec2 end, bool initialize = true);
		Arrow(glProgram& program, glm::vec2 start, glm::vec2 end, glm::vec3 color, bool initialize = true);

	protected:
		Arrow();
		virtual void MainDraw();
		virtual void CreateHead(glm::vec2 start, glm::vec2 end, float t, glm::vec3 color = glm::vec3(1.0f));

		float _arrowSize = 0.05f;
};

#endif