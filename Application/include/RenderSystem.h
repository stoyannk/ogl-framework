#pragma once

namespace oglwork
{

class APP_EXPORTED_SYMBOL RenderSystem
{
public:
	RenderSystem(SDL_Window* window);
	void Draw(double dt);

private:
	SDL_Window* m_Window;

	RenderSystem(const RenderSystem&);
	RenderSystem& operator=(const RenderSystem&);
};

}