#pragma once

#include "Nu/Core/Core.h"
#include "Nu/Core/Log.h"

#ifdef NU_ENABLE_ASSERTS

namespace Nu::Assert
{
	// Returns the simple file name rather than full path as suggested by LovelySanta
	constexpr const char* CurrentFileName(const char* path) {
		const char* file = path;
		while (*path)
		{
			if (*path == '/' || *path == '\\')
				file = ++path;
			else
				path++;
		}
		return file;
	}
}

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define NU_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { NU##type##ERROR(msg, __VA_ARGS__); NU_DEBUGBREAK(); } }
#define NU_INTERNAL_ASSERT_WITH_MSG(type, check, ...) NU_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define NU_INTERNAL_ASSERT_NO_MSG(type, check) NU_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", NU_STRINGIFY_MACRO(check), ::Nu::Assert::CurrentFileName(__FILE__), __LINE__)

#define NU_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define NU_INTERNAL_ASSERT_GET_MACRO(...) NU_EXPAND_MACRO( NU_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, NU_INTERNAL_ASSERT_WITH_MSG, NU_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define NU_ASSERT(...) NU_EXPAND_MACRO( NU_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define NU_CORE_ASSERT(...) NU_EXPAND_MACRO( NU_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define NU_ASSERT(...)
#define NU_CORE_ASSERT(...)
#endif
