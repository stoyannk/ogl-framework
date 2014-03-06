#include "stdafx.h"

#include <Subset.h>

namespace oglwork
{

Subset::Subset()
	: m_Primitive(0)
	, m_PrimitiveCount(0)
{
	m_IndexBuffer.Generate();
	m_VAO.Generate();
}

void Subset::SetIndexBufferData(GLenum type, unsigned count, const GLuint* indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer.Get());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		count * sizeof(GLuint),
		indices,
		GL_STATIC_DRAW);
	CHECK_GL_ERROR;

	m_Primitive = type;
	m_PrimitiveCount = count;
}

void Subset::Draw()
{
	glBindVertexArray(m_VAO.Get());
	glDrawElements(m_Primitive, m_PrimitiveCount, GL_UNSIGNED_INT, 0);

	CHECK_GL_ERROR;
}

}