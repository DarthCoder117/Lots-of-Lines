#ifndef COLLOCATED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#define COLLOCATED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#include "RenderingSystem/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class CollocatedPairedCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:

		VISUALIZATION_METHOD("Collocated Paired Coordinates", EVT_COLLOCATED_PAIRED_COORDINATES)

		void getNavigationOptions(NavigationOptions& optionsOut) 
		{
			optionsOut = NavigationOptions();
		};

		bool generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, RenderingSystem* driver, const VisualizationOptions& options);
	};
}

#endif
