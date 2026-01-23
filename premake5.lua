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
IncludeDir["stb_image"] = "Nu/vendor/stb_image"

group "Dependencies"
	include "Nu/vendor/GLFW"
	include "Nu/vendor/Glad"
	include "Nu/vendor/ImGui"

group ""

project "Nu"
	location "Nu"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nupch.h"
	pchsource "Nu/src/nupch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NU_PLATFORM_WINDOWS",
			"NU_BUILD_DLL",
			"GLFW_INCLUDE_NONE" -- will not include any OPENGL header with GLFW
		}
		
	filter "configurations:Debug"
		defines "NU_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		runtime "Release"
		optimize "on"

	filter "configurations:Debug"
		buildoptions "/utf-8"

	filter "configurations:Release"
		buildoptions "/utf-8"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		systemversion "latest"

		defines
		{
			"NU_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NU_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		runtime "Release"
		optimize "on"

	filter "configurations:Debug"
		buildoptions "/utf-8"

	filter "configurations:Release"
		buildoptions "/utf-8"