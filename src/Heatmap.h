#ifndef heatmap_h_defined
#define heatmap_h_defined

#include "DrawableBase.h"

class Heatmap : public DrawableBase
{
	public:
		Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, bool initialize = true);
		Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, glm::vec2 minVector, glm::vec2 maxVector, bool initialize = true);

	protected:
		Heatmap();
		void CreateVertices(glm::vec2 size, glm::vec2 cellSize);
		void CreateElements(glm::vec2 size);
		virtual void MainDraw();
		void CalculateBounds(glm::vec2* vData, unsigned int vSize, glm::vec2 &minOut, glm::vec2 &maxOut);
		glm::vec2 CalculateDivisions(glm::vec2 min, glm::vec2 max, int minimumDivisions, glm::vec2 &outCellDimensions);
};

#endif