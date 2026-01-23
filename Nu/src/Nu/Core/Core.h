#pragma once

#include <memory>

#ifdef NU_PLATFORM_WINDOWS
	#if NU_DYNAMIC_LINK
		#ifdef NU_BUILD_DLL
			#define NU_API __declspec(dllexport) //__NU_API__ maybe?
		#else
			#define NU_API __declspec(dllimport)
		#endif // NU_BUILD_DLL
	#else
		#define NU_API
	#endif
#else
	#error Nu only supports Windows!
#endif // NU_PLATFORM_WINDOWS

#ifdef NU_DEBUG
	#define NU_ENABLE_ASSERTS
#endif

#ifdef NU_ENABLE_ASSERTS
	#define NU_ASSERT(x, ...) { if(!(x)) { NU_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NU_CORE_ASSERT(x, ...) { if(!(x)) { NU_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NU_ASSERT(x, ...)
	#define NU_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x) // 1 shifted by x places

#define NU_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Nu {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}