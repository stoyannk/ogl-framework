#include "stdafx.h"

#include <Mesh.h>

namespace oglwork
{

Mesh::Mesh()
{}

Mesh::Mesh(const VertexAttributesVec& attributes)
	: m_Attributes(attributes)
{}

Buffer& Mesh::AddVertexBuffer()
{
	m_VertexBuffers.push_back(Buffer());
	m_VertexBuffers.back().Generate();

	return m_VertexBuffers.back();
}

void Mesh::AddSubset(const Subset& subset)
{
	m_Subsets.push_back(subset);
}

void Mesh::BindVertexAttributes()
{
	oglwork::BindVertexAttributes(m_Attributes, m_VertexBuffers);
}

}