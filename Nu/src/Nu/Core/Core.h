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

#define NU_EXPAND_MACRO(x) x
#define NU_STRINGIFY_MACRO(x) #x

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

#include "Nu/Core/Log.h"
#include "Nu/Core/Assert.h"
