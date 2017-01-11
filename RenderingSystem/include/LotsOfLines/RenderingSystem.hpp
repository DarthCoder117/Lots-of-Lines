#ifndef DATE_MODEL_H
#define DATA_MODEL_H
#include "LotsOfLines/DataModel.hpp"
#include <vector>

namespace LotsOfLines
{
	class IRenderer;

	enum E_VISUALIZATION_TYPE
	{
		EVT_PARALLEL_COORDINATES
	};

	///@brief The RenderingSystem manages different drivers to render with and handles all visualization rendering.
	class RenderingSystem
	{
	public:

		RenderingSystem(IRenderer* driver);
	
		IRenderer* getDriver() const;

		bool run();

		void beginDraw(float r = 0.6f, float g = 0.6f, float b = 1.0f);

		void endDraw();

	private:

		IRenderer* m_driver;
	};
}

#endif