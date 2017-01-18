#ifndef I_VISUALIZATION_METHOD_H
#define I_VISUALIZATION_METHOD_H
#include "LotsOfLines/DataSet.hpp"
#include "LotsOfLines/RenderingSystem.hpp"
#include "LotsOfLines/IRenderer.hpp"
#include <vector>

namespace LotsOfLines
{
	struct NavigationOptions
	{
		bool lockZoomX = false;
		bool lockZoomY = false;

		bool lockPanX = false;
		bool lockPanY = false;
	};

	class IVisualizationMethod
	{
	public:

		virtual ~IVisualizationMethod() {}

		virtual E_VISUALIZATION_TYPE getType() = 0;

		virtual bool generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut) = 0;

		///@brief Should return the navigation options for the rendering method (X scroll lock, etc)
		virtual void getNavigationOptions(NavigationOptions& optionsOut) {}
	};
}

#endif