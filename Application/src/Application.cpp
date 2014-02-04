#include "stdafx.h"
#include "../include/Application.h"

namespace oglwork
{

void LogOutputFunction(void* userdata,
	int category,
	SDL_LogPriority priority,
	const char* message)
{
	((Application*)userdata)->Log(category, priority, message);
}

Application::Application()
	: m_Window(nullptr)
	, m_OglContext(nullptr)
{}

bool Application::Initialize(const AppParams& params)
{
	m_InitParams = params;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return false;
	}

	SDL_LogSetOutputFunction(&LogOutputFunction, this);

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialization successful");

	unsigned flags = SDL_WINDOW_OPENGL;
	if (params.Fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	m_Window = SDL_CreateWindow(
		params.Name,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		params.Width,
		params.Height,
		flags
		);

	if (!m_Window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window");
		return false;
	}

	m_OglContext = SDL_GL_CreateContext(m_Window);
	if (!m_OglContext) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create OpenGL context");
		return false;
	}

	if (glewInit() != GLEW_OK) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize GLEW");
		return false;
	}

	return true;
}

Application::~Application()
{
	if (m_OglContext) {
		SDL_GL_DeleteContext(m_OglContext);
	}

	if (m_Window) {
		SDL_DestroyWindow(m_Window);
	}

	if (SDL_WasInit(0)) {
		SDL_Quit();
	}
}

void Application::Log(int category, SDL_LogPriority priority, const char* message)
{
	static const char* Categories[] = {
		"Application",
		"Error",
		"System",
		"Audio",
		"Video",
		"Render",
		"Input"
	};

	static const char* Priorities[] = {
		"Verbose",
		"Debug",
		"Info",
		"Warning",
		"Error",
		"Critical"
	};

	if (!m_Log.is_open()) {
		std::string filename(m_InitParams.Name);
		filename.append("Log.log");
		m_Log.open(filename.c_str());
		m_Log.imbue(std::locale(""));
	}

	if (!m_Log.is_open())
		return;

	using std::chrono::system_clock;
	auto now = system_clock::now();
	std::time_t tt = system_clock::to_time_t(now);

	std::tm ptm;
	localtime_s(&ptm, &tt);
	m_Log << std::put_time(&ptm, "%c") << " "
		<< Categories[category - SDL_LOG_CATEGORY_APPLICATION] << " "
		<< Priorities[priority - SDL_LOG_PRIORITY_VERBOSE] << " "
		<< "| " << message
		<< std::endl;
}

}
