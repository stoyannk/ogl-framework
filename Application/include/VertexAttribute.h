#pragma once

#include "OGLPtrsDecls.h"

namespace oglwork
{

struct VertexAttribute
{
	GLint Size;
	GLenum Type;
	GLboolean Normalized;
	GLsizei Stride;
	GLsizei Offset;
	GLboolean PreserveInteger;

	GLint VertexBufferBinding;
};

typedef std::vector<VertexAttribute> VertexAttributesVec;

void APP_EXPORTED_SYMBOL BindVertexAttributes(
	const VertexAttributesVec& vertexAttributes,
	const std::vector<Buffer>& vertexBuffers);

}
