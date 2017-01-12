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
		EVT_COUNT
	};

	///@brief The RenderingSystem manages different drivers to render with and handles all visualization rendering.
	class RenderingSystem
	{
	public:

		RenderingSystem(IRenderer* driver);
	
		IRenderer* getDriver() const;

		bool run();

		void beginDraw(float r = 0.6f, float g = 0.6f, float b = 1.0f);

		void endDraw();

		std::shared_ptr<IVertexBufferObject> generateFromDataSet(std::shared_ptr<DataSet> dataSet, E_VISUALIZATION_TYPE type);

		void drawVBO(std::shared_ptr<IVertexBufferObject> vbo);

	private:

		IRenderer* m_driver;

		std::vector<std::shared_ptr<IVisualizationMethod> > m_visualizationMethods;
	};
}

#endif