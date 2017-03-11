#include "RenderingSystem/ShiftedPairedCoordinatesVisualizationMethod.hpp"
#include <algorithm>

using namespace LotsOfLines;

// Shifted paired coordinates with steps
bool ShiftedPairedCoordinatesVisualizationMethod::generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, RenderingSystem* driver, const VisualizationOptions& options)
{
	unsigned int lineIdx = 0;
	unsigned int selectedLineIdx = 1;
	unsigned int vectorSize = 0;

	// Read in options
	const bool autoStep = options.getBool(AUTO_STEP),
		horizontal = options.getBool(HORIZONTAL),
		collapsed = options.getBool(COLLAPSED);

	// Get distance between first two pair X values
	// This is semi-hardcoded shift value, though might be final variant
	Vector firstVec = dataSet->getVector(0);
	// Set selected vector as first in selection or if no selection, the first total
	const std::set<unsigned int> selected = driver->getSelection();
	Vector selectedVec = 
		(selected.size() > 0 && *selected.begin() - 1 < dataSet->vectorCount()) ?
		dataSet->getVector(*selected.begin() - 1) : firstVec;
	
	// Select first line if no selected line in range
	if (selected.size() == 0 || *selected.begin() - 1 >= dataSet->vectorCount())
		driver->selectLine(1);
	// Otherwise store selected line index
	else
		selectedLineIdx = *selected.begin();

	// Take into account odd amount of variables
	if (firstVec.size() % 2 != 0)
	{
		// Add an extra variable at end
		firstVec.push_back(firstVec.at(firstVec.size() - 1));
		selectedVec.push_back(selectedVec.at(selectedVec.size() - 1));
	}

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
	if (horizontal)
	{
		// Merely using first vec here for ease of test
		for (unsigned int i = 0; i < selectedVec.size(); i++)
		{
			if (i % 2 == 1 && i > 2) shiftVec[i] += (selectedVec[1] - selectedVec[i]);
			// else add 0
		}
	}
	else if (collapsed)
	{
		// Using first vec again
		for (unsigned int i = 0; i < selectedVec.size(); i++)
		{
			if (i % 2 == 0 && i > 1) shiftVec[i] += (selectedVec[0] - selectedVec[i]);
			else if (i % 2 == 1 && i > 2) shiftVec[i] += (selectedVec[1] - selectedVec[i]);
			// else add 0
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
			Vertex v((float)(vec[x - 1] + shiftVec[x - 1]), (float)(vec[x] + shiftVec[x]), lineIdx);
			v.dataClassIndex = iter.classIndex();
			v.flags = (selectedLineIdx == lineIdx) ? EVSF_DRAW_POINT : 0;
			verticesOut.push_back(v);
			// If single left over vector
			if (x == vectorSize - 2)
			{
				// Or (vec[x + 1], 0)
				v.x = (float)(vec[x + 1] + shiftVec[x + 1]);
				v.y = (float)(vec[x + 1] + shiftVec[x + 2]);
				v.flags = (selectedLineIdx == lineIdx) ? EVSF_DRAW_POINT : 0;
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
			if ((i + (baseIndex * vectorSize)) % ((int)round(vectorSize / 2.0)) != 0) {
				indicesOut.push_back(i + (baseIndex * vectorSize) - 1);
				indicesOut.push_back(i + (baseIndex * vectorSize));
			}
		}
	}

	return true;
}
