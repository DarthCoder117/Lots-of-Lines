#ifndef I_VERTEX_BUFFER_OBJECT_HPP
#define I_VERTEX_BUFFER_OBJECT_HPP

namespace LotsOfLines
{
	struct Vertex;

	///@brief Interface for creating vertex/index buffer (OpenGL VBO)
	///Vertex Buffer Objects should only be constructed through the IRenderer interface.
	class IVertexBufferObject
	{
	public:

		virtual ~IVertexBufferObject() {}

		///@brief Map the vertex buffer for access.
		///@return A pointer to the vertex buffer's data, or NULL if the buffer couldn't be mapped.
		virtual Vertex* mapVertices(bool readOnly = 0) = 0;
		///@brief Unmap (unlock) the vertex buffer after accessing it.
		virtual void unmapVertices() = 0;

		virtual unsigned int vertexCount() const = 0;
		virtual unsigned int indexCount() const = 0;
	};
}

#endif