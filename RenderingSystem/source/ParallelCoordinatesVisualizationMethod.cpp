#include "LotsOfLines/ParallelCoordinatesVisualizationMethod.hpp"
#include <GL/glew.h>

using namespace LotsOfLines;

bool ParallelCoordinatesVisualizationMethod::generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, RenderingSystem* driver, const VisualizationOptions& options)
{
	unsigned int lineIdx = 0;
	unsigned int vectorSize = 0;
	double interval = 2.0 / 4.0;

	m_axes.clear();

	//Get options
	bool fitToScreenHorizontal = options.getBool(FIT_TO_SCREEN_HORIZONTAL);
	bool shifted = options.getBool(SHIFTED);
	double axisSpacing = options.getDouble(AXIS_SPACING);
	
	//Quick struct for storing vector and index
	typedef struct VectorPair {
		Vector vector;
		unsigned int index;
	} VectorPair;

	//Shift around this line
	Vector median;
	unsigned int medianLineIdx = 0;

	if (shifted) {
		//For median calculation
		std::multimap<const double, VectorPair> firstVariables;

		for (auto iter = dataSet->iterator(); iter.hasNext(); iter++)
		{
			const Vector& vec = iter.vector();
			VectorPair vector;
			vector.vector = vec;
			vector.index = iter.lineIndex();
			firstVariables.emplace(vec[0], vector);
		}

		// Get median vector
		size_t size = firstVariables.size();
		
		std::multimap<const double, VectorPair>::iterator iter = firstVariables.begin();
		// If even elements, get 1 of central elements. No need to be picky
		if (size % 2 == 0)
		{
			std::advance(iter, size / 2 - 1);
		}
		else
		{
			std::advance(iter, size / 2);
		}
		// Assign element
		median = iter->second.vector;
		medianLineIdx = iter->second.index;
	}

	for (auto iter = dataSet->iterator(); iter.hasNext(); iter++)
	{
		lineIdx++;

		//Generate vertices to draw vector as line
		const Vector& vec = iter.vector();
		vectorSize = vec.size();
		interval = 2.0 / ((double)vectorSize - 1);
		for (unsigned int x = 0; x < vec.size(); ++x)
		{
			//Scale to 2 screen units if fit to screen is enabled, otherwise just use the requested spacing
			if (!fitToScreenHorizontal)
			{
				interval = std::fmax(interval, axisSpacing);
			}

			Vertex v(-1.0f + (float)(x * interval), (float)vec[x] + (shifted ? (float)(median[0] - median[x]) : 0.0f), lineIdx);
			v.dataClassIndex = iter.classIndex();
			v.flags = 0;
			verticesOut.push_back(v);
		}

		m_scrollLimit = ((float)interval * ((float)vectorSize - 1.0f)) - 2.0f;
	}

	//Generate indices for lines
	unsigned int numVectors = dataSet->vectorCount();
	for (unsigned int baseIndex = 0; baseIndex < numVectors; ++baseIndex)
	{
		for (unsigned int i = 1; i < vectorSize; ++i)
		{
			indicesOut.push_back(i + (baseIndex * vectorSize) - 1);
			indicesOut.push_back(i + (baseIndex * vectorSize));
		}
	}

	if (shifted) 
	{
		driver->selectLine(medianLineIdx + 1);
	}

	//Get position for each axis line.
	for (unsigned int i = 0; i < vectorSize; ++i)
	{
		m_axes.push_back(-1.0f + (float)(interval * i));
	}

	return true;
}

void ParallelCoordinatesVisualizationMethod::preDraw(RenderingSystem* driver)
{
	driver->getDriver()->setShader(nullptr);

	glColor3f(0.6f, 0.6f, 0.6f);
	const glm::mat4x4& mvp = driver->getDriver()->getModelViewProjection();
	glLoadMatrixf((float*)&mvp);
	glBegin(GL_LINES);

	for (float axis : m_axes)
	{
		glVertex3f(axis, 1000.0f, 0.0f);
		glVertex3f(axis, -1000.0f, 0.0f);
	}

	glEnd();
}
