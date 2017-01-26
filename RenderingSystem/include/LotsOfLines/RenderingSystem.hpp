#ifndef RENDERING_SYSTEM_HPP
#define RENDERING_SYSTEM_HPP
#include "LotsOfLines/DataModel.hpp"
#include "LotsOfLines/IVertexBufferObject.hpp"
#include <vector>

namespace LotsOfLines
{
	class IRenderer;
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
	
		void registerVisualizationMethod(E_VISUALIZATION_TYPE type, std::shared_ptr<IVisualizationMethod> visMethod);

		std::shared_ptr<IVisualizationMethod> getCurrentVisualizationMethod();

		IRenderer* getDriver() const;

		bool run();

		void beginDraw(float r = 0.2f, float g = 0.2f, float b = 0.2f);

		void endDraw();

		void setViewTransform(float camX, float camY, float zoomX, float zoomY);

		void setVisualizationType(E_VISUALIZATION_TYPE type);

		void setNavigationOptions(bool lockZoomX, bool lockZoomY, bool lockPanX, bool lockPanY);

		void setDataSet(std::shared_ptr<DataSet> dataSet);

		void drawVisualization();

		std::shared_ptr<IVertexBufferObject> generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type);

		void drawVBO(std::shared_ptr<IVertexBufferObject> vbo);

	private:

		IRenderer* m_driver;

		E_VISUALIZATION_TYPE m_currentVisualizationType = EVT_PARALLEL_COORDINATES;
		std::shared_ptr<DataSet> m_dataSet = nullptr;

		std::map<E_VISUALIZATION_TYPE, std::shared_ptr<IVertexBufferObject> > m_vboCache;

		std::map<E_VISUALIZATION_TYPE, std::shared_ptr<IVisualizationMethod> > m_visualizationMethods;
	};
}

#endif