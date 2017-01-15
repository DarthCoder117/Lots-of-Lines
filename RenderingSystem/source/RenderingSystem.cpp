#include "LotsOfLines/RenderingSystem.hpp"
#include "LotsOfLines/IRenderer.hpp"

#include "LotsOfLines/ParallelCoordinatesVisualizationMethod.hpp"

using namespace LotsOfLines;

RenderingSystem::RenderingSystem(IRenderer* driver)
	:m_driver(driver),
	m_visualizationMethods({
		std::make_shared<ParallelCoordinatesVisualizationMethod>()
	})
{
	
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

std::shared_ptr<IVertexBufferObject> RenderingSystem::generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type)
{
	for (auto method : m_visualizationMethods)
	{
		if (method->getType() == type)
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			if (method->generateVBO(dataSet, vertices, indices))
			{
				return m_driver->createVBO(vertices, indices);
			}
		}
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

int main()
{
	DataModel dataModel({
		new DataFileLoader()
	});

	std::shared_ptr<DataSet> data = dataModel.loadData("D:/School/CWU/CS 481/Lots-of-Lines/tests/data/iris.data");

	RenderingSystem renderer(new OpenGLRenderer());

	std::shared_ptr<IVertexBufferObject> vbo = renderer.generateFromDataSet(data, EVT_PARALLEL_COORDINATES);

	renderer.setViewTransform(0.0f, 3.7f, 1.0f, 0.2f);

	while (renderer.run())
	{
		renderer.beginDraw();

		renderer.drawVBO(vbo);

		renderer.endDraw();
	}

	return 0;
}
