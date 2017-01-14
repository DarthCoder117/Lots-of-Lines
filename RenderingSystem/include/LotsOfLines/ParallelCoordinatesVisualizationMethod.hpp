#ifndef PARALLEL_COORDINATES_VISUALIZATION_METHOD_HPP
#define PARALLEL_COORDINATES_VISUALIZATION_METHOD_HPP
#include "LotsOfLines/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class ParallelCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:

		E_VISUALIZATION_TYPE getType() { return EVT_PARALLEL_COORDINATES; }

		bool generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut);
	};
}

#endif