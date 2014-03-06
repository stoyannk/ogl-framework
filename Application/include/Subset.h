#pragma once

#include "OGLPtrsDecls.h"

namespace oglwork
{

class APP_EXPORTED_SYMBOL Subset
{
public:
	Subset();

	const Buffer& GetIndexBuffer() const { return m_IndexBuffer; }
	const VAO& GetVAO() const { return m_VAO; }

	void SetIndexBufferData(GLenum type, unsigned count, const GLuint* indices);

	void Draw();

private:
	Buffer m_IndexBuffer;
	VAO m_VAO;

	GLenum m_Primitive;
	unsigned m_PrimitiveCount;
};

typedef std::vector<Subset> SubsetsVec;

}