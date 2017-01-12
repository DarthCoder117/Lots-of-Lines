#ifndef I_VISUALIZATION_METHOD_H
#define I_VISUALIZATION_METHOD_H
#include "LotsOfLines/DataSet.hpp"
#include "LotsOfLines/RenderingSystem.hpp"
#include "LotsOfLines/IRenderer.hpp"
#include <vector>

namespace LotsOfLines
{
	class IVisualizationMethod
	{
	public:

		virtual ~IVisualizationMethod() {}

		virtual E_VISUALIZATION_TYPE getType() = 0;

		virtual bool generateVBO(std::shared_ptr<DataSet> dataSet, std::vector<float3>& verticesOut, std::vector<unsigned int>& indicesOut) = 0;
	};
}

#endif