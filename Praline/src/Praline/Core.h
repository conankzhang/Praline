#pragma once

#ifdef PRALINE_PLATFORM_WINDOWS
	#ifdef PRALINE_BUILD_DLL
		#define PRALINE_API __declspec(dllexport)
	#else
		#define PRALINE_API __declspec(dllimport)
	#endif
#else
	#error Praline only supports Windows!
#endif
