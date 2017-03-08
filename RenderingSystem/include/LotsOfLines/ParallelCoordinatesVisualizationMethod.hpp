#ifndef PARALLEL_COORDINATES_VISUALIZATION_METHOD_HPP
#define PARALLEL_COORDINATES_VISUALIZATION_METHOD_HPP
#include "LotsOfLines/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class ParallelCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:
		
		VISUALIZATION_METHOD("Parallel Coordinates", EVT_PARALLEL_COORDINATES)

		const char* FIT_TO_SCREEN_HORIZONTAL = "Fit horizontal";
		const char* SHIFTED = "Shift axes based around central line";
		const char* AXIS_SPACING = "Axis spacing";

		float m_scrollLimit = 0.0f;

		void getNavigationOptions(NavigationOptions& optionsOut) 
		{
			optionsOut = NavigationOptions(true, false);
			optionsOut.limitScroll = true;
			optionsOut.minScrollLimitX = 0.0f;
			optionsOut.maxScrollLimitX = m_scrollLimit;
		}

		void getDefaultOptions(VisualizationOptions& options)
		{
			options.setBool(FIT_TO_SCREEN_HORIZONTAL, true);
			options.setBool(SHIFTED, false);
			options.setDouble(AXIS_SPACING, 0.2);
		}

		bool generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, RenderingSystem* driver, const VisualizationOptions& options);
		
		void preDraw(RenderingSystem* driver);

	private:

		std::vector<float> m_axes;
	};
}

#endif