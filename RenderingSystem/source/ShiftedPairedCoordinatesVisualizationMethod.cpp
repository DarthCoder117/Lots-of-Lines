#include "LotsOfLines/ShiftedPairedCoordinatesVisualizationMethod.hpp"
#include <algorithm>

using namespace LotsOfLines;

// Shifted paired coordinates with steps
bool ShiftedPairedCoordinatesVisualizationMethod::generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options)
{
	unsigned int lineIdx = 0;
	unsigned int vectorSize = 0;

	// Read in options
	const bool autoStep = options.getBool(AUTO_STEP),
		horizontal = options.getBool(HORIZONTAL),
		nonIntersecting = options.getBool(NON_INTERSECTING),
		collapsed = options.getBool(COLLAPSED),
		increasing = options.getBool(INCREASING);

	// Get distance between first two pair X values
	// This is semi-hardcoded shift value, though might be final variant
	const Vector& firstVec = dataSet->getVectors(*dataSet->getClasses().begin())[0];
	double distance = options.getDouble(STEP);
	Vector shiftVec = Vector();

	// Another potential parameter
	unsigned int selectedLine = 0;

	// Add a normal step
	if (autoStep)
	{
		distance = firstVec[2] ? abs(firstVec[0] - firstVec[2]) : 0;
		double shift = 0.0;
		// Assign values to shift vector
		for (unsigned int i = 0; i < firstVec.size(); i++)
		{
			shiftVec.push_back(shift);
			if (i % 2 == 1) shift += distance;
		}
	}
	else if (horizontal)
	{
		// Merely using first vec here for ease of test
		for (unsigned int i = 0; i < firstVec.size(); i++)
		{
			if (i % 2 == 1 && i > 2) shiftVec.push_back(firstVec[1] - firstVec[i]);
			else shiftVec.push_back(0);
		}
	}
	else if (collapsed)
	{
		// Using first vec again
		for (unsigned int i = 0; i < firstVec.size(); i++)
		{
			if (i % 2 == 0 && i > 1) shiftVec.push_back(firstVec[0] - firstVec[i]);
			else if (i % 2 == 1 && i > 2) shiftVec.push_back(firstVec[1] - firstVec[i]);
			else shiftVec.push_back(0);
		}
	}
	else // Custom step
	{
		double shift = 0.0;
		// Assign distance to shift vector
		for (unsigned int i = 0; i < firstVec.size(); i++)
		{
			shiftVec.push_back(shift);
			if (i % 2 == 1) shift += distance;
		}
	}

	// Iterate through dataset
	for (auto iter = dataSet->iterator(); iter.hasNext(); iter++)
	{
		lineIdx++;

		double shift = 0.0f;
		const Vector& vec = iter.vector();
		vectorSize = vec.size();
		for (unsigned int x = 1; x < vec.size(); x += 2)
		{
			Vertex v((float)(vec[x - 1] + shiftVec[x - 1]), (float)(vec[x] + shiftVec[x]));
			v.dataClassIndex = iter.classIndex();
			v.lineIndex = lineIdx;
			verticesOut.push_back(v);
			// If single left over vector
			if (x == vectorSize - 2)
			{
				lineIdx++;
				// Or (vec[x + 1], 0)
				v.x = (float)(vec[x + 1] + shiftVec[x + 1]);
				v.y = (float)(vec[x + 1] + shiftVec[x + 1]);
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