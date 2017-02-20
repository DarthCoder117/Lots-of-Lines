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

	// Hard Coded Parameters
	enum ShiftedPairedCoordinatesType {
		AUTO_STEP,
		CUSTOM_STEP,
		HORIZONTAL_LINE,
		NON_INTERSECTING,
		HORIZONTAL_NON_INTERSECTING,
		COLLAPSED,
		INCREASING
	};

	// Get distance between first two pair X values
	// This is semi-hardcoded shift value, though might be final variant
	const Vector& firstVec = dataSet->getVectors(*dataSet->getClasses().begin())[0];
	double distance;
	Vector shiftVec = Vector();
	// Or just hard:
	// double distance = 1.0;

	// Another parameter
	unsigned int selectedLine = 0;
	ShiftedPairedCoordinatesType type = COLLAPSED;
	const Vector& selectedVec = dataSet->getVectors(*dataSet->getClasses().begin())[0];

	switch (type)
	{
	case AUTO_STEP:
		distance = firstVec[2] ? abs(firstVec[0] - firstVec[2]) : 0;
		// Assign values to shift vector
		for (int i = 0; i < firstVec.size(); i++)
		{
			shiftVec.push_back(distance);
		}
		break;
	case CUSTOM_STEP:
		distance = 1.0;
		// Assign distance to shift vector
		for (int i = 0; i < firstVec.size(); i++)
		{
			shiftVec.push_back(distance);
		}
		break;
	case HORIZONTAL_LINE:
		// Merely using first vec here for ease of test
		for (int i = 0; i < selectedVec.size(); i++)
		{
			if (i % 2 == 0) shiftVec.push_back(selectedVec[0] - selectedVec[i]);
			else shiftVec.push_back(0);
		}
		break;
	case NON_INTERSECTING:
		break;
	case HORIZONTAL_NON_INTERSECTING:
		break;
	case COLLAPSED:
		for (int i = 0; i < firstVec.size(); i++)
		{
			if (i % 2 == 0) shiftVec.push_back(firstVec[0] - firstVec[i]);
			else shiftVec.push_back(firstVec[1] - firstVec[i]);
		}
		break;
	case INCREASING:
		break;
	default:
		distance = 0.0;
		// Assign distance to shift vector
		for (int i = 0; i < firstVec.size(); i++)
			shiftVec.push_back(distance);
		break;
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
			Vertex v((float)(vec[x - 1] + shift), (float)(vec[x] + shift));
			v.r = colors[iter.classIndex()][0];
			v.g = colors[iter.classIndex()][1];
			v.b = colors[iter.classIndex()][2];
			v.lineIndex = lineIdx;
			verticesOut.push_back(v);
			shift += shiftVec[x];
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