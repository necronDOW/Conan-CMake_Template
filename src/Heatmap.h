#ifndef heatmap_h_defined
#define heatmap_h_defined

#include "DrawableBase.h"

class Heatmap : public DrawableBase
{
	public:
		Heatmap(glProgram& program, glm::vec2* &vData, unsigned int vSize, bool initialize = true);

	private:
		Heatmap();
		virtual void MainDraw();
};

#endif