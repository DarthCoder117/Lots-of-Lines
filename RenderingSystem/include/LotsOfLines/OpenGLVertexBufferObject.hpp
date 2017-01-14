#ifndef OPENGL_VERTEX_BUFFER_OBJECT_HPP
#define OPENGL_VERTEX_BUFFER_OBJECT_HPP
#include "LotsOfLines/OpenGLRenderer.hpp"
#include "LotsOfLines/IVertexBufferObject.hpp"

namespace LotsOfLines
{
	class OpenGLVertexBufferObject : public IVertexBufferObject
	{
	public:

		~OpenGLVertexBufferObject();
		
		bool init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

		void draw();

	private:

		unsigned int m_vertexBuffer;

		unsigned int m_indexBuffer;
		unsigned int m_indexCount = 0;
	};
}

#endif