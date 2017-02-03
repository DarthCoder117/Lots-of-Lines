#ifndef SHIFTED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#define SHIFTED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#include "LotsOfLines/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class ShiftedPairedCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:

		VISUALIZATION_METHOD("Shifted Paired Coordinates", EVT_SHIFTED_PAIRED_COORDINATES)

		void getNavigationOptions(NavigationOptions& optionsOut) 
		{
			optionsOut = NavigationOptions();
		}

		bool generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options);
	};
}

#endif