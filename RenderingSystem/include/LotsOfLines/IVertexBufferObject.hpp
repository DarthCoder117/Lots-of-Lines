#ifndef I_VERTEX_BUFFER_OBJECT_HPP
#define I_VERTEX_BUFFER_OBJECT_HPP

namespace LotsOfLines
{
	///@brief Interface for creating vertex/index buffer (OpenGL VBO)
	///Vertex Buffer Objects should only be constructed through the IRenderer interface.
	class IVertexBufferObject
	{
	public:

		virtual ~IVertexBufferObject() {}
	};
}

#endif