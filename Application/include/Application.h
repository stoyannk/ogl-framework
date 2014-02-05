#pragma once

namespace oglwork
{

class RenderSystem;

struct APP_EXPORTED_SYMBOL AppParams
{
	const char* Name;
	unsigned Width;
	unsigned Height;
	bool Fullscreen;
	bool VSync;
};

class APP_EXPORTED_SYMBOL Application
{
public:
	Application();

	virtual bool Initialize(const AppParams& params);
	virtual void Log(int category, SDL_LogPriority priority, const char* message);
	void Run();

	virtual ~Application();

	virtual void Update(double dtSeconds) = 0;
	
	RenderSystem* GetRenderSystem() const;

private:
	Application(const Application&);
	Application& operator=(const Application&);

	AppParams m_InitParams;
	std::ofstream m_Log;

	SDL_Window* m_Window;

	SDL_GLContext m_OglContext;

	std::unique_ptr<RenderSystem> m_RenderSystem;

	unsigned long long m_PerfFrequency;
	unsigned long long m_LastFrameCounter;

	bool m_Quit;
};

}