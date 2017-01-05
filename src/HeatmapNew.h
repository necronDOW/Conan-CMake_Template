#ifndef heatmapnew_h_defined
#define heatmapnew_h_defined

#include "DrawableBase.h"

class Histogram2D;
class DataSet;

class HeatmapNew : public DrawableBase
{
	public:
		HeatmapNew();
		HeatmapNew(glProgram &program, DataSet* dataSet);
		void OffsetMidCell(glm::vec2 value);
		bool IsInitialized();
		glm::vec2 GetSize();
		void AddHistogram(Histogram2D* histogram);

		glm::vec2 GetMidCell();
		float GetBorderWidth();

		glm::vec2 cellSize;

	protected:
		void CreateVertices();
		void CreateElements();
		virtual void MainDraw();
		glm::vec3 GetColor(float t);
		void ColorCell(int index, glm::vec3 color);

		glm::vec2 _midCell;
		std::vector<Histogram2D*> _histograms;
		glm::vec3 _lowColor;
		glm::vec3 _midColor;
		glm::vec3 _hiColor;
		float _borderWidth = 0.2f;
};

#endif