#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H
#include "LotsOfLines/IRenderer.hpp"

struct GLFWwindow;

namespace LotsOfLines
{
	///@brief Renderer implementation for drawing visualizations using OpenGL.
	class OpenGLRenderer : public IRenderer
	{
	public:

		OpenGLRenderer();

	private:

		GLFWwindow* window;
	};
}

#endif
