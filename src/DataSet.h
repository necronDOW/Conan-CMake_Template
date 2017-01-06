#ifndef dataset_h_defined
#define dataset_h_defined

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Trajectory.h"
#include "AssetManager.h"

class Histogram2D;
class Heatmap;

class DataSet
{
	public:
		DataSet(glProgram &program, std::string fileDir, Heatmap* heatmap, float scale);
		~DataSet();

		glm::vec2 Get(unsigned int index);

		unsigned int GetLength();
		glm::vec2 GetMax();
		glm::vec2 GetMin();
		float GetBorderWidth();

	private:
		DataSet();

		void UpdateMinMax(glm::vec2 check);
		bool ParseValue(std::string str, char id, float &out);
		bool IsNum(std::string str);

		glm::vec2* _data;
		glm::vec2 _max, _min = glm::vec2(99999.0f);
		unsigned int _length;
		float _scale;
		Trajectory* _trajectory;
		Heatmap* _heatmap;
};

#endif