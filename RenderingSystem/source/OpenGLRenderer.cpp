#include "LotsOfLines/OpenGLRenderer.hpp"
#include "LotsOfLines/OpenGLVertexBufferObject.hpp"
#include "LotsOfLines/RenderingSystem.hpp"
#include "LotsOfLines/OpenGLShader.hpp"
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <ctime>

using namespace LotsOfLines;

OpenGLRenderer::OpenGLRenderer()
{
	
}

OpenGLRenderer::~OpenGLRenderer()
{
	
}

void APIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::string severityStr = "Notification";
	if (severity == GL_DEBUG_SEVERITY_HIGH)
	{
		severityStr = "High";
	}
	else if (severity == GL_DEBUG_SEVERITY_MEDIUM)
	{
		severityStr = "Medium";
	}
	else if (severity == GL_DEBUG_SEVERITY_LOW)
	{
		severityStr = "Low";
	}

	std::cout << "(" << severityStr << ") " << message << "\n";
}

bool OpenGLRenderer::init()
{
	//Init GLEW so that we can use modern OpenGL on Windows
	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	std::string versionInfo = "";
	versionInfo.append((const char*)glGetString(GL_VERSION)).append("\n");
	versionInfo.append((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)).append("\n");
	versionInfo.append((const char*)glGetString(GL_VENDOR)).append("\n");
	int count = 0; 
	glGetIntegerv(GL_NUM_EXTENSIONS, &count);
	for (int i = 0; i < count; ++i)
	{
		versionInfo.append((const char*)glGetStringi(GL_EXTENSIONS, i)).append("\n");
	}
	printf(versionInfo.c_str());

	//Enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(errorCallback, nullptr);

	//Enable scissor test so that splitscreen works.
	glEnable(GL_SCISSOR_TEST);

	return true;
}

void OpenGLRenderer::clearScreen(float r, float g, float b)
{
	//Clear frame buffer
	glClearColor(r, g, b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::beginDraw()
{

}

void OpenGLRenderer::endDraw()
{
	
}

void OpenGLRenderer::setClassColors(float* colors)
{
	m_dataClassColors = colors;
}

void OpenGLRenderer::setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	glViewport(x, y, width, height);
	glScissor(x, y, width, height);
}

void OpenGLRenderer::setModelViewProjection(const glm::mat4x4& mvp)
{
	m_modelViewProj = mvp;
}

const glm::mat4x4& OpenGLRenderer::getModelViewProjection() const
{
	return m_modelViewProj;
}

IShader* OpenGLRenderer::createShader()
{
	return new OpenGLShader();
}

void OpenGLRenderer::setShader(IShader* shader)
{
	if (shader)
	{
		unsigned int program = ((OpenGLShader*)shader)->getProgram();
		glUseProgram(program);

		//Set uniforms
		GLint MatrixID = glGetUniformLocation(program, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &m_modelViewProj[0][0]);

		GLint dataClassColorsID = glGetUniformLocation(program, "dataClassColors");
		if (m_dataClassColors)
		{
			glUniform3fv(dataClassColorsID, 10, (float*)m_dataClassColors);
		}
	}
	else
	{
		glUseProgram(0);
	}
}

void OpenGLRenderer::drawVBO(std::shared_ptr<IVertexBufferObject> vbo, bool lines)
{
	std::static_pointer_cast<OpenGLVertexBufferObject, IVertexBufferObject>(vbo)->draw(lines);
}

std::shared_ptr<IVertexBufferObject> OpenGLRenderer::createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	std::shared_ptr<OpenGLVertexBufferObject> buffer = std::make_shared<OpenGLVertexBufferObject>();
	if (buffer->init(vertices, indices)) return buffer;

	return nullptr;
}
