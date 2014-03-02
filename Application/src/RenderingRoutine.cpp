#include "stdafx.h"

#include <RenderingRoutine.h>

namespace oglwork
{

void RenderingRoutine::SetSystem(RenderSystem* system)
{
	m_System = system;
}

RenderingRoutine::~RenderingRoutine()
{}

void RenderingRoutine::PreDraw(double dt)
{}

void RenderingRoutine::PostDraw(double dt)
{}

}
