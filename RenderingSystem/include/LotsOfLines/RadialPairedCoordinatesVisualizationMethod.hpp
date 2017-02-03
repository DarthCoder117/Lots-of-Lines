#ifndef RADIAL_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#define RADIAL_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#include "LotsOfLines/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class RadialPairedCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:

		VISUALIZATION_METHOD("Radial Paired Coordinates", EVT_RADIAL_PAIRED_COORDINATES)

		void getNavigationOptions(NavigationOptions& optionsOut) 
		{
			optionsOut = NavigationOptions();
		}

		bool generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, const VisualizationOptions& options);
	};
}

#endif