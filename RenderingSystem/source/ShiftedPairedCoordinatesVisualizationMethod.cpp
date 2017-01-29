#include "LotsOfLines/ShiftedPairedCoordinatesVisualizationMethod.hpp"
#include <algorithm>

using namespace LotsOfLines;

// Shifted paired coordinates with steps
bool ShiftedPairedCoordinatesVisualizationMethod::generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut)
{
	unsigned int numVectors = 0;
	unsigned int vectorSize = 0;

	//Iterate over each data class and generate lines
	unsigned int classIdx = 0;

	float colors[][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};

	// Get boundaries based off of first vector
	const Vector& firstVec = dataSet->getVectors(*dataSet->getClasses().begin())[0];
	auto max = std::max_element(firstVec.begin(), firstVec.end());
	auto min = std::min_element(firstVec.begin(), firstVec.end());
	float diff = *max - *min;
	float width = 2.0f;

	// Scaling
	float interval = width / diff;
	// Shifting
	float shift[2] = {
		firstVec[0] * interval * -1,
		firstVec[1] ? firstVec[1] * interval * -1 : 0
	};
	double distance = firstVec[2] ? abs(firstVec[0] - firstVec[2]) : 0;
	//Generate vertices for each data class
	for (auto dataClass : dataSet->getClasses())
	{
		VectorClass vectors = dataSet->getVectors(dataClass);
		numVectors += vectors.size();

		for (unsigned int i = 0; i < vectors.size(); ++i)
		{
			double step = 0.0f;
			//Generate vertices to draw vector as line
			const Vector& vec = vectors[i];
			vectorSize = vec.size();
			for (unsigned int x = 1; x < vec.size(); x += 2)
			{
				Vertex v((vec[x - 1] + step) * interval + shift[0], (vec[x] + step) * interval + shift[1]);
				v.r = colors[classIdx][0];
				v.g = colors[classIdx][1];
				v.b = colors[classIdx][2];
				verticesOut.push_back(v);
				step += distance;
				// If single left over vector
				if (x == vectorSize - 2)
				{
					//Or (vec[x + 1], 0)
					v = Vertex((vec[x + 1] + step) * interval + shift[0], (vec[x + 1] + step) * interval + shift[1]);
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
		for (unsigned int i = 1; i < vectorSize; ++i)
		{
			if ((i + (baseIndex * vectorSize)) % (vectorSize / 2) != 0) {
				indicesOut.push_back(i + (baseIndex * vectorSize) - 1);
				indicesOut.push_back(i + (baseIndex * vectorSize));
			}
		}
	}

	return true;
}