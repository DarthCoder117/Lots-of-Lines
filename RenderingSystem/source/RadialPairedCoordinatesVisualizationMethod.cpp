#include "LotsOfLines/RadialPairedCoordinatesVisualizationMethod.hpp"
#include <algorithm>

using namespace LotsOfLines;

bool RadialPairedCoordinatesVisualizationMethod::generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options)
{
	unsigned int numVectors = 0;
	unsigned int vectorSize = 0;
	const int DRAW_METHOD = 1;

	//Iterate over each data class and generate lines
	unsigned int classIdx = 0;

	float colors[][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};

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

			for (unsigned int x = 1; x < vec.size(); x += 2)
			{
				Vertex v = (x == 1) ?
					Vertex((float)vec[x - 1], (float)vec[x]) :
					Vertex((float)(vec[0] + vec[x - 1]), (float)(vec[1] + vec[x]));
				v.r = colors[classIdx][0];
				v.g = colors[classIdx][1];
				v.b = colors[classIdx][2];
				verticesOut.push_back(v);
				// If single left over vector
				if (x == vectorSize - 2)
				{
					//Or (vec[x + 1], 0)
					v = Vertex((float)vec[x + 1], (float)vec[x + 1]);
					verticesOut.push_back(v);
					vectorSize++;
				}
			}
		}

		classIdx++;
	}
	//Generate indices for lines
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