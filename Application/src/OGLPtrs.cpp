#include "stdafx.h"

#include "../include/OGLPtrs.h"

namespace oglwork
{

#define DECLARE_RESOURCE_TRAIT(TRAIT) \
	APP_EXPORTED_SYMBOL void(__stdcall* OGLResource<TRAIT>::Gen)(GLsizei, GLuint*) = 0; \
	APP_EXPORTED_SYMBOL void(__stdcall* OGLResource<TRAIT>::Delete)(GLsizei, const GLuint*) = 0; \
	template APP_EXPORTED_SYMBOL class OGLResource<TRAIT>;

DECLARE_RESOURCE_TRAIT(buffer_trait)
DECLARE_RESOURCE_TRAIT(texture_trait)
DECLARE_RESOURCE_TRAIT(vao_trait)

void SetResourceFunctionPointers()
{
	OGLResource<buffer_trait>::Gen = glGenBuffers;
	OGLResource<buffer_trait>::Delete = glDeleteBuffers;

	OGLResource<texture_trait>::Gen = glGenTexturesEXT;
	OGLResource<texture_trait>::Delete = glDeleteTexturesEXT;

	OGLResource<vao_trait>::Gen = glGenVertexArrays;
	OGLResource<vao_trait>::Delete = glDeleteVertexArrays;
}

}