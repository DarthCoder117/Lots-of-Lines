#include "LotsOfLines/OpenGLVertexBufferObject.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace LotsOfLines;

OpenGLVertexBufferObject::~OpenGLVertexBufferObject()
{

}

bool OpenGLVertexBufferObject::init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	//Vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//Index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	m_indexCount = indices.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_indexCount, &indices[0], GL_STATIC_DRAW);

	return true;
}

void OpenGLVertexBufferObject::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(float) * 6,                  // stride
		(void*)0            // array buffer offset
	);

	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		24,                  // stride
		(void*)(sizeof(float) * 3)            // array buffer offset
	);

	glDrawElements(GL_LINES, m_indexCount, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}