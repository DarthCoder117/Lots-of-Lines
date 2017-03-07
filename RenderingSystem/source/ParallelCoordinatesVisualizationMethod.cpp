#include "LotsOfLines/ParallelCoordinatesVisualizationMethod.hpp"

using namespace LotsOfLines;

bool ParallelCoordinatesVisualizationMethod::generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options)
{
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
		double interval = 2.0 / ((double)vectorSize - 1);
		for (unsigned int x = 0; x < vec.size(); ++x)
		{
			//Scale to 2 screen units if fit to screen is enabled, otherwise just use the requested spacing
			if (!fitToScreenHorizontal)
			{
				interval = std::fmax(interval, axisSpacing);
			}

			Vertex v(-1.0f + (float)(x * interval), (float)vec[x], lineIdx);
			v.dataClassIndex = iter.classIndex();
			v.flags = 0;
			verticesOut.push_back(v);
		}

		m_scrollLimit = ((float)interval * ((float)vectorSize - 1.0f)) - 2.0f;
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