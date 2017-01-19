#include "LotsOfLines/ParallelCoordinatesVisualizationMethod.hpp"

using namespace LotsOfLines;

bool ParallelCoordinatesVisualizationMethod::generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut)
{
	unsigned int numVectors = 0;
	unsigned int vectorSize = 0;

	//Iterate over each data class and generate lines
	unsigned int classIdx = 0;

	float colors[][3] = {
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f}
	};

	const Vector& maxValues = dataSet->getMaxValues();
	const Vector& minValues = dataSet->getMinValues();

	//Generate vertices for each data class
	for (auto dataClass : dataSet->getClasses())
	{
		VectorClass vectors = dataSet->getVectors(dataClass);
		numVectors += vectors.size();
		for (unsigned int i = 0; i < vectors.size(); ++i)
		{
			//Generate vertices to draw vector as line
			const Vector& vec = vectors[i];
			vectorSize = vec.size();
			for (unsigned int x = 0; x < vec.size(); ++x)
			{
				float interval = 2.0f / ((float)vectorSize - 1);//Screen is 2 screen units wide

				//Normalize data
				double val = vec[x];
				double max = maxValues[x];
				double min = maxValues[x];
				double normalized = (val - min) / (max - min);

				Vertex v(-1.0f + (float)x * interval, (float)vec[x]);
				v.r = colors[classIdx][0];
				v.g = colors[classIdx][1];
				v.b = colors[classIdx][2];
				verticesOut.push_back(v);
			}
		}

		classIdx++;
	}

	//Generate indices for lines
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