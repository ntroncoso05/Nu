workspace "Nu"
	architecture "x64"
	startproject "Sandbox" --Not Working

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
IncludeDir["Glad"] = "Nu/vendor/Glad/include"
IncludeDir["ImGui"] = "Nu/vendor/imgui"
IncludeDir["glm"] = "Nu/vendor/glm"

include "Nu/vendor/GLFW"
include "Nu/vendor/Glad"
include "Nu/vendor/ImGui"

project "Nu"
	location "Nu"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nupch.h"
	pchsource "Nu/src/nupch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NU_PLATFORM_WINDOWS",
			"NU_BUILD_DLL",
			"GLFW_INCLUDE_NONE" -- will not include any OPENGL header with GLFW
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
		
	filter "configurations:Debug"
		defines "NU_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		runtime "Release"
		optimize "On"

	filter "configurations:Debug"
		buildoptions "/utf-8"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Nu/src",
		"Nu/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Nu"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NU_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NU_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		runtime "Release"
		optimize "On"

	filter "configurations:Debug"
		buildoptions "/utf-8"