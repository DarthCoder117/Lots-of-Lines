#ifndef RENDERING_SYSTEM_HPP
#define RENDERING_SYSTEM_HPP
#include "LotsOfLines/IRenderer.hpp"
#include "LotsOfLines/DataModel.hpp"
#include "LotsOfLines/IVertexBufferObject.hpp"
#include <vector>

namespace LotsOfLines
{
	class IVisualizationMethod;

	enum E_VISUALIZATION_TYPE
	{
		EVT_PARALLEL_COORDINATES,
		EVT_COLLOCATED_PAIRED_COORDINATES,
		EVT_RADIAL_PAIRED_COORDINATES,
		EVT_SHIFTED_PAIRED_COORDINATES,
		EVT_COUNT
	};

	///@brief The RenderingSystem manages different drivers to render with and handles all visualization rendering.
	class RenderingSystem
	{
	public:

		RenderingSystem(IRenderer* driver);
	
		///@brief Initialize the rendering system and its driver.
		bool init();

		///@return Pointer to the driver implementation.
		IRenderer* getDriver() const;

	public:

		///@brief Registers a visualization method and makes it available to use.
		void registerVisualizationMethod(E_VISUALIZATION_TYPE type, std::shared_ptr<IVisualizationMethod> visMethod);

		///@return The currently active visualization method.
		std::shared_ptr<IVisualizationMethod> getCurrentVisualizationMethod();

		///@brief Set the active visualization type.
		void setVisualizationType(E_VISUALIZATION_TYPE type);

	private:

		E_VISUALIZATION_TYPE m_currentVisualizationType = EVT_PARALLEL_COORDINATES;

		std::map<E_VISUALIZATION_TYPE, std::shared_ptr<IVisualizationMethod> > m_visualizationMethods;

	public:

		///@brief Call when a mouse press event occurs on the window
		void onMousePress(int x, int y);
		///@brief Call when a mouse move event occurs on the window
		void onMouseMove(int x, int y);
		///@brief Call when a mouse release event occurs on the window
		void onMouseRelease(int x, int y);
		///@brief Call when a mouse scroll wheel event occurs.
		///@param delta The amount of degrees the mouse wheel was moved.
		void onMouseScroll(int delta);

	private:

		bool m_mousePressed = false;
		int m_startMouseX = 0, m_startMouseY = 0;

		float m_camX = 0.0f, m_camY = 0.0f;
		float m_zoomX = 1.0f, m_zoomY = 1.0f;
		float m_camStartX = 0.0f, m_camStartY = 0.0f;

	public:

		///@brief Call when the window is resized.
		void onResize(unsigned int width, unsigned int height);

		void setViewTransform(float camX, float camY, float zoomX, float zoomY);

		void setDataSet(std::shared_ptr<DataSet> dataSet);

		void beginDraw(float r = 0.2f, float g = 0.2f, float b = 0.2f);

		void endDraw();

		void drawVisualization();

		void drawVBO(std::shared_ptr<IVertexBufferObject> vbo);

		///@brief Gets index of the closest line to the 
		unsigned int getClosestLine(float x, float y);

	private:

		std::shared_ptr<IVertexBufferObject> generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type, std::vector<Vertex>& verticesOut);

		IRenderer* m_driver;

		std::shared_ptr<DataSet> m_dataSet = nullptr;

		std::map<E_VISUALIZATION_TYPE, std::shared_ptr<IVertexBufferObject> > m_vboCache;
		std::map<E_VISUALIZATION_TYPE, std::vector<Vertex> > m_vertices;
	};
}

#endif