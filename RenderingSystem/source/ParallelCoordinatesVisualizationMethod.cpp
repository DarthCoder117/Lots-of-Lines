#include "LotsOfLines/ParallelCoordinatesVisualizationMethod.hpp"

using namespace LotsOfLines;

bool ParallelCoordinatesVisualizationMethod::generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<float3>& verticesOut, std::vector<unsigned int>& indicesOut)
{
	//Iterate over each data class and generate lines
	for (auto dataClass : dataSet->getClasses())
	{
		VectorClass vectors = dataSet->getVectors(dataClass);
		for (unsigned int i = 0; i < vectors.size(); ++i)
		{
			//Generate vertices to draw vector as line
			const Vector& vec = vectors[i];
			for (unsigned int x = 0; x < vec.size(); ++x)
			{
				verticesOut.push_back(float3(-1.0f + ((float)x) * 0.675, (vec[x] / 4.0f) - 1.0f, 0.0f));
			}

			//Generate indices for line
			unsigned int baseIndex = i * vec.size();
			if (baseIndex != 0) baseIndex++;
			unsigned int lastIndex = 0;

			indicesOut.push_back(baseIndex);
			for (unsigned int idx = 0; idx < vec.size() - 1; ++idx)
			{
				lastIndex = baseIndex + idx + 1;
				indicesOut.push_back(lastIndex);
				indicesOut.push_back(lastIndex);
			}
			indicesOut.push_back(lastIndex + 1);
		}
	}

	return true;
}