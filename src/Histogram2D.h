#ifndef histogram2d_h_defined
#define histogram2d_h_defined

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class DataSet;
class Heatmap;

class Histogram2D
{
	public:
		Histogram2D(DataSet* dataSet, Heatmap* heatmap, int minimumBound);

		float GetValue(unsigned int index);

		glm::vec2 GetSize();
		unsigned int GetLength();
		float GetMin();
		float GetMax();

	private:
		Histogram2D();

		void Initialize(DataSet* dataSet, Heatmap* heatmap);
		void CalculateBounds(DataSet* dataSet, unsigned int minimumBound, glm::vec2& outCellSize);
		void CalculateMinMax();

		float* _bins;
		unsigned int _sizeX, _sizeY;
		float _maxValue, _minValueExZero;
};

#endif