#ifndef SHIFTED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#define SHIFTED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#include "RenderingSystem/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class ShiftedPairedCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:

		VISUALIZATION_METHOD("Shifted Paired Coordinates", EVT_SHIFTED_PAIRED_COORDINATES)

		const char* STEP = "Distance of step";
		const char* AUTO_STEP = "Auto step distance calculation";
		const char* HORIZONTAL = "Shift around horizontal line";
		const char* COLLAPSED = "Collapse line to point";

		void getNavigationOptions(NavigationOptions& optionsOut) 
		{
			optionsOut = NavigationOptions();
		}

		void getDefaultOptions(VisualizationOptions& options)
		{
			options.setDouble(STEP, 0.0);
			options.setBool(AUTO_STEP, true);
			options.setBool(HORIZONTAL, false);
			options.setBool(COLLAPSED, false);
		}

		bool generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, RenderingSystem* driver, const VisualizationOptions& options);
	};
}

#endif
