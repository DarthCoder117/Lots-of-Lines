#include "LotsOfLines/OpenGLRenderer.hpp"
#include "LotsOfLines/OpenGLVertexBufferObject.hpp"
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

void OpenGLRenderer::initShaders()
{
	//TODO: Load default shaders here...
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

void OpenGLRenderer::drawVBO(std::shared_ptr<IVertexBufferObject> vbo)
{
	std::static_pointer_cast<OpenGLVertexBufferObject, IVertexBufferObject>(vbo)->draw();
}

std::shared_ptr<IVertexBufferObject> OpenGLRenderer::createVBO(const std::vector<float3>& vertices, const std::vector<unsigned int>& indices)
{
	std::shared_ptr<OpenGLVertexBufferObject> buffer = std::make_shared<OpenGLVertexBufferObject>();
	if (buffer->init(vertices, indices)) return buffer;

	return nullptr;
}
