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

		GLFWwindow* m_window;

		unsigned int m_program;

		float m_camX = 0.0f;
		float m_camY = 0.0f;
		float m_zoomX = 1.0f;
		float m_zoomY = 1.0f;
	};
}

#endif
