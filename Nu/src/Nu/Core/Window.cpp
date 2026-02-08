#include "nupch.h"
#include "Nu/Core/Window.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Nu
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef NU_PLATFORM_WINDOWS
				return CreateScope<WindowsWindow>(props);
		#else
				NU_CORE_ASSERT(false, "Unknown platform!");
				return nullptr;
		#endif
	}

}