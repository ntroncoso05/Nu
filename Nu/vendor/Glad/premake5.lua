project "Glad"
	kind "StaticLib"
	language "C"
	--staticruntime "off"
	--warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		--[[files
		{
			"src/win32_init.c",
			"src/win32_joystick.c",
			"src/win32_module.c",
			"src/win32_monitor.c",
			"src/win32_time.c",
			"src/win32_thread.c",
			"src/win32_window.c",
			"src/wgl_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		} ]]
		
	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

	--[[filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter { "system:windows", "configurations:Debug-AS" }	
		runtime "Debug"
		symbols "on"
		sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
        symbols "off"

	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files
		{
			"src/x11_init.c",
			"src/x11_monitor.c",
			"src/x11_window.c",
			"src/xkb_unicode.c",
			"src/posix_module.c",
			"src/posix_time.c",
			"src/posix_thread.c",
			"src/posix_module.c",
			"src/glx_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c",
			"src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:macosx"
		pic "On"

		files
		{
			"src/cocoa_init.m",
			"src/cocoa_monitor.m",
			"src/cocoa_window.m",
			"src/cocoa_joystick.m",
			"src/cocoa_time.c",
			"src/nsgl_context.m",
			"src/posix_thread.c",
			"src/posix_module.c",
			"src/osmesa_context.c",
			"src/egl_context.c"
		}

		defines
		{
			"_GLFW_COCOA"
		}
	
	]]