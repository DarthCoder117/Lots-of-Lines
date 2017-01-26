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
			r(1.0f), g(0.5f), b(0.5f),
			lineIndex(0)
		{}

		float x, y, z;
		float r, g, b;
		std::uint32_t lineIndex;
	};

	class IRenderer
	{
	public:

		virtual ~IRenderer() {}

		///@return Returns true while the window should be shown.
		virtual bool run() = 0;

		///@brief Sets up rendering states to begin a frame.
		virtual void beginDraw(float r, float g, float b) = 0;

		///@brief Flips buffers to screen.
		virtual void endDraw() = 0;

		///@brief Set pan/zoom the view.
		virtual void setViewTransform(float camX, float camY, float zoomX, float zoomY) = 0;

		///@brief Set pan/zoom options
		virtual void setNavigationOptions(bool lockZoomX, bool lockZoomY, bool lockPanX, bool lockPanY) = 0;

		///@brief Draw a VBO to the screen.
		virtual void drawVBO(std::shared_ptr<IVertexBufferObject> vbo) = 0;

		virtual void setSelectedLine(unsigned int selectedLine) = 0;

		///@brief Construct a VBO from a list of vertices and indices.
		virtual std::shared_ptr<IVertexBufferObject> createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) = 0;
	};
}

#endif