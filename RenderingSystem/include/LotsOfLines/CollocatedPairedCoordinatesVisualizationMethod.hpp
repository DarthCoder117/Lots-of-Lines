#ifndef COLLOCATED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#define COLLOCATED_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#include "LotsOfLines/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class CollocatedPairedCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:
		void getNavigationOptions(NavigationOptions& optionsOut) {
			optionsOut = NavigationOptions();
		};
		E_VISUALIZATION_TYPE getType() { return EVT_COLLOCATED_PAIRED_COORDINATES; }

		bool generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut);
	};
}

#endif