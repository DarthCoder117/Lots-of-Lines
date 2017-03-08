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

		Vertex* mapVertices(bool readOnly = false);
		void unmapVertices();

		unsigned int* mapIndices();
		void unmapIndices();

		unsigned int vertexCount() const;
		unsigned int indexCount() const;

		void draw(bool lines = true);

	private:

		unsigned int m_vertexBuffer;
		unsigned int m_vertexCount;

		unsigned int m_indexBuffer;
		unsigned int m_indexCount = 0;
	};
}

#endif