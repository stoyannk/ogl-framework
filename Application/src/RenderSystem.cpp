#include "stdafx.h"
#include <RenderSystem.h>

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

}
