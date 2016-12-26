#ifndef heatmap_h_defined
#define heatmap_h_defined

#include "Plane.h"
#include "Renderer.h"

class Heatmap
{
	public:
		Heatmap(glProgram& program, Renderer* renderer, std::vector<std::string> vData);

	private:
		Heatmap();
};

#endif