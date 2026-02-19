include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Nu"
	architecture "x86_64"
	startproject "Nu-Editor" --Not Working

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Nu/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Nu/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Nu/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Nu/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Nu/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Nu/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Nu/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Nu/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "Nu/vendor/GLFW"
	include "Nu/vendor/Glad"
	include "Nu/vendor/ImGui"
	include "Nu/vendor/yaml-cpp"
group ""

include "Nu"
include "Sandbox"
include "Nu-Editor"
