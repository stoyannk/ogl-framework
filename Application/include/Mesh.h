#pragma once

#include "OGLPtrsDecls.h"
#include "VertexAttribute.h"
#include "Subset.h"

namespace oglwork
{

class APP_EXPORTED_SYMBOL Mesh
{
public:
	Mesh();
	Mesh(const VertexAttributesVec& attributes);

	BuffersVec& GetVertexBuffers() { return m_VertexBuffers; }
	Buffer& AddVertexBuffer();
	VertexAttributesVec& GetAttributes() { return m_Attributes; }

	SubsetsVec& GetSubsets() { return m_Subsets; }
	void AddSubset(const Subset& subset);

	void BindVertexAttributes();

private:
	BuffersVec m_VertexBuffers;
	VertexAttributesVec m_Attributes;
	SubsetsVec m_Subsets;
};

}