#ifndef SHIFTED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#define SHIFTED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#include "LotsOfLines/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class ShiftedPairedCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:

		VISUALIZATION_METHOD("Shifted Paired Coordinates", EVT_SHIFTED_PAIRED_COORDINATES)

		const char* STEP = "Distance of step";
		const char* AUTO_STEP = "Auto step distance calculation";
		const char* HORIZONTAL = "Shift around horizontal line";
		const char* NON_INTERSECTING = "Remove intersections";
		const char* COLLAPSED = "Collapse line to point";
		const char* INCREASING = "Increasing lines";

		void getNavigationOptions(NavigationOptions& optionsOut) 
		{
			optionsOut = NavigationOptions();
		}

		void getDefaultOptions(VisualizationOptions& options)
		{
			options.setDouble(STEP, 1.0);
			options.setBool(AUTO_STEP, true);
			options.setBool(HORIZONTAL, false);
			options.setBool(NON_INTERSECTING, false);
			options.setBool(COLLAPSED, false);
			options.setBool(INCREASING, false);
		}

		bool generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options);
	};
}

#endif