#ifndef trajectory_h_defined
#define trajectory_h_defined

#include "Arrow.h"
#include "Renderer.h"

class Trajectory : public DrawableBase
{
	public:
		Trajectory(glProgram& program, glm::vec2* vData, unsigned int vSize);
		void Update(float deltaTime);

	protected:
		Trajectory();
		virtual void MainDraw();
		glm::vec3 RandomColor();
};

#endif