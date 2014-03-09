#pragma once

namespace oglwork
{

class RenderSystem;

struct APP_EXPORTED_SYMBOL AppParams
{
	AppParams()
		: Name("")
		, Width(1280)
		, Height(720)
		, MultisampleCount(0)
		, LogPriority(SDL_LOG_PRIORITY_INFO)
		, Fullscreen(false)
		, VSync(true)
		, sRGB(false)
		#ifdef _DEBUG
		, EnableDebugOutput(true)
		#else
		, EnableDebugOutput(false)
		#endif
	{}

	const char* Name;
	unsigned Width;
	unsigned Height;
	unsigned MultisampleCount;
	SDL_LogPriority LogPriority;
	bool Fullscreen;
	bool VSync;
	bool sRGB;
	bool EnableDebugOutput;
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

	virtual void OnKeyDownEvent(const SDL_KeyboardEvent& event) {}
	virtual void OnKeyUpEvent(const SDL_KeyboardEvent& event) {}
	
protected:
	AppParams m_InitParams;

private:
	Application(const Application&);
	Application& operator=(const Application&);

	std::ofstream m_Log;

	SDL_Window* m_Window;

	SDL_GLContext m_OglContext;

	std::unique_ptr<RenderSystem> m_RenderSystem;

	unsigned long long m_PerfFrequency;
	unsigned long long m_LastFrameCounter;

	bool m_Quit;
};

}