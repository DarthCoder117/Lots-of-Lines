#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "LotsOfLines/RenderingSystem.hpp"
#include "LotsOfLines/IRenderer.hpp"

#include "LotsOfLines/ParallelCoordinatesVisualizationMethod.hpp"
#include "LotsOfLines/CollocatedPairedCoordinatesVisualizationMethod.hpp"
#include "LotsOfLines/RadialPairedCoordinatesVisualizationMethod.hpp"
#include "LotsOfLines/ShiftedPairedCoordinatesVisualizationMethod.hpp"

using namespace LotsOfLines;

RenderingSystem::RenderingSystem(IRenderer* driver)
	:m_driver(driver)
{
	m_driver->m_renderingSystem = this;

	registerVisualizationMethod(EVT_PARALLEL_COORDINATES, std::make_shared<ParallelCoordinatesVisualizationMethod>());
	registerVisualizationMethod(EVT_COLLOCATED_PAIRED_COORDINATES, std::make_shared<CollocatedPairedCoordinatesVisualizationMethod>());
	registerVisualizationMethod(EVT_RADIAL_PAIRED_COORDINATES, std::make_shared<RadialPairedCoordinatesVisualizationMethod>());
	registerVisualizationMethod(EVT_SHIFTED_PAIRED_COORDINATES, std::make_shared<ShiftedPairedCoordinatesVisualizationMethod>());
}

bool RenderingSystem::init()
{
	return m_driver->init();
}

void RenderingSystem::registerVisualizationMethod(E_VISUALIZATION_TYPE type, std::shared_ptr<IVisualizationMethod> visMethod)
{
	m_visualizationMethods[type] = visMethod;
}

void RenderingSystem::getVisualizationMethods(VisualizationMethodList& visualizationMethodsOut)
{
	for (auto method : m_visualizationMethods)
	{
		visualizationMethodsOut.push_back(method.second);
	}
}

IRenderer* RenderingSystem::getDriver() const
{
	return m_driver;
}

void RenderingSystem::onMousePress(int x, int y)
{
	//Store mouse drag start positions
	m_mousePressed = true;
	m_startMouseX = x;
	m_startMouseY = y;

	//Store window start drag position too
	m_camStartX = m_camX;
	m_camStartY = m_camY;
}

void RenderingSystem::onMouseMove(int x, int y)
{
	if (m_mousePressed)
	{
		NavigationOptions options;
		std::shared_ptr<IVisualizationMethod> method = getCurrentVisualizationMethod();
		if (method) method->getNavigationOptions(options);

		//Offset camera position by amount cursor moved
		m_camX = options.lockPanX ? m_camX : m_camStartX + (float)(m_startMouseX - x) * 0.01f;
		m_camY = options.lockPanY ? m_camY : m_camStartY + (float)(y - m_startMouseY) * 0.01f;
	}
}

void RenderingSystem::onMouseRelease(int x, int y)
{
	m_mousePressed = false;
}

void RenderingSystem::onMouseScroll(int delta)
{
	NavigationOptions options;
	std::shared_ptr<IVisualizationMethod> method = getCurrentVisualizationMethod();
	if (method) method->getNavigationOptions(options);

	m_zoomX = std::fmax(0, !options.lockZoomX ? m_zoomX + delta * 0.01f : m_zoomX);
	m_zoomY = std::fmax(0, !options.lockZoomY ? m_zoomY + delta * 0.01f : m_zoomY);
}

void RenderingSystem::onResize(unsigned int width, unsigned int height)
{
	m_driver->setViewport(0, 0, width, height);
}

void RenderingSystem::draw(float r, float g, float b)
{
	setViewTransform(m_camX, m_camY, m_zoomX, m_zoomY);

	//Begin drawing frame
	m_driver->beginDraw();
	m_driver->clearScreen(r, g, b);

	//Draw visualization
	if (m_vbo)
	{
		drawVBO(m_vbo);
	}

	m_driver->endDraw();
}

void RenderingSystem::autoViewTransform(E_VISUALIZATION_TYPE type)
{
	if (!m_dataSet) return;

	const Vector& maxValues = m_dataSet->getMaxValues();
	const Vector& minValues = m_dataSet->getMinValues();
	double camX = 0.0f, camY = 0.0f, zoomX = 2.0f, zoomY = 2.0f;
	double minY = !minValues.empty() ? minValues[1] : INFINITY,
		maxY = !maxValues.empty() ? maxValues[1] : -INFINITY;
	// Parallel Coordinates
	if (type == EVT_PARALLEL_COORDINATES)
	{
		// Only handle Y values. X values handled in Visualization Method
		zoomX = 1.0f;
		for (unsigned int i = 0; i < maxValues.size(); ++i)
		{
			if (maxY < maxValues[i]) maxY = maxValues[i];
			if (minY > minValues[i]) minY = minValues[i];
		}
	}
	else
	{
		// For all Paired Visualization Methods
		double minX = minValues[0], maxX = maxValues[0];
		for (unsigned int i = 0; i < minValues.size(); ++i)
		{
			if (i % 2 == 0)
			{
				if (minX > minValues[i]) minX = minValues[i];
				if (maxX < maxValues[i]) maxX = maxValues[i];
			}
			else
			{
				if (minY > minValues[i]) minY = minValues[i];
				if (maxY < maxValues[i]) maxY = maxValues[i];
			}
		}
		const Vector& firstVec = m_dataSet->getVectors(*m_dataSet->getClasses().begin())[0];
		double max_firstX = firstVec[0], max_firstY = firstVec[1] ? firstVec[1] : -INFINITY;
		double distance = firstVec[2] ? abs(firstVec[0] - firstVec[2]) : 0;
		double total = distance * (maxValues.size() / 2);
		switch (type)
		{
		case EVT_COLLOCATED_PAIRED_COORDINATES:
			// Don't need to change any values
			break;
		case EVT_RADIAL_PAIRED_COORDINATES:
			// Estimate max values and assign min values
			maxX = maxValues[0] + maxX;
			if (maxValues[1]) maxY = maxValues[1] + maxY;
			if (minX < minValues[0]) minX = minValues[0];
			if (minValues[1] && minY < minValues[1]) minY = minValues[1];
			break;
		case EVT_SHIFTED_PAIRED_COORDINATES:
			// Again only an estimate of max values
			maxX += total;
			maxY += total;
			break;
		default:
			break;
		}
		camX = maxX / 2.0f + minX / 2.0f;
		zoomX /= (maxX - minX);
	}
	camY = maxY / 2.0f + minY / 2.0f;
	zoomY /= maxY - minY;
	setViewTransform((float)camX, (float)camY, (float)zoomX, (float)zoomY);
}

void RenderingSystem::setViewTransform(float camX, float camY, float zoomX, float zoomY)
{
	m_camX = camX;
	m_camY = camY;
	m_zoomX = zoomX;
	m_zoomY = zoomY;
	m_driver->setViewTransform(camX, camY, zoomX, zoomY);
}

void RenderingSystem::setVisualizationType(E_VISUALIZATION_TYPE type)
{
	if (type != m_currentVisualizationType)
	{
		m_currentVisualizationType = type;

		std::vector<Vertex> vertices;
		if (m_dataSet && type != EVT_COUNT)
		{
			m_vbo = generateFromDataSet(m_dataSet, type, vertices);
		}

		autoViewTransform(type);
	}
}

std::shared_ptr<IVisualizationMethod> RenderingSystem::getCurrentVisualizationMethod()
{
	return m_visualizationMethods[m_currentVisualizationType];
}

void RenderingSystem::setDataSet(std::shared_ptr<DataSet> dataSet)
{
	if (m_dataSet != dataSet)
	{
		m_dataSet = dataSet;
	}

	//Rebuild VBO
	if (!m_vbo && m_currentVisualizationType != EVT_COUNT)
	{
		std::vector<Vertex> vertices;
		m_vbo = generateFromDataSet(m_dataSet, m_currentVisualizationType, vertices);
	}

	//Automatically transform view on next frame
	autoViewTransform(m_currentVisualizationType);
}

std::shared_ptr<IVertexBufferObject> RenderingSystem::generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type, std::vector<Vertex>& verticesOut)
{
	auto iter = m_visualizationMethods.find(type);
	if (iter == m_visualizationMethods.end())
	{
		return nullptr;
	}

	std::shared_ptr<IVisualizationMethod> method = iter->second;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	if (method->generateVBO(dataSet, vertices, indices))
	{
		return m_driver->createVBO(vertices, indices);
	}

	return nullptr;
}

void RenderingSystem::drawVBO(std::shared_ptr<IVertexBufferObject> vbo)
{
	m_driver->drawVBO(vbo);
}

unsigned int RenderingSystem::getClosestLine(float x, float y)
{
	float closestDist = std::numeric_limits<float>::max();
	unsigned int closestLine = 0;
	/*for (auto vertex : m_vertices[m_currentVisualizationType])
	{
		glm::vec2 m(x, y);
		glm::vec2 v(vertex.x, vertex.y);
		float dist = glm::distance(m, v);
		if (dist < closestDist)
		{
			closestDist = dist;
			closestLine = vertex.lineIndex;
		}
	}*/

	return closestLine;
}

// TEMPORARY FOR GHETTO TESTING PURPOSES. TESTS WILL BE MOVED TO THE TEST FRAMEWORK SHORTLY.
/*#include "LotsOfLines/OpenGLRenderer.hpp"
#include "LotsOfLines/DataFileLoader.hpp"
#include "LotsOfLines/CSVFileLoader.hpp"

int main()
{
	DataModel dataModel({
		new DataFileLoader()
	});

	std::shared_ptr<DataSet> data = dataModel.loadData("../../tests/data/iris.data");

	RenderingSystem renderer(new OpenGLRenderer());

	renderer.setDataSet(data);

	renderer.setVisualizationType(EVT_PARALLEL_COORDINATES);
	renderer.getDriver()->setSelectedLine(1);

	// Set nav options
	std::shared_ptr<IVisualizationMethod> method = renderer.getCurrentVisualizationMethod();
	NavigationOptions& options = NavigationOptions();
	method->getNavigationOptions(options);
	renderer.setNavigationOptions(options.lockZoomX, options.lockZoomY, options.lockPanX, options.lockPanY);

	while (renderer.run())
	{
		renderer.beginDraw();

		renderer.drawVisualization();

		renderer.endDraw();
	}

	return 0;
}*/
