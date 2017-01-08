#ifndef Heatmap_h_defined
#define Heatmap_h_defined

#include "DrawableBase.h"
#include "VisualHelper.h"

class Histogram2D;
class DataSet;

class Heatmap : public DrawableBase
{
	public:
		Heatmap();
		Heatmap(glProgram &program, DataSet* dataSet);
		~Heatmap();
		void OffsetMidCell(glm::vec2 value);
		bool IsInitialized();
		glm::vec2 GetSize();
		void AddHistogram(Histogram2D* histogram);
		void ApplyLastHistogram();
		void ApplyHistogram(Histogram2D* histogram);

		glm::vec2 GetMidCell();
		float GetBorderWidth();

		glm::vec2 cellSize;

	protected:
		void CreateVertices();
		void CreateElements();
		virtual void MainDraw();
		void PromptColorChoice();
		glm::vec3 GetColor(float t);
		void ColorCell(int index, glm::vec3 color);
		glm::vec3 GetCellColor(int index);

		glm::vec2 _midCell;
		std::vector<Histogram2D*> _histograms;
		glm::vec3 _lowColor;
		glm::vec3 _midColor;
		glm::vec3 _hiColor;
		float _borderWidth = 0.2f;
		unsigned int _histogramsVisualised = 0;
};

#endif