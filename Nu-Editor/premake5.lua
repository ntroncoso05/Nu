project "Nu-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Nu/vendor/spdlog/include",
		"%{wks.location}/Nu/src",
		"%{wks.location}/Nu/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
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
		buildoptions "/utf-8"
