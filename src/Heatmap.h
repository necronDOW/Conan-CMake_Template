#ifndef heatmap_h_defined
#define heatmap_h_defined

#include "DrawableBase.h"

class Histogram
{
	private:
		float* _data;
		int _sizeX, _sizeY;
		glm::vec2 _midCell;
		float _maxValue;

	public:
		Histogram() { }
		Histogram(unsigned int sizeX, unsigned int sizeY, glm::vec2 midCell)
		{
			_sizeX = sizeX;
			_sizeY = sizeY;
			_midCell = midCell;

			_data = new float[GetSize()];
			for (int i = 0; i < (GetSize()); i++)
				_data[i] = 0.0f;
		}

		void CalculateMaxValue()
		{
			for (int i = 0; i < GetSize(); i++)
			{
				if (_data[i] > _maxValue)
					_maxValue = _data[i];
			}
		}

		void AddToValue(unsigned int index, float value)
		{
			if (index < GetSize())
				_data[index] += value;
		}
		void AddToValue(unsigned int x, unsigned int y, float value)
		{
			if (x < _sizeX && y < _sizeY)
				_data[(_sizeX * y) + x] += value;
		}

		float GetValue(unsigned int index)
		{
			if (index < GetSize())
				return _data[index];
			else return -1.0f;
		}
		float GetValue(unsigned int x, unsigned int y)
		{
			if (x < _sizeX && y < _sizeY)
				return _data[(_sizeX * y) + x];
			else return -1.0f;
		}
		glm::vec2 GetMidCell() { return _midCell; }
		int GetSize() { return _sizeX * _sizeY;  }
		float GetMaxValue() { return _maxValue; }
};

class Heatmap : public DrawableBase
{
	public:
		Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, bool initialize = true);
		Heatmap(glProgram& program, glm::vec2* vData, unsigned int vSize, unsigned int minimumDivisions, glm::vec2 minVector, glm::vec2 maxVector, bool initialize = true);

		void AddPositions(glm::vec2* vData, unsigned int vSize);

	protected:
		Heatmap();
		void CreateVertices();
		void CreateElements();
		virtual void MainDraw();
		void CalculateBounds(glm::vec2* vData, unsigned int vSize, glm::vec2 &minOut, glm::vec2 &maxOut);
		glm::vec2 CalculateDivisions(glm::vec2 min, glm::vec2 max, int minimumDivisions, glm::vec2 &outCellDimensions);
		void CreateHistogram(glm::vec2* vData, unsigned int vSize);
		glm::vec3 GetColor(float t);
		glm::vec3 GetCellColor(int index);
		void ColorCell(int index, glm::vec3 color);
		glm::vec3 GenerateRandomColor();

		float _borderWidth = 0.2f;
		float maxHistogramValue = -1.0f;
		glm::vec2 _size, _cellSize;
		glm::vec3 _lowColor;
		glm::vec3 _midColor;
		glm::vec3 _hiColor;
		Histogram* _histogram;
};

#endif