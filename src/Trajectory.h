#ifndef trajectory_h_defined
#define trajectory_h_defined

#include "Arrow.h"
#include "Renderer.h"

class Trajectory
{
	public:
		Trajectory(glProgram& program, Renderer* renderer, glm::vec2* &vData, int vSize);
		Trajectory(glProgram& program, Renderer* renderer, glm::vec2* &vData, int vSize, std::vector<std::string> cData);
		void Update();

		glm::vec2 GetOffset();
		glm::vec2 GetLow();
		glm::vec2 GetHi();
		glm::vec2 GetRange();

	private:
		Trajectory();
		void AssignBounds(glm::vec2 value);
		void UpdateBounds(glm::vec2 check);

		glm::vec2 _offset;
		glm::vec2 _low, _hi;
		glm::vec2 _scale;
};

#endif