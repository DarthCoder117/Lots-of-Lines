#ifndef RENDERING_SYSTEM_HPP
#define RENDERING_SYSTEM_HPP
#include "LotsOfLines/IRenderer.hpp"
#include "LotsOfLines/DataModel.hpp"
#include "LotsOfLines/IVertexBufferObject.hpp"
#include "LotsOfLines/VisualizationOptions.hpp"
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

	typedef std::vector<std::shared_ptr<IVisualizationMethod> > VisualizationMethodList;

	///@brief The RenderingSystem manages different drivers to render with and handles all visualization rendering.
	class RenderingSystem
	{
	public:

		RenderingSystem(IRenderer* driver);
	
		///@brief Initialize the rendering system and its driver.
		bool init();

		///@return Pointer to the driver implementation.
		IRenderer* getDriver() const;

	private:

		IRenderer* m_driver;

	public:

		///@brief Registers a visualization method and makes it available to use.
		void registerVisualizationMethod(E_VISUALIZATION_TYPE type, std::shared_ptr<IVisualizationMethod> visMethod);

		///@brief Get the list of currently registered visualization methods.
		void getVisualizationMethods(VisualizationMethodList& visualizationMethodsOut);

		///@brief Set current visualization type and regenerate vertex buffers.
		void setVisualizationType(E_VISUALIZATION_TYPE type);

		///@brief Regenerate the visualization after options or datasets have changed.
		void redraw();

		///@return Shared pointer to the current visualization method.
		std::shared_ptr<IVisualizationMethod> getCurrentVisualizationMethod();

		///@brief Set the data set that will be drawn by the rendering system.
		void setDataSet(std::shared_ptr<DataSet> dataSet);

		///@return Current visualization options in use.
		VisualizationOptions& getVisualizationOptions();

		///@brief Set the color to use when rendering a data class.
		void setDataClassColor(unsigned int classIdx, float r, float g, float b);
		///@return 3-element float array with data class color.
		const float* getDataClassColor(unsigned int classIdx) const;
		///@return The full array of data class colors
		const float** getDataClassColors() const;
		///@return The total number of data class colors that have been configured.
		unsigned int getDataClassColorCount() const;

	private:

		//rgb(191,48,48) 
		//rgb(217,116,0)
		//rgb(255,217,64)
		//rgb(51,48,13)
		//rgb(45,128,32)
		//rgb(0,255,0)
		//rgb(182,242,230)
		//rgb(0,111,166)
		//rgb(61,85,242)
		//rgb(191,96,159)
		float m_dataClassColors[10][3] = 
		{
			{ 0.74902f, 0.188235f, 0.188235f },
			{ 0.239216f, 0.333333f, 0.94902f },
			{ 0.176471f, 0.501961f, 0.12549f },
			{ 0.0f, 1.0f, 0.0f },
			{ 1.0f, 0.85098f, 0.25098f },
			{ 0.713725f, 0.94902f, 0.901961f },
			{ 0.0f, 0.435294f, 0.65098f },
			{ 0.74902f, 0.376471f, 0.623529f },
			{ 0.2f, 0.188235f, 0.0509804f },
			{ 0.85098f, 0.454902f, 0.0f }
		};

		E_VISUALIZATION_TYPE m_currentVisualizationType = EVT_COUNT;

		std::map<E_VISUALIZATION_TYPE, std::shared_ptr<IVisualizationMethod> > m_visualizationMethods;

		std::shared_ptr<DataSet> m_dataSet = nullptr;

		VisualizationOptions m_options;

		///@brief Generate a VBO from a data set.
		std::shared_ptr<IVertexBufferObject> generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type, std::vector<Vertex>& verticesOut);

	public:

		///@brief Call when a mouse press event occurs on the window
		void onMousePress(int x, int y);
		///@brief Call when a mouse press event occurs on the window
		void onRightClick(int x, int y);
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

		unsigned int m_windowWidth;
		unsigned int m_windowHeight;

		glm::mat4x4 m_modelViewProjection;

		///@brief Expands a selection from a vertex to the entire line.
		void expandSelectionToLine(Vertex* vertices, unsigned int vertexCount, Vertex* selected);

	public:

		///@brief Call when the window is resized.
		void onResize(unsigned int width, unsigned int height);

		///@brief Scales the view to the current visualization automatically.
		void autoViewTransform(E_VISUALIZATION_TYPE type);

		void setViewTransform(float camX, float camY, float zoomX, float zoomY);

		void draw(float r = 0.2f, float g = 0.2f, float b = 0.2f);

		void drawVBO(std::shared_ptr<IVertexBufferObject> vbo);

		///@brief Set the line that's selected.
		void setSelectedLine(unsigned int lineIndex);

		///@brief Gets index of the closest line to the 
		unsigned int getClosestLine(float x, float y);

	private:

		bool m_autoViewTransformFlag = false;

		std::shared_ptr<IVertexBufferObject> m_vbo;
		std::vector<Vertex> m_vertices;
	};
}

#endif