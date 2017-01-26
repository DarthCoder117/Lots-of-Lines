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
	registerVisualizationMethod(EVT_PARALLEL_COORDINATES, std::make_shared<ParallelCoordinatesVisualizationMethod>());
	registerVisualizationMethod(EVT_COLLOCATED_PAIRED_COORDINATES, std::make_shared<CollocatedPairedCoordinatesVisualizationMethod>());
	registerVisualizationMethod(EVT_RADIAL_PAIRED_COORDINATES, std::make_shared<RadialPairedCoordinatesVisualizationMethod>());
	registerVisualizationMethod(EVT_SHIFTED_PAIRED_COORDINATES, std::make_shared<ShiftedPairedCoordinatesVisualizationMethod>());
}

void RenderingSystem::registerVisualizationMethod(E_VISUALIZATION_TYPE type, std::shared_ptr<IVisualizationMethod> visMethod)
{
	m_visualizationMethods[type] = visMethod;
}

std::shared_ptr<IVisualizationMethod> RenderingSystem::getCurrentVisualizationMethod()
{
	return m_visualizationMethods[m_currentVisualizationType];
}

IRenderer* RenderingSystem::getDriver() const
{
	return m_driver;
}

bool RenderingSystem::run()
{
	return m_driver->run();
}

void RenderingSystem::beginDraw(float r, float g, float b)
{
	m_driver->beginDraw(r, g, b);
}

void RenderingSystem::endDraw()
{
	m_driver->endDraw();
}

void RenderingSystem::setViewTransform(float camX, float camY, float zoomX, float zoomY)
{
	m_driver->setViewTransform(camX, camY, zoomX, zoomY);
}

void RenderingSystem::setNavigationOptions(bool lockZoomX, bool lockZoomY, bool lockPanX, bool lockPanY)
{
	m_driver->setNavigationOptions(lockZoomX, lockZoomY, lockPanX, lockPanY);
}

void RenderingSystem::setVisualizationType(E_VISUALIZATION_TYPE type)
{
	if (m_currentVisualizationType != type)
	{
		m_currentVisualizationType = type;

		//Generate VBO if needed
		if (m_vboCache.find(type) == m_vboCache.end())
		{
			std::vector<Vertex> vertices;
			m_vboCache[type] = generateFromDataSet(m_dataSet, type, vertices);
			m_vertices[type] = vertices;
		}
	}
}

void RenderingSystem::setDataSet(std::shared_ptr<DataSet> dataSet)
{
	if (m_dataSet != dataSet)
	{
		m_dataSet = dataSet;

		//Generate VBO buffer if needed
		if (m_vboCache.find(m_currentVisualizationType) == m_vboCache.end())
		{
			std::vector<Vertex> vertices;
			m_vboCache[m_currentVisualizationType] = generateFromDataSet(m_dataSet, m_currentVisualizationType, vertices);
			m_vertices[m_currentVisualizationType] = vertices;
		}
	}
}

void RenderingSystem::drawVisualization()
{
	auto iter = m_vboCache.find(m_currentVisualizationType);
	if (iter != m_vboCache.end())
	{
		drawVBO(iter->second);
	}
}

std::shared_ptr<IVertexBufferObject> RenderingSystem::generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type, std::vector<Vertex>& verticesOut)
{
	auto iter = m_visualizationMethods.find(type);
	if (iter == m_visualizationMethods.end())
	{
		return nullptr;
	}

	std::shared_ptr<IVisualizationMethod> method = iter->second;

	std::vector<unsigned int> indices;
	if (method->generateVBO(dataSet, verticesOut, indices))
	{
		return m_driver->createVBO(verticesOut, indices);
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
	for (auto vertex : m_vertices[m_currentVisualizationType])
	{
		glm::vec2 m(x, y);
		glm::vec2 v(vertex.x, vertex.y);
		float dist = glm::distance(m, v);
		if (dist < closestDist)
		{
			closestDist = dist;
			closestLine = vertex.lineIndex;
		}
	}

	return closestLine;
}

// TEMPORARY FOR GHETTO TESTING PURPOSES. TESTS WILL BE MOVED TO THE TEST FRAMEWORK SHORTLY.
#include "LotsOfLines/OpenGLRenderer.hpp"
#include "LotsOfLines/DataFileLoader.hpp"
#include "LotsOfLines/CSVFileLoader.hpp"

int main()
{
	DataModel dataModel({
		new DataFileLoader()
	});

	std::shared_ptr<DataSet> data = dataModel.loadData("../../tests/data/iris-small.data");

	RenderingSystem renderer(new OpenGLRenderer());

	renderer.setDataSet(data);

	renderer.setViewTransform(0.0f, 3.7f, 1.0f, 0.2f);
	renderer.setVisualizationType(EVT_PARALLEL_COORDINATES);
	renderer.getDriver()->setSelectedLine(1);

	//renderer.setViewTransform(0.0f, 0.2f, 1.0f, 1.0f);

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
}
