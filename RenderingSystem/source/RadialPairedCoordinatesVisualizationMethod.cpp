#include "LotsOfLines/RadialPairedCoordinatesVisualizationMethod.hpp"
#include <algorithm>

using namespace LotsOfLines;

bool RadialPairedCoordinatesVisualizationMethod::generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options)
{
	unsigned int lineIdx = 0;
	unsigned int vectorSize = 0;

	// Get draw option
	bool drawSequentially = options.getBool(DRAW_SEQUENTIALLY);

	for (auto iter = dataSet->iterator(); iter.hasNext(); iter++)
	{
		lineIdx++;

		const Vector& vec = iter.vector();
		vectorSize = vec.size();
		for (unsigned int x = 1; x < vec.size(); x += 2)
		{
			Vertex v = (x == 1) ?
				Vertex((float)vec[x - 1], (float)vec[x]) :
				Vertex((float)(vec[0] + vec[x - 1]), (float)(vec[1] + vec[x]));
			v.dataClassIndex = iter.classIndex();
			v.flags = 0;
			verticesOut.push_back(v);
			// If single left over vector
			if (x == vectorSize - 2)
			{
				lineIdx++;
				// Or (vec[x + 1], 0)
				v.x = (float)vec[x + 1];
				v.y = (float)vec[x + 1];
				verticesOut.push_back(v);
			}
		}
	}

	//Generate indices for lines
	unsigned int numVectors = dataSet->vectorCount();
	for (unsigned int baseIndex = 0; baseIndex < numVectors; ++baseIndex)
	{
		for (unsigned int i = 1, j = 0; i < vectorSize; ++i)
		{
			if (drawSequentially)
			{
				if ((i + (baseIndex * vectorSize)) % ((int)round(vectorSize / 2.0)) != 0) {
					indicesOut.push_back(i + (baseIndex * vectorSize) - 1);
					indicesOut.push_back(i + (baseIndex * vectorSize));
				}				
			} 
			else
			{
				if ((i + (baseIndex * vectorSize)) % ((int)round(vectorSize / 2.0)) == 0) {
					j += vectorSize / 2;
				}
				indicesOut.push_back(j + (baseIndex * vectorSize));
				indicesOut.push_back(i + (baseIndex * vectorSize));
			}
		}
	}

	return true;
}