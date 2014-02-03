#pragma once

namespace oglwork
{

struct APP_EXPORTED_SYMBOL AppParams
{
	const char* Name;
};

class APP_EXPORTED_SYMBOL Application
{
public:
	Application();

	virtual bool Initialize(const AppParams& params);

	virtual void Log(int category, SDL_LogPriority priority, const char* message);

	virtual ~Application();

private:
	AppParams m_InitParams;
	std::ofstream m_Log;
};

}