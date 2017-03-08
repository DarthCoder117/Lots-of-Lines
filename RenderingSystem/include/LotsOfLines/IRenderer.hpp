#ifndef I_RENDERER_H
#define I_RENDERER_H
#include "LotsOfLines/IVertexBufferObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

namespace LotsOfLines
{
	enum E_VERTEX_STATE_FLAGS
	{
		EVSF_SELECTED = 0x01,
		EVSF_HIDDEN = 0x02,
		EVSF_DRAW_POINT = 0x04
	};

	///@brief Vertex structure for storing data to be sent to OpenGL for rendering
	struct Vertex
	{
		Vertex(float x, float y, unsigned int lineIdx)
			:x(x), y(y), z(0.0f),
			dataClassIndex(0),
			flags(0),
			lineIndex(lineIdx)
		{}

		float x, y, z;
		std::uint32_t dataClassIndex; ///< Index of data class this vertice's data belongs to
		std::uint32_t flags;///< Vertex state flags
		std::uint32_t lineIndex;///< Index of line
	};

	class RenderingSystem;
	class IShader;

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

		///@brief Set model*view*projection matrix.
		virtual void setModelViewProjection(const glm::mat4x4& mvp) = 0;
		///@return The currently set model*view*projection matrix.
		virtual const glm::mat4x4& getModelViewProjection() const = 0;

		///@brief Create a new shader object.
		virtual IShader* createShader() = 0;
		///@brief Set the shader program to draw with.
		virtual void setShader(IShader* shader) = 0;

		///@brief Draw a VBO to the screen.
		///@param lines Whether to draw as lines or points.
		virtual void drawVBO(std::shared_ptr<IVertexBufferObject> vbo, bool lines = true) = 0;

		///@brief Construct a VBO from a list of vertices and indices.
		virtual std::shared_ptr<IVertexBufferObject> createVBO(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) = 0;
	};
}

#endif