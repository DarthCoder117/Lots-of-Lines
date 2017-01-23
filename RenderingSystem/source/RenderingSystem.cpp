#include "LotsOfLines/RenderingSystem.hpp"
#include "LotsOfLines/IRenderer.hpp"

#include "LotsOfLines/ParallelCoordinatesVisualizationMethod.hpp"
#include "LotsOfLines/CollocatedPairedCoordinatesVisualizationMethod.hpp"
#include "LotsOfLines/RadialPairedCoordinatesVisualizationMethod.hpp"

using namespace LotsOfLines;

RenderingSystem::RenderingSystem(IRenderer* driver)
	:m_driver(driver)
{
	registerVisualizationMethod(EVT_PARALLEL_COORDINATES, std::make_shared<ParallelCoordinatesVisualizationMethod>());
	registerVisualizationMethod(EVT_COLLOCATED_PAIRED_COORDINATES, std::make_shared<CollocatedPairedCoordinatesVisualizationMethod>());
	registerVisualizationMethod(EVT_RADIAL_PAIRED_COORDINATES, std::make_shared<RadialPairedCoordinatesVisualizationMethod>());
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
			m_vboCache[type] = generateFromDataSet(m_dataSet, type);
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
			m_vboCache[m_currentVisualizationType] = generateFromDataSet(m_dataSet, m_currentVisualizationType);
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

std::shared_ptr<IVertexBufferObject> RenderingSystem::generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type)
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

// TEMPORARY FOR GHETTO TESTING PURPOSES. TESTS WILL BE MOVED TO THE TEST FRAMEWORK SHORTLY.
#include "LotsOfLines/OpenGLRenderer.hpp"
#include "LotsOfLines/DataFileLoader.hpp"
#include "LotsOfLines/CSVFileLoader.hpp"

int main()
{
	DataModel dataModel({
		new DataFileLoader()
	});

	std::shared_ptr<DataSet> data = dataModel.loadData("../../tests/data/collocated-paired-coordinates-test.data");

	RenderingSystem renderer(new OpenGLRenderer());

	renderer.setDataSet(data);
	renderer.setVisualizationType(EVT_RADIAL_PAIRED_COORDINATES);
	renderer.setViewTransform(0.0f, 0.2f, 1.0f, 1.0f);

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
