#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP
#include "RenderingSystem/IRenderer.hpp"

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
		const glm::mat4x4& getModelViewProjection() const;

		IShader* createShader();
		void setShader(IShader* shader);

		void drawVBO(std::shared_ptr<IVertexBufferObject> vbo, bool lines);

		std::shared_ptr<IVertexBufferObject> createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	private:

		float* m_dataClassColors = nullptr;///< 10x3 array of floats

		glm::mat4x4 m_modelViewProj;
	};
}

#endif
