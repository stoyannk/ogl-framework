#include "stdafx.h"
#include "../include/RenderSystem.h"

namespace oglwork
{

RenderSystem::RenderSystem(SDL_Window* window)
	: m_Window(window)
{}

void RenderSystem::Draw(double dt)
{
	SDL_GL_SwapWindow(m_Window);
}

}
