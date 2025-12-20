#pragma once

#ifdef NU_PLATFORM_WINDOWS
	#ifdef NU_BUILD_DLL
		#define NU_API __declspec(dllexport)
	#else
		#define NU_API __declspec(dllimport)
	#endif // NU_BUILD_DLL
#else
	#error Nu only supports Windows!
#endif // NU_PLATFORM_WINDOWS