workspace "Nu"
	architecture "x86_64"
	startproject "Nu-Editor" --Not Working

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
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
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
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
			"HZ_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "NU_DEBUG"
		runtime "Debug"
		symbols "on"
		buildoptions "/utf-8"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		runtime "Release"
		optimize "on"
		buildoptions "/utf-8"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		runtime "Release"
		optimize "on"
		
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

	filter "configurations:Debug"
		defines "NU_DEBUG"
		runtime "Debug"
		symbols "on"
		buildoptions "/utf-8"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		runtime "Release"
		optimize "on"
		buildoptions "/utf-8"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		runtime "Release"
		optimize "on"

project "Nu-Editor"
	location "Nu-Editor"
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

	filter "configurations:Debug"
		defines "NU_DEBUG"
		runtime "Debug"
		symbols "on"
		buildoptions "/utf-8"
		
	filter "configurations:Release"
		defines "NU_RELEASE"
		runtime "Release"
		optimize "on"
		buildoptions "/utf-8"
		
	filter "configurations:Dist"
		defines "NU_DIST"
		runtime "Release"
		optimize "on"