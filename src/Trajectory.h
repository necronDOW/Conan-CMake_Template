#ifndef trajectory_h_defined
#define trajectory_h_defined

#include "Arrow.h"
#include "Renderer.h"

class Trajectory
{
	public:
		Trajectory(glProgram& program, glm::vec2* vData, unsigned int vSize);
		void Update(float deltaTime);

		glm::vec2 GetLow();
		glm::vec2 GetHi();
		glm::vec2 GetRange();

	private:
		Trajectory();
		void UpdateBounds(glm::vec2 check);

		glm::vec2 _low, _hi;
		std::vector<Arrow*> _segments;
};

#endif