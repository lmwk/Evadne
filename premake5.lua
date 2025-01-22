include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Evadne" 
	architecture "x86_64"
	
	startproject "Evadne-Editor"
	
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

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Evadne/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Evadne/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Evadne/vendor/imgui/"
IncludeDir["glm"] = "%{wks.location}/Evadne/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Evadne/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Evadne/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Evadne/vendor/yaml-cpp/include"


group "Dependencies"

	include "Evadne/vendor/GLFW"
	include "Evadne/vendor/Glad"
	include "Evadne/vendor/imgui"
	include "vendor/premake"
	include "Evadne/vendor/yaml-cpp"

group ""

include "Evadne"
include "Sandbox"
include "Evadne-Editor"
