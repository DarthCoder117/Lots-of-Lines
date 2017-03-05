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

		bool init();

		void clearScreen(float r, float g, float b);

		void beginDraw();

		void endDraw();

		void setClassColors(float* colors);

		void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

		void setModelViewProjection(const glm::mat4x4& mvp);

		IShader* createShader();
		void setShader(IShader* shader);

		void drawVBO(std::shared_ptr<IVertexBufferObject> vbo);

		void setSelectedLine(unsigned int selectedLine);

		std::shared_ptr<IVertexBufferObject> createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	private:

		float* m_dataClassColors;///< 10x3 array of floats

		void initShaders();

		unsigned int m_program;

		glm::mat4x4 m_modelViewProj;

		unsigned int m_selectedLine = 0;
	};
}

#endif
