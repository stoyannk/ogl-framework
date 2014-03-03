#include "stdafx.h"

#include <ShaderCompiler.h>

#include <sstream>

namespace oglwork
{

bool ReadFile(const std::string& filename, std::string& output)
{
	std::ifstream fin(filename.c_str());

	if (!fin.is_open())
		return false;

	output.assign((std::istreambuf_iterator<char>(fin)),
					std::istreambuf_iterator<char>());

	return true;
}

struct ShaderScope
{
public:
	ShaderScope(GLenum type)
	{
		Object = glCreateShader(type);
	}

	~ShaderScope()
	{
		glDeleteShader(Object);
	}

	GLuint Object;
};

bool CompileFromFile(
	GLint object,
	const std::string& filename,
	const char* name,
	std::string& error)
{
	std::string content;
	std::ostringstream ostr;

	if (!ReadFile(filename, content))
	{
		error = "Unable to read file " + filename;
		return false;
	}

	const char* contentPtr = content.c_str();
	glShaderSource(object, 1, &contentPtr, nullptr);
	glCompileShader(object);
	GLint infoLogLen = 0;
	glGetShaderiv(object, GL_INFO_LOG_LENGTH, &infoLogLen);
	if (infoLogLen > 1)
	{
		std::string log;
		log.resize(infoLogLen);
		glGetShaderInfoLog(object, infoLogLen - 1, nullptr, &log[0]);

		ostr << name << " shader compilation output: " << log << std::endl;
	}
	GLint result = 0;
	glGetShaderiv(object, GL_COMPILE_STATUS, &result);

	error += ostr.str();

	return (result == GL_TRUE);
}

Program ShaderCompiler::CreateProgramFromFiles(
	const ShaderCompiler::ShaderSourceFiles& sourceFiles,
	std::string& error)
{
	Program result;
	result.Generate();

	std::string content;
	if (!sourceFiles.Vertex.empty())
	{
		ShaderScope scope(GL_VERTEX_SHADER);
		if (!CompileFromFile(scope.Object, sourceFiles.Vertex, "Vertex", error))
			return Program();

		glAttachShader(result.Get(), scope.Object);
	}
	if (!sourceFiles.Tesselation.empty())
	{
		ShaderScope scope(GL_TESS_CONTROL_SHADER);
		if (!CompileFromFile(scope.Object, sourceFiles.Tesselation, "Tesselation", error))
			return Program();

		glAttachShader(result.Get(), scope.Object);
	}
	if (!sourceFiles.Evaluation.empty())
	{
		ShaderScope scope(GL_TESS_EVALUATION_SHADER);
		if (!CompileFromFile(scope.Object, sourceFiles.Evaluation, "Evaluation", error))
			return Program();

		glAttachShader(result.Get(), scope.Object);
	}
	if (!sourceFiles.Geometry.empty())
	{
		ShaderScope scope(GL_GEOMETRY_SHADER);
		if (!CompileFromFile(scope.Object, sourceFiles.Geometry, "Geometry", error))
			return Program();

		glAttachShader(result.Get(), scope.Object);
	}
	if (!sourceFiles.Fragment.empty())
	{
		ShaderScope scope(GL_FRAGMENT_SHADER);
		if (!CompileFromFile(scope.Object, sourceFiles.Fragment, "Fragment", error))
			return Program();

		glAttachShader(result.Get(), scope.Object);
	}
	if (!sourceFiles.Compute.empty())
	{
		ShaderScope scope(GL_COMPUTE_SHADER);
		if (!CompileFromFile(scope.Object, sourceFiles.Compute, "Compute", error))
			return Program();

		glAttachShader(result.Get(), scope.Object);
	}

	glLinkProgram(result.Get());

	std::ostringstream ostr;
	GLint infoLogLen = 0;
	glGetProgramiv(result.Get(), GL_INFO_LOG_LENGTH, &infoLogLen);
	if (infoLogLen > 1)
	{
		std::string log;
		log.resize(infoLogLen);
		glGetProgramInfoLog(result.Get(), infoLogLen - 1, nullptr, &log[0]);

		ostr << "Program link output: " << log << std::endl;
	}

	error += ostr.str();

	GLint linkResult = 0;
	glGetProgramiv(result.Get(), GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		error += "Program link failed!";
		return Program();
	}

	return result;
}

}