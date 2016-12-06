#ifndef arrow_h_defined
#define arrow_h_defined

#include "Line.h"

class Arrow : public Line
{
	public:
		Arrow(glProgram& program, glm::vec3 start, glm::vec3 end, bool initialize = true);
		Arrow(glProgram& program, glm::vec3 start, glm::vec3 end, glm::vec3 color, bool initialize = true);

	protected:
		Arrow();
		virtual void MainDraw();
		virtual void CreateHead(glm::vec3 start, glm::vec3 end, float t, glm::vec3 color = glm::vec3(1.0f));
};

#endif