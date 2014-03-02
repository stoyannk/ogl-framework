#include "stdafx.h"

#include <OGLPtrs.h>

namespace oglwork
{

#define DECLARE_RESOURCE_TRAIT(TRAIT) \
	template APP_EXPORTED_SYMBOL class OGLResource<TRAIT>;

DECLARE_RESOURCE_TRAIT(buffer_trait)
DECLARE_RESOURCE_TRAIT(texture_trait)
DECLARE_RESOURCE_TRAIT(vao_trait)
DECLARE_RESOURCE_TRAIT(program_trait)

}