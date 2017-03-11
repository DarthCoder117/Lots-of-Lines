#ifndef I_VISUALIZATION_METHOD_H
#define I_VISUALIZATION_METHOD_H
#include "DataModel/DataSet.hpp"
#include "RenderingSystem/RenderingSystem.hpp"
#include "RenderingSystem/IRenderer.hpp"
#include "RenderingSystem/VisualizationOptions.hpp"
#include <vector>

namespace LotsOfLines
{
	struct NavigationOptions
	{
		bool lockZoomX, lockZoomY;
		bool lockPanX, lockPanY;
		float minScrollLimitX, maxScrollLimitX;
		bool limitScroll;
		
		NavigationOptions(bool zX = false, bool zY = false, bool pX = false, bool pY = false, float sMinX = 0.0f, float sMaxX = 0.0f)
			: lockZoomX(zX), lockZoomY(zY), lockPanX(pX), lockPanY(pY), minScrollLimitX(sMinX), maxScrollLimitX(sMaxX), limitScroll(false) {}
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
		virtual bool generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, RenderingSystem* driver, const VisualizationOptions& options = VisualizationOptions()) = 0;

		///@brief Draw axis lines and other extra features of the visualization method.
                virtual void preDraw(RenderingSystem*) {}

		///@brief Should return the navigation options for the rendering method (X scroll lock, etc)
		virtual void getNavigationOptions(NavigationOptions& optionsOut) = 0;

		///@brief Should fill an empty VisualizationOptions object with the default options to use for the visualization method.
		///This method will be called once when the visualization method is loaded in order to generate fields for the UI system.
                virtual void getDefaultOptions(VisualizationOptions&) {}
	};
}

#endif
