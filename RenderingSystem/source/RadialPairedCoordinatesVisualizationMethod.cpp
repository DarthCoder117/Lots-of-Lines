#include "LotsOfLines/RadialPairedCoordinatesVisualizationMethod.hpp"
#include <algorithm>

using namespace LotsOfLines;

bool RadialPairedCoordinatesVisualizationMethod::generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options)
{
	// Hardcoded draw method
	const int DRAW_METHOD = 1;
	float colors[][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};

	unsigned int lineIdx = 0;
	unsigned int vectorSize = 0;

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
			v.r = colors[iter.classIndex()][0];
			v.g = colors[iter.classIndex()][1];
			v.b = colors[iter.classIndex()][2];
			v.lineIndex = lineIdx;
			verticesOut.push_back(v);
			// If single left over vector
			if (x == vectorSize - 2)
			{
				lineIdx++;
				// Or (vec[x + 1], 0)
				v.x = (float)vec[x + 1];
				v.y = (float)vec[x + 1];
				v.lineIndex = lineIdx;
				verticesOut.push_back(v);
			}
		}
	}
	//Generate indices for lines
	for (unsigned int baseIndex = 0; baseIndex < numVectors; ++baseIndex)
	{
		for (unsigned int i = 1; i < vectorSize; ++i)
		{
			if ((i + (baseIndex * vectorSize)) % (vectorSize / 2) != 0) {
				indicesOut.push_back(i + (baseIndex * vectorSize) - 1);
				indicesOut.push_back(i + (baseIndex * vectorSize));
			}
		}
	}
	//Generate indices for lines
	unsigned int numVectors = dataSet->vectorCount();
	for (unsigned int baseIndex = 0; baseIndex < numVectors; ++baseIndex)
	{
		for (unsigned int i = 1, j = 0; i < vectorSize; ++i)
		{
			switch (DRAW_METHOD) {
			case 0:
				if ((i + (baseIndex * vectorSize)) % (vectorSize / 2) == 0) {
					j += vectorSize / 2;
				}
				indicesOut.push_back(j + (baseIndex * vectorSize));
				indicesOut.push_back(i + (baseIndex * vectorSize));
				break;
			case 1:
				if ((i + (baseIndex * vectorSize)) % (vectorSize / 2) != 0) {
					indicesOut.push_back(i + (baseIndex * vectorSize) - 1);
					indicesOut.push_back(i + (baseIndex * vectorSize));
				}
				break;
			}
		}
	}

	return true;
}