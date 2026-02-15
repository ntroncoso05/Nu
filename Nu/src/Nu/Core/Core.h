#pragma once

#include <memory>

#include "Nu/Core/PlatformDetection.h"

#ifdef NU_DEBUG
	#if defined(NU_PLATFORM_WINDOWS)
		#define NU_DEBUGBREAK() __debugbreak()
	#elif defined(NU_PLATFORM_LINUX)
		#include <signal.h>
		#define NU_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define NU_ENABLE_ASSERTS
#else
	#define NU_DEBUGBREAK()
#endif

// TODO: Make this macro able to take in no arguments except condition
#ifdef NU_ENABLE_ASSERTS
	#define NU_ASSERT(x, ...) { if(!(x)) { NU_ERROR("Assertion Failed: {0}", __VA_ARGS__); NU_DEBUGBREAK(); } }	
	#define NU_CORE_ASSERT(x, ...) { if(!(x)) { NU_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); NU_DEBUGBREAK(); } }
#else
	#define NU_ASSERT(x, ...)
	#define NU_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x) // 1 shifted by x places

#define NU_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Nu {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}