#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include "LotsOfLines/RenderingSystem.hpp"
#include "LotsOfLines/IRenderer.hpp"
#include "LotsOfLines/Shaders.hpp"

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
	if (!m_driver->init()) return false;
	if (!Shaders::compileShaders(m_driver)) return false;

	m_driver->setClassColors((float*)m_dataClassColors);

	return true;
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

void RenderingSystem::onRightClick(int x, int y)
{
	//Calculate actual mouse click position
	float mouseX = 2.0f * x / m_windowWidth - 1;
	float mouseY = -2.0f * y / m_windowHeight + 1;

	glm::mat4x4 invMvp = glm::inverse(m_modelViewProjection);
	glm::vec4 transformedMousePos(mouseX, mouseY, 1.0f, 1.0f);
	transformedMousePos = invMvp * transformedMousePos;
	transformedMousePos /= transformedMousePos.w;

	glm::vec2 mousePos(transformedMousePos.x, transformedMousePos.y);

	//Select all vertices below
	if (m_vbo)
	{
		Vertex* vertices = m_vbo->mapVertices();
		unsigned int* indices = m_vbo->mapIndices();

		const float selectionDist = 0.05f;//Default selection radius

		//Pick the closest veretex to the mouse pointer
		Vertex* closestVertex = nullptr;
		float shortestDist = selectionDist;

		//Iterate through each vertex and add to selection list
		for (unsigned int i = 0; i < m_vbo->vertexCount(); ++i)
		{
			glm::vec2 vertPos(vertices[i].x, vertices[i].y);

			//Clear flags on vertex
			vertices[i].flags &= ~EVSF_SELECTED;

			//Add vertex to selected list
			float dist = glm::distance(mousePos, vertPos);
			if (dist <= shortestDist)
			{
				closestVertex = &vertices[i];
				shortestDist = dist;
			}
		}

		//Expand vertex selection to entire line
		if (closestVertex)
		{
			expandSelectionToLine(vertices, m_vbo->vertexCount(), closestVertex);
		}

		m_vbo->unmapIndices();
		m_vbo->unmapVertices();
	}
}

void RenderingSystem::expandSelectionToLine(Vertex* vertices, unsigned int vertexCount, Vertex* selected)
{
	for (unsigned int i = 0; i < vertexCount; ++i)
	{
		if (vertices[i].lineIndex == selected->lineIndex)
		{
			vertices[i].flags |= EVSF_SELECTED;
		}
	}
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

		//Lock scroll
		if (options.limitScroll)
		{
			m_camX = std::fmax(m_camX, options.minScrollLimitX);
			m_camX = std::fmin(m_camX, options.maxScrollLimitX);
		}
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

	m_zoomX = std::fmax(0.0f, !options.lockZoomX ? m_zoomX + delta * 0.01f : m_zoomX);
	m_zoomY = std::fmax(0.0f, !options.lockZoomY ? m_zoomY + delta * 0.01f : m_zoomY);
}

void RenderingSystem::onResize(unsigned int width, unsigned int height)
{
	m_windowWidth = width;
	m_windowHeight = height;
	m_driver->setViewport(0, 0, width, height);
}

void RenderingSystem::draw(float r, float g, float b)
{
	//Calculate MVP matrix
	glm::mat4x4 view = glm::translate(glm::mat4x4(), glm::vec3(-m_camX, -m_camY, 0.0f));
	glm::mat4x4 proj = glm::ortho(-m_zoomX, m_zoomX, -m_zoomY, m_zoomX, -1.0f, 1.0f);
	m_modelViewProjection = view * proj;
	m_driver->setModelViewProjection(m_modelViewProjection);

	//Begin drawing frame
	m_driver->beginDraw();
	m_driver->clearScreen(r, g, b);

	//Draw visualization
	if (m_vbo)
	{
		//Draw unselected lines first
		m_driver->setShader(Shaders::defaultVisualization);
		drawVBO(m_vbo);

		//Selection gets drawn on top so that it doesn't get hidden by the other lines
		m_driver->setShader(Shaders::selectedLine);
		drawVBO(m_vbo);
	}

	m_driver->endDraw();
}

void RenderingSystem::autoViewTransform(E_VISUALIZATION_TYPE type)
{
	/*if (!m_dataSet) return;

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
	setViewTransform((float)camX, (float)camY, (float)zoomX, (float)zoomY);*/
}

void RenderingSystem::setViewTransform(float camX, float camY, float zoomX, float zoomY)
{
	m_camX = camX;
	m_camY = camY;
	m_zoomX = zoomX;
	m_zoomY = zoomY;
}

void RenderingSystem::setVisualizationType(E_VISUALIZATION_TYPE type)
{
	if (type != m_currentVisualizationType)
	{
		m_currentVisualizationType = type;

		//Setup default options
		m_options.clear();
		getCurrentVisualizationMethod()->getDefaultOptions(m_options);
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
}

VisualizationOptions& RenderingSystem::getVisualizationOptions()
{
	return m_options;
}

void RenderingSystem::setDataClassColor(unsigned int classIdx, float r, float g, float b)
{
	m_dataClassColors[classIdx][0] = r;
	m_dataClassColors[classIdx][1] = g;
	m_dataClassColors[classIdx][2] = b;

	m_driver->setClassColors((float*)m_dataClassColors);
}

const float* RenderingSystem::getDataClassColor(unsigned int classIdx) const
{
	return m_dataClassColors[classIdx];
}

const float** RenderingSystem::getDataClassColors() const
{
	return (const float**)m_dataClassColors;
}

unsigned int RenderingSystem::getDataClassColorCount() const
{
	return sizeof(m_dataClassColors);
}

void RenderingSystem::redraw()
{
	//Generate vertex buffer
	m_vertices.clear();
	if (m_dataSet && m_currentVisualizationType != EVT_COUNT)
	{
		m_vbo = generateFromDataSet(m_dataSet, m_currentVisualizationType, m_vertices);
	}

	//Scale view to fit
	//autoViewTransform(m_currentVisualizationType);
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
	if (method->generateVBO(dataSet, verticesOut, indices, m_options))
	{
		return m_driver->createVBO(verticesOut, indices);
	}

	return nullptr;
}

void RenderingSystem::drawVBO(std::shared_ptr<IVertexBufferObject> vbo)
{
	m_driver->drawVBO(vbo);
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
