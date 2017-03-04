#include "LotsOfLines/OpenGLVertexBufferObject.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace LotsOfLines;

OpenGLVertexBufferObject::~OpenGLVertexBufferObject()
{

}

bool OpenGLVertexBufferObject::init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	m_vertexCount = vertices.size();
	m_indexCount = indices.size();

	//Vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_DYNAMIC_COPY);

	//Index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_indexCount, &indices[0], GL_STATIC_DRAW);

	return true;
}

void OpenGLVertexBufferObject::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	size_t offset = 0;
	glVertexAttribPointer(
		0,                  // attribute 0.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(Vertex),                  // stride
		(void*)offset           // array buffer offset
	);
	offset += sizeof(float) * 3;

	glVertexAttribIPointer(
		1,                  // attribute 1.
		1,                  // size
		GL_UNSIGNED_INT,           // type
		sizeof(Vertex),                  // stride
		(void*)offset            // array buffer offset
	);
	offset += sizeof(unsigned int);

	glVertexAttribIPointer(
		2,                  // attribute 2.
		1,                  // size
		GL_UNSIGNED_INT,    // type 
		sizeof(Vertex),                 // stride
		(void*)offset            // array buffer offset
	);
	offset += sizeof(unsigned int);

	glDrawElements(GL_LINES, m_indexCount, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

Vertex* OpenGLVertexBufferObject::mapVertices(bool readOnly)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	return (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, readOnly ? GL_READ_ONLY : GL_READ_WRITE);
}

void OpenGLVertexBufferObject::unmapVertices()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

unsigned int OpenGLVertexBufferObject::vertexCount() const
{
	return m_vertexCount;
}

unsigned int OpenGLVertexBufferObject::indexCount() const
{
	return m_indexCount;
}
