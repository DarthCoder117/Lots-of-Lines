#ifndef SHADERS_HPP
#define SHADERS_HPP
#include "RenderingSystem/IRenderer.hpp"
#include "RenderingSystem/IShader.hpp"
#include <string>

namespace LotsOfLines
{
	class Shaders
	{
	public:

		///@brief Called at init time by the rendering system to build all the shaders
		static bool compileShaders(IRenderer* driver);

		static IShader* defaultVisualization;
		static IShader* selectedLine;
		static IShader* point;
	};
}

#endif
