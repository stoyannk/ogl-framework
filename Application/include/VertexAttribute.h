#pragma once

namespace oglwork
{

struct VertexAttribute
{
	GLint Size;
	GLenum Type;
	GLboolean Normalized;
	GLsizei Stride;

	GLint VertexBufferBinding;
};

}
