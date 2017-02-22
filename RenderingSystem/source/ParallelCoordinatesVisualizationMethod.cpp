#include "LotsOfLines/ParallelCoordinatesVisualizationMethod.hpp"

using namespace LotsOfLines;

bool ParallelCoordinatesVisualizationMethod::generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options)
{
	float colors[][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};

	unsigned int lineIdx = 0;
	unsigned int vectorSize = 0;

	//Get options
	bool fitToScreenHorizontal = options.getBool(FIT_TO_SCREEN_HORIZONTAL);
	double axisSpacing = options.getDouble(AXIS_SPACING);

	for (auto iter = dataSet->iterator(); iter.hasNext(); iter++)
	{
		lineIdx++;

		//Generate vertices to draw vector as line
		const Vector& vec = iter.vector();
		vectorSize = vec.size();
		for (unsigned int x = 0; x < vec.size(); ++x)
		{
			//Scale to 2 screen units if fit to screen is enabled, otherwise just use the requested spacing
			float interval = 2.0f / ((float)vectorSize - 1);
			if (!fitToScreenHorizontal)
			{
				interval = std::fmax(interval, axisSpacing);
			}

			Vertex v(-1.0f + (float)x * interval, (float)vec[x]);
			v.r = colors[iter.classIndex()][0];
			v.g = colors[iter.classIndex()][1];
			v.b = colors[iter.classIndex()][2];
			v.lineIndex = lineIdx;
			verticesOut.push_back(v);
		}
	}

	//Generate indices for lines
	unsigned int numVectors = dataSet->vectorCount();
	for (unsigned int baseIndex = 0; baseIndex < numVectors; ++baseIndex)
	{
		for (unsigned int i = 1; i < vectorSize; ++i)
		{
			indicesOut.push_back(i + (baseIndex * vectorSize) - 1);
			indicesOut.push_back(i + (baseIndex * vectorSize));
		}
	}

	return true;
}