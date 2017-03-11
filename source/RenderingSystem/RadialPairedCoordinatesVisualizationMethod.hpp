#ifndef RADIAL_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#define RADIAL_PAIRED_COORDINATES_VISUALIZATION_METHOD_HPP
#include "RenderingSystem/IVisualizationMethod.hpp"

namespace LotsOfLines
{
	class RadialPairedCoordinatesVisualizationMethod : public IVisualizationMethod
	{
	public:

		VISUALIZATION_METHOD("Radial (Anchored) Paired Coordinates", EVT_RADIAL_PAIRED_COORDINATES)

		const char* DRAW_SEQUENTIALLY = "Draw lines sequentially";

		void getNavigationOptions(NavigationOptions& optionsOut) 
		{
			optionsOut = NavigationOptions();
		}

		void getDefaultOptions(VisualizationOptions& options)
		{
			options.setBool(DRAW_SEQUENTIALLY, true);
		}

		bool generateVBO(const std::shared_ptr<const DataSet> dataSet, std::vector<Vertex>& verticesOut, std::vector<unsigned int>& indicesOut, RenderingSystem* driver, const VisualizationOptions& options);
	};
}

#endif
