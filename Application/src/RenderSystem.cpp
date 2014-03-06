#include "stdafx.h"
#include <RenderSystem.h>
#include <VertexAttribute.h>

namespace oglwork
{

RenderSystem::RenderSystem(SDL_Window* window)
	: m_Window(window)
{}

void RenderSystem::Draw(double dt)
{
	std::for_each(m_Routines.begin(), m_Routines.end(),
		[dt](RenderingRoutine* routine) {
		routine->PreDraw(dt);
	});

	std::for_each(m_Routines.begin(), m_Routines.end(),
		[dt](RenderingRoutine* routine) {
		routine->Draw(dt);
	});

	SDL_GL_SwapWindow(m_Window);

	std::for_each(m_Routines.begin(), m_Routines.end(),
		[dt](RenderingRoutine* routine) {
		routine->PostDraw(dt);
	});
}

void RenderSystem::AddRoutine(RenderingRoutine* routine)
{
	routine->SetSystem(this);
	m_Routines.push_back(routine);
}

bool RenderSystem::RemoveRoutine(RenderingRoutine* routine)
{
	auto rit = std::find(m_Routines.begin(), m_Routines.end(), routine);

	if (rit == m_Routines.cend())
		return false;

	(*rit)->SetSystem(nullptr);

	m_Routines.erase(rit);

	return true;
}

void RenderSystem::ClearRoutines()
{
	m_Routines.clear();
}

void BindVertexAttributes(
	const VertexAttributesVec& vertexAttributes,
	const std::vector<Buffer>& vertexBuffers)
{
	unsigned arrayId = 0;
	for (auto bufId = 0u; bufId < vertexBuffers.size(); ++bufId)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[bufId].Get());
		auto attribId = 0u;
		for (auto i = 0u; i < vertexAttributes.size(); ++i)
		{
			const auto& attribute = vertexAttributes[i];
			if (attribute.VertexBufferBinding != bufId)
				continue;

			if (attribute.PreserveInteger)
			{
				glVertexAttribIPointer(attribId, attribute.Size, attribute.Type, attribute.Stride, (GLvoid *)attribute.Offset);
			}
			else
			{
				glVertexAttribPointer(attribId, attribute.Size, attribute.Type, attribute.Normalized, attribute.Stride, (GLvoid *)attribute.Offset);
			}

			glEnableVertexAttribArray(arrayId++);

			attribId++;
		}
	}
}

}
