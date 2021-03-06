#include "stdafx.h"
#include <Application.h>
#include <RenderSystem.h>
#include <OGLPtrsDecls.h>

namespace oglwork
{

void LogOutputFunction(void* userdata,
	int category,
	SDL_LogPriority priority,
	const char* message)
{
	((Application*)userdata)->Log(category, priority, message);
}

void __stdcall gl_error(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	GLvoid* userParam)
{
	SDL_LogPriority priority;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW:
		priority = SDL_LOG_PRIORITY_DEBUG;
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		priority = SDL_LOG_PRIORITY_INFO;
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		priority = SDL_LOG_PRIORITY_ERROR;
		break;
	}
	LogOutputFunction(userParam,
		SDL_LOG_CATEGORY_RENDER,
		priority,
		message);
}

Application::Application()
	: m_Window(nullptr)
	, m_OglContext(nullptr)
	, m_Quit(false)
	, m_PerfFrequency(0LL)
	, m_LastFrameCounter(0LL)
{}

bool Application::Initialize(const AppParams& params)
{
	m_InitParams = params;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return false;
	}

	SDL_LogSetOutputFunction(&LogOutputFunction, this);

	SDL_LogSetAllPriority(params.LogPriority);

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialization successful");

	unsigned flags = SDL_WINDOW_OPENGL;
	if (params.Fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (params.sRGB) {
		SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (params.MultisampleCount) {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, params.MultisampleCount);
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
	
	if (params.EnableDebugOutput)
	{
		glDebugMessageCallbackARB(gl_error, this);
		glEnable(GL_DEBUG_OUTPUT);
	}

	m_RenderSystem.reset(new RenderSystem(m_Window));

	SDL_GL_SetSwapInterval(params.VSync ? 1 : 0);

	m_PerfFrequency = SDL_GetPerformanceFrequency();

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

void Application::Run()
{
	m_LastFrameCounter = SDL_GetPerformanceCounter();
	while (!m_Quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				m_Quit = true;
				break;
			case SDL_KEYDOWN:
				OnKeyDownEvent(event.key);
				break;
			case SDL_KEYUP:
				OnKeyUpEvent(event.key);
				break;
			}
		}

		auto now = SDL_GetPerformanceCounter();

		auto dt = double(now - m_LastFrameCounter) / m_PerfFrequency;

		Update(dt);
		m_RenderSystem->Draw(dt);

		m_LastFrameCounter = now;
	}
}

RenderSystem* Application::GetRenderSystem() const
{
	return m_RenderSystem.get();
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

GLenum CheckGLError()
{
	auto error = glGetError();
	if (error != GL_NO_ERROR) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, (const char*)gluErrorString(error));
	}
	return error;
}

void APP_EXPORTED_SYMBOL ClearGLErrors()
{
	while (CheckGLError() != GL_NO_ERROR);
}