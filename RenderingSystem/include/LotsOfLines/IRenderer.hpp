#ifndef I_RENDERER_H
#define I_RENDERER_H
#include "LotsOfLines/IVertexBufferObject.hpp"
#include <vector>
#include <memory>

namespace LotsOfLines
{
	struct Vertex
	{
		Vertex(float x, float y)
			:x(x), y(y), z(0.0f),
			dataClassIndex(0),
			lineIndex(0)
		{}

		float x, y, z;
		std::uint32_t dataClassIndex;
		std::uint32_t lineIndex;
	};

	class RenderingSystem;

	class IRenderer
	{
	protected:

		RenderingSystem* m_renderingSystem;

		friend class RenderingSystem;

	public:

		virtual ~IRenderer() {}

		///@brief Initialize the rendering driver by setting up default shaders and rendering states.
		virtual bool init() = 0;

		///@brief Clears the screen before re-rendering.
		virtual void clearScreen(float r, float g, float b) = 0;

		///@brief Sets up rendering states to begin a frame.
		virtual void beginDraw() = 0;

		///@brief Flips buffers to screen.
		virtual void endDraw() = 0;

		///@brief Set the 10x3 array of floats for colors to use when rendering the data class.
		virtual void setClassColors(float* colors) = 0;

		///@brief Set the viewport
		virtual void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

		///@brief Set pan/zoom the view.
		virtual void setViewTransform(float camX, float camY, float zoomX, float zoomY) = 0;

		///@brief Draw a VBO to the screen.
		virtual void drawVBO(std::shared_ptr<IVertexBufferObject> vbo) = 0;

		///@brief Sets the line that will be drawn as selected.
		virtual void setSelectedLine(unsigned int selectedLine) = 0;

		///@brief Construct a VBO from a list of vertices and indices.
		virtual std::shared_ptr<IVertexBufferObject> createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) = 0;
	};
}

#endif