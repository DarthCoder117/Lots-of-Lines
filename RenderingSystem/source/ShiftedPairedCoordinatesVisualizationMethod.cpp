#include "LotsOfLines/ShiftedPairedCoordinatesVisualizationMethod.hpp"
#include <algorithm>

using namespace LotsOfLines;

// Shifted paired coordinates with steps
bool ShiftedPairedCoordinatesVisualizationMethod::generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options)
{
	float colors[][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};

	unsigned int lineIdx = 0;
	unsigned int vectorSize = 0;

	// Get distance between first two pair X values
	// This is semi-hardcoded shift value, though might be final variant
	const Vector& firstVec = dataSet->getVectors(*dataSet->getClasses().begin())[0];
	double distance = firstVec[2] ? abs(firstVec[0] - firstVec[2]) : 0;
	
	for (auto iter = dataSet->iterator(); iter.hasNext(); iter++)
	{
		lineIdx++;

		double shift = 0.0f;
		const Vector& vec = iter.vector();
		vectorSize = vec.size();
		for (unsigned int x = 1; x < vec.size(); x += 2)
		{
			Vertex v((float)(vec[x - 1] + shift), (float)(vec[x] + shift));
			v.r = colors[iter.classIndex()][0];
			v.g = colors[iter.classIndex()][1];
			v.b = colors[iter.classIndex()][2];
			v.lineIndex = lineIdx;
			verticesOut.push_back(v);
			shift += distance;
			// If single left over vector
			if (x == vectorSize - 2)
			{
				lineIdx++;
				// Or (vec[x + 1], 0)
				v.x = (float)(vec[x + 1] + shift);
				v.y = (float)(vec[x + 1] + shift);
				v.lineIndex = lineIdx;
				verticesOut.push_back(v);
			}
		}
	}

	//Generate indices for lines
	unsigned int numVectors = dataSet->vectorCount();
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