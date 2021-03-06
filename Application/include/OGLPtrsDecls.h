#pragma once

#include "OGLPtrs.h"

namespace oglwork
{

extern template APP_EXPORTED_SYMBOL class OGLResource<buffer_trait>;
typedef OGLResource<buffer_trait> Buffer;
typedef std::vector<Buffer> BuffersVec;

extern template APP_EXPORTED_SYMBOL class OGLResource<texture_trait>;
typedef OGLResource<texture_trait> Texture;

extern template APP_EXPORTED_SYMBOL class OGLResource<vao_trait>;
typedef OGLResource<vao_trait> VAO;

extern template APP_EXPORTED_SYMBOL class OGLResource<program_trait>;
typedef OGLResource<program_trait> Program;

}