#ifndef Heatmap_h_defined
#define Heatmap_h_defined

#include "DrawableBase.h"
#include "VisualHelper.h"

class Histogram2D;
class DataSet;

struct HistogramContainer
{
	Histogram2D* histogram;
	glm::vec3 color;
	bool visualised;

	HistogramContainer(Histogram2D* h)
	{
		histogram = h;
		color = glm::vec3(-1);
		visualised = false;
	}

	bool ColorApplied()
	{
		return !(color == glm::vec3(-1));
	}
};

class Heatmap : public DrawableBase
{
	public:
		Heatmap();
		Heatmap(glProgram &program, DataSet* dataSet);
		~Heatmap();
		void OffsetMidCell(glm::vec2 value);
		bool IsInitialized();
		glm::vec2 GetSize();
		unsigned int AddHistogram(Histogram2D* histogram, glm::vec3 color);
		void ApplyHistogram(unsigned int index);
		void SubtractHistogram(unsigned int index);
		HistogramContainer* GetHistogramContainer(int index);

		glm::vec2 GetMidCell();
		float GetBorderWidth();

		glm::vec2 cellSize;

	protected:
		void CreateVertices();
		void CreateElements();
		virtual void MainDraw();
		glm::vec3 GetColor(glm::vec3 hiColor, glm::vec3 midColor, glm::vec3 lowColor, float t);
		void ColorCell(int index, glm::vec3 color);
		glm::vec3 GetCellColor(int index);
		unsigned int HeatmapsVisualised();

		glm::vec2 _midCell;
		glm::vec2 _baseDimensions;
		std::vector<HistogramContainer*> _histograms;
		float _borderWidth = 0.45f;
};

#endif