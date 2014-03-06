#pragma once

APP_EXPORTED_SYMBOL GLenum CheckGLError();
APP_EXPORTED_SYMBOL void ClearGLErrors();

#ifdef _DEBUG
#define CHECK_GL_ERROR CheckGLError()
#define CLEAR_GL_ERRORS ClearGLErrors()
#else
#define CHECK_GL_ERROR
#define CLEAR_GL_ERRORS
#endif