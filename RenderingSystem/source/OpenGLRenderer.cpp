#include "LotsOfLines/OpenGLRenderer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace LotsOfLines;

OpenGLRenderer::OpenGLRenderer()
{
	//Initialize the library
	if (!glfwInit()) return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//Create a windowed mode window and its OpenGL context
	m_window = glfwCreateWindow(640, 480, "OpenGL test", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return;
	}

	//Make the window's context current
	glfwMakeContextCurrent(m_window);
	//Init GLEW so that we can use modern OpenGL on Windows
	if (glewInit() != GLEW_OK)
	{
		return;
	}
}

OpenGLRenderer::~OpenGLRenderer()
{
	glfwTerminate();
}

bool OpenGLRenderer::run()
{
	return !glfwWindowShouldClose(m_window);
}

void OpenGLRenderer::beginDraw(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::endDraw()
{
	//Swap front and back buffers
	glfwSwapBuffers(m_window);

	//Poll for and process events
	glfwPollEvents();
}
