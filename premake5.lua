workspace "Nu"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Nu/vendor/GLFW/include"

include "Nu/vendor/GLFW"

project "Nu"
	location "Nu"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nupch.h"
	pchsource "Nu/src/nupch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NU_PLATFORM_WINDOWS",
			"NU_BUILD_DLL"
		}

		postbuildcommands
		{
			("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "NU_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		optimize "On"

	filter "configurations:Debug"
		buildoptions "/utf-8"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Nu/vendor/spdlog/include",
		"Nu/src"
	}

	links
	{
		"Nu"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NU_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NU_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		optimize "On"

	filter "configurations:Debug"
		buildoptions "/utf-8"