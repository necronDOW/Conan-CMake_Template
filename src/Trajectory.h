#ifndef trajectory_h_defined
#define trajectory_h_defined

#include "Arrow.h"
#include "Renderer.h"

class Trajectory
{
	public:
		Trajectory(glProgram& program, Renderer* renderer, std::vector<std::string> vData);
		Trajectory(glProgram& program, Renderer* renderer, std::vector<std::string> vData, std::vector<std::string> cData);
		void Update();

	private:
		Trajectory();
		bool FindValue(std::string str, char id, float& out);
		bool IsNum(std::string str);
};

#endif