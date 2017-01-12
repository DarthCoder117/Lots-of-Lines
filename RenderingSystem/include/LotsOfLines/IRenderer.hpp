#ifndef I_RENDERER_H
#define I_RENDERER_H
#include "LotsOfLines/IVertexBufferObject.hpp"
#include <vector>
#include <memory>

namespace LotsOfLines
{
	struct float3
	{
		float3(float x, float y, float z)
			:x(x), y(y), z(z)
		{}

		float x, y, z = 0.0f;
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

		///@brief Draw a VBO to the screen.
		virtual void drawVBO(std::shared_ptr<IVertexBufferObject> vbo) = 0;

		///@brief Construct a VBO from a list of vertices and indices.
		virtual std::shared_ptr<IVertexBufferObject> createVBO(const std::vector<float3>& vertices, const std::vector<unsigned int>& indices) = 0;
	};
}

#endif