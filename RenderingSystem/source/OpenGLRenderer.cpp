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

static const char* vertex_shader_text =
"#version 330 core\n"

"const uint SELECTED = 0x01;\n"
"const uint HIDDEN = 0x02;\n"

"uniform mat4 MVP;\n"
"uniform vec3 dataClassColors[10];\n"

"layout(location = 0) in vec3 pos;\n"
"layout(location = 1) in uint classIndex;\n"
"layout(location = 2) in uint flags;\n"

"out vec3 fragmentColor;\n"
"out uint fragmentFlags;"
"void main()\n"
"{\n"
"   gl_Position = MVP * vec4(pos, 1.0);\n"

"	if (flags & SELECTED)\n"
"	{\n"
"		fragmentColor = vec3(1.0);\n"
"	}\n"
"	else\n"
"	{\n"
"		fragmentColor = dataClassColors[classIndex];\n"
"	}\n"
"   fragmentFlags = flags;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330 core\n"
"in vec3 fragmentColor;"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    color = fragmentColor;\n"
"}\n";

OpenGLRenderer::OpenGLRenderer()
{
	
}

void OpenGLRenderer::initShaders()
{
	//Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
 	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);
		std::cout << errorLog.data() << "\n";

		glDeleteShader(vertexShader);
		return;
	}

	//Pixel shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragmentShader);

	isCompiled = 0;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);
		std::cout << errorLog.data() << "\n";

		glDeleteShader(fragmentShader); 
		return;
	}

	//Link both shaders
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

	GLint isLinked = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_program, maxLength, &maxLength, &infoLog[0]);
		std::cout << infoLog.data() << "\n";

		//We don't need the program anymore.
		glDeleteProgram(m_program);
		//Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(m_program, vertexShader);
	glDetachShader(m_program, fragmentShader);
}

OpenGLRenderer::~OpenGLRenderer()
{
	
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

	initShaders();

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

		GLint selectedLineID = glGetUniformLocation(program, "selectedLine");
		glUniform1ui(selectedLineID, m_selectedLine);

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

void OpenGLRenderer::drawVBO(std::shared_ptr<IVertexBufferObject> vbo)
{
	std::static_pointer_cast<OpenGLVertexBufferObject, IVertexBufferObject>(vbo)->draw();
}

void OpenGLRenderer::setSelectedLine(unsigned int selectedLine)
{
	m_selectedLine++;
}

std::shared_ptr<IVertexBufferObject> OpenGLRenderer::createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	std::shared_ptr<OpenGLVertexBufferObject> buffer = std::make_shared<OpenGLVertexBufferObject>();
	if (buffer->init(vertices, indices)) return buffer;

	return nullptr;
}
