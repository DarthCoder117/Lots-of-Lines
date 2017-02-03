#ifndef I_VISUALIZATION_METHOD_H
#define I_VISUALIZATION_METHOD_H
#include "LotsOfLines/DataSet.hpp"
#include "LotsOfLines/RenderingSystem.hpp"
#include "LotsOfLines/IRenderer.hpp"
#include "LotsOfLines/VisualizationOptions.hpp"
#include <vector>

namespace LotsOfLines
{
	struct NavigationOptions
	{
		bool lockZoomX, lockZoomY;
		bool lockPanX, lockPanY;
		
		NavigationOptions(bool zX = false, bool zY = false, bool pX = false, bool pY = false)
			: lockZoomX(zX), lockZoomY(zY), lockPanX(pX), lockPanY(pY) {}
	};

	///@brief Macro for defining new visualization types easily.
	#define VISUALIZATION_METHOD(typeName, type)\
		E_VISUALIZATION_TYPE getType() { return type; }\
		std::string getTypeName() {return typeName; }\
		static E_VISUALIZATION_TYPE getClassType() { return type; }\
		static std::string getClassTypeName() {return typeName; }

	///@brief Visualization method interface for generating vertex buffers based on a dataset.
	class IVisualizationMethod
	{
	public:

		virtual ~IVisualizationMethod() {}

		///@return The enum type of the visualization method.
		virtual E_VISUALIZATION_TYPE getType() = 0;
		///@return The string type name of the visualization method.
		virtual std::string getTypeName() = 0;

		///@brief Generate a vertex buffer for the visualization.
		virtual bool generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options = VisualizationOptions()) = 0;

		///@brief Should return the navigation options for the rendering method (X scroll lock, etc)
		virtual void getNavigationOptions(NavigationOptions& optionsOut) = 0;

		///@brief Should fill an empty VisualizationOptions object with the default options to use for the visualization method.
		///This method will be called once when the visualization method is loaded in order to generate fields for the UI system.
		virtual void getDefaultOptions(VisualizationOptions& options) {}
	};
}

#endif