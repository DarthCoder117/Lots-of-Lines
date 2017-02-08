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

		///@brief Enable/disable a visualization type and manage the list of enabled visualization types.
		///A maximum of 4 visualization types can be enabled at once. The oldest enabled method will be replaced if the maximum of 4 is reached.
		void enableVisualizationType(E_VISUALIZATION_TYPE type, bool enabled = true);

		///@return The list of currently enabled visualization types.
		const std::vector<E_VISUALIZATION_TYPE>& getEnabledVisualizationTypes();

		///@brief Set the data set that will be drawn by the rendering system.
		void setDataSet(std::shared_ptr<DataSet> dataSet);

	private:

		std::vector<E_VISUALIZATION_TYPE> m_enabledVisualizationTypes;

		std::map<E_VISUALIZATION_TYPE, std::shared_ptr<IVisualizationMethod> > m_visualizationMethods;

		std::shared_ptr<DataSet> m_dataSet = nullptr;

		///@brief Generate a VBO from a data set.
		std::shared_ptr<IVertexBufferObject> generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type, std::vector<Vertex>& verticesOut);

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

		///@brief Sets the splitscreen mode.
		///@param count Number of screens to split to (either 1, 2 or 4).
		void setSplitScreen(unsigned short count);

		///@brief Scales the view to the current visualization automatically.
		void autoViewTransform();

		void setViewTransform(float camX, float camY, float zoomX, float zoomY);

		void draw(float r = 0.2f, float g = 0.2f, float b = 0.2f);

		void drawVBO(std::shared_ptr<IVertexBufferObject> vbo);

		///@brief Gets index of the closest line to the 
		unsigned int getClosestLine(float x, float y);

	private:

		///@brief Automatically adjusts the viewport
		void autoViewTransformImpl(E_VISUALIZATION_TYPE type);

		bool m_autoViewTransformFlag = false;

		///@brief Draw the current visualization to the screen.
		void drawVisualization(E_VISUALIZATION_TYPE type);

		unsigned int m_screenWidth = 0;
		unsigned int m_screenHeight = 0;
		unsigned short m_splitScreenCount = 0;

		///@brief Updates the viewport settings when the screen resolution or splitscreen mode changes.
		///@param screenIdx The index of the screen viewport to update.
		void updateViewport(unsigned short screenIdx);

		std::map<E_VISUALIZATION_TYPE, std::shared_ptr<IVertexBufferObject> > m_vboCache;
		std::map<E_VISUALIZATION_TYPE, std::vector<Vertex> > m_vertices;
	};
}

#endif