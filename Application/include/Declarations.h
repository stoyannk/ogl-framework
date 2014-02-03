#pragma once

#ifdef _MSC_VER
#ifdef APPLICATION_EXPORTS
#define APP_EXPORTED_SYMBOL __declspec(dllexport)
#else
#define APP_EXPORTED_SYMBOL __declspec(dllimport)
#endif
#endif

#define OGL_APP_API APP_EXPORTED_SYMBOL
