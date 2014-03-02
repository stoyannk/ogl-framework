#pragma once

#include "OGLPtrsDecls.h"

namespace oglwork
{

class APP_EXPORTED_SYMBOL ShaderCompiler
{
public:
	struct APP_EXPORTED_SYMBOL ShaderSourceFiles
	{
		std::string Vertex;
		std::string Tesselation;
		std::string Evaluation;
		std::string Geometry;
		std::string Fragment;

		std::string Compute;
	};

	static Program CreateProgramFromFiles(const ShaderSourceFiles& sourceFiles, std::string& error);
};

}