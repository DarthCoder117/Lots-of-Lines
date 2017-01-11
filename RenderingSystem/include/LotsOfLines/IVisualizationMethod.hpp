#ifndef I_VISUALIZATION_METHOD_H
#define I_VISUALIZATION_METHOD_H
#include "LotsOfLines/DataSet.hpp"
#include "LotsOfLines/IRenderer.hpp"
#include <vector>

namespace LotsOfLines
{
	enum E_VISUALIZATION_METHOD
	{
		EVM_PARALLEL_COORDINATES,
		EVM_COUNT
	};

	class IVisualizationMethod
	{
	public:

		virtual ~IVisualizationMethod() {}

		virtual E_VISUALIZATION_METHOD getType() = 0;

		virtual void generateVBO(const DataSet& dataSet, std::vector<float3>& verticesOut, std::vector<unsigned int>& indicesOut) = 0;
	};
}

#endif