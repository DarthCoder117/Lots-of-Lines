#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP
#include "LotsOfLines/IRenderer.hpp"

struct GLFWwindow;

namespace LotsOfLines
{
	///@brief Renderer implementation for drawing visualizations using OpenGL.
	class OpenGLRenderer : public IRenderer
	{
	public:

		OpenGLRenderer();

		~OpenGLRenderer();

		bool run();

		void beginDraw(float r, float g, float b);

		void endDraw();

		void setViewTransform(float camX, float camY, float zoomX, float zoomY);

		void drawVBO(std::shared_ptr<IVertexBufferObject> vbo);

		std::shared_ptr<IVertexBufferObject> createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	private:

		void initShaders();

		void updateInput();

		GLFWwindow* m_window;

		unsigned int m_program;

		float m_camX = 0.0f;
		float m_camY = 0.0f;
		float m_zoomX = 1.0f;
		float m_zoomY = 1.0f;

		double m_lastTime = 0.0;
		double m_deltaTime = 0.0;

		static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
		static void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);

		bool m_mouseDown = false;
		double m_lastMouseX = 0.0;
		double m_lastMouseY = 0.0;
	};
}

#endif
