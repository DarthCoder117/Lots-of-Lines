#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H
//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "LotsOfLines/IRenderer.hpp"

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
