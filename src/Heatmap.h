#ifndef heatmap_h_defined
#define heatmap_h_defined

#include "Plane.h"
#include "Renderer.h"
#include "Trajectory.h"

class Heatmap
{
	public:
		Heatmap(glProgram& program, Renderer* renderer, glm::vec2* &vData, int vSize, Trajectory* trajectory);

	private:
		Heatmap();
		void ClampToPlane(glm::vec2& position, Plane* p);
};

#endif