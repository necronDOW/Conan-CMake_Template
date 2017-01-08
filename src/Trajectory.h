#ifndef trajectory_h_defined
#define trajectory_h_defined

#include "Renderer.h"

class Trajectory : public DrawableBase
{
	public:
		Trajectory(glProgram& program, glm::vec2* vData, unsigned int vSize, glm::vec3 color);
		void Update(float deltaTime);

	protected:
		Trajectory();
		virtual void MainDraw();
		void CreateArrow(glm::vec3 start, glm::vec3 end, float t, unsigned int index);

		glm::vec3 _colorLow, _colorHi;
		float _maxLen;
};

#endif