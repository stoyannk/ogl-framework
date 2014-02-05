#pragma once

#include "RenderingRoutine.h"

namespace oglwork
{

class APP_EXPORTED_SYMBOL RenderSystem
{
public:
	RenderSystem(SDL_Window* window);
	void Draw(double dt);

	void AddRoutine(RenderingRoutine* routine);
	bool RemoveRoutine(RenderingRoutine* routine);
	void ClearRoutines();

private:
	SDL_Window* m_Window;
	std::vector<RenderingRoutine*> m_Routines;

	RenderSystem(const RenderSystem&);
	RenderSystem& operator=(const RenderSystem&);
};

}