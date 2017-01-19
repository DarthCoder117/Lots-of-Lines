#include "LotsOfLines/OpenGLRenderer.hpp"
#include "LotsOfLines/OpenGLVertexBufferObject.hpp"
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace LotsOfLines;

static const char* vertex_shader_text =
"#version 330 core\n"
"uniform mat4 MVP;\n"
"in vec3 pos;\n"
"in vec3 vertexColor;\n"
"out vec3 fragmentColor;\n"
"void main()\n"
"{\n"
"   gl_Position = MVP * vec4(pos, 1.0);\n"
"	fragmentColor = vertexColor;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330 core\n"
"in vec3 fragmentColor;"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    color = fragmentColor;\n"
"}\n";

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Set static vars
bool OpenGLRenderer::m_lockZoomX = false;
bool OpenGLRenderer::m_lockZoomY = false;

OpenGLRenderer::OpenGLRenderer()
{
	//Initialize the library
	if (!glfwInit()) return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//Create a windowed mode window and its OpenGL context
	m_window = glfwCreateWindow(1024, 768, "OpenGL test", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return;
	}
	glfwSetWindowUserPointer(m_window, this);

	glfwSetMouseButtonCallback(m_window, onMouseButton);
	glfwSetScrollCallback(m_window, onMouseScroll);
	glfwSetWindowSizeCallback(m_window, windowSizeCallback);

	//Make the window's context current
	glfwMakeContextCurrent(m_window);
	//Init GLEW so that we can use modern OpenGL on Windows
	if (glewInit() != GLEW_OK)
	{
		return;
	}

	initShaders();
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
	glfwTerminate();
}

bool OpenGLRenderer::run()
{
	return !glfwWindowShouldClose(m_window);
}

void OpenGLRenderer::beginDraw(float r, float g, float b)
{
	//Calculate frame time
	double currentTime = glfwGetTime();
	m_deltaTime = currentTime - m_lastTime;
	m_lastTime = currentTime;

	//Clear frame buffer
	glClearColor(r, g, b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Set shader program
	glUseProgram(m_program);

	//Setup matrices for pan/zoom
	glm::mat4x4 zoom = glm::scale(glm::mat4x4(), glm::vec3(m_zoomX, m_zoomY, 0.0f));
	glm::mat4x4 translate = glm::translate(glm::mat4x4(), glm::vec3(-m_camX, -m_camY, 0.0f));
	glm::mat4x4 mvp = zoom * translate;

	GLuint MatrixID = glGetUniformLocation(m_program, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void OpenGLRenderer::endDraw()
{
	//Swap front and back buffers
	glfwSwapBuffers(m_window);

	//Poll for and process events
	glfwPollEvents();
	updateInput();
}

void OpenGLRenderer::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	OpenGLRenderer* renderer = (OpenGLRenderer*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		glfwGetCursorPos(window, &renderer->m_lastMouseX, &renderer->m_lastMouseY);

		if (action == GLFW_PRESS)
		{
			renderer->m_mouseDown = true;
		}
		else if (action == GLFW_RELEASE)
		{
			renderer->m_mouseDown = false;
		}
	}
}

void OpenGLRenderer::onMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	OpenGLRenderer* renderer = (OpenGLRenderer*)glfwGetWindowUserPointer(window);

	float offset = (float)(renderer->m_deltaTime * yoffset * 20);
	renderer->m_zoomX = m_lockZoomX ? renderer->m_zoomX : std::fmaxf(renderer->m_zoomX + offset, 0.0f);
	renderer->m_zoomY = m_lockZoomY ? renderer->m_zoomY : std::fmaxf(renderer->m_zoomY + offset, 0.0f);
}

void OpenGLRenderer::updateInput()
{
	if (m_mouseDown)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(m_window, &mouseX, &mouseY);

		double mouseDeltaX = m_lastMouseX - mouseX;
		double mouseDeltaY = mouseY - m_lastMouseY;

		m_camX += m_lockPanX ? 0.0f : (float)(mouseDeltaX * m_deltaTime * 3);
		m_camY += m_lockPanY ? 0.0f : (float)(mouseDeltaY * m_deltaTime * 15);

		m_lastMouseX = mouseX;
		m_lastMouseY = mouseY;
	}
}

void OpenGLRenderer::setViewTransform(float camX, float camY, float zoomX, float zoomY)
{
	m_camX = camX;
	m_camY = camY;
	m_zoomX = zoomX;
	m_zoomY = zoomY;
}

void OpenGLRenderer::setNavigationOptions(bool lockZoomX, bool lockZoomY, bool lockPanX, bool lockPanY)
{
	m_lockZoomX = lockZoomX;
	m_lockZoomY = lockZoomY;
	m_lockPanX = lockPanX;
	m_lockPanY = lockPanY;
}

void OpenGLRenderer::drawVBO(std::shared_ptr<IVertexBufferObject> vbo)
{
	glBlendFunc(GL_ONE, GL_ONE);

	std::static_pointer_cast<OpenGLVertexBufferObject, IVertexBufferObject>(vbo)->draw();
}

std::shared_ptr<IVertexBufferObject> OpenGLRenderer::createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	std::shared_ptr<OpenGLVertexBufferObject> buffer = std::make_shared<OpenGLVertexBufferObject>();
	if (buffer->init(vertices, indices)) return buffer;

	return nullptr;
}
