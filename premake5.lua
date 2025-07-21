include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

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


group "Dependencies"

	include "Evadne/vendor/GLFW"
	include "Evadne/vendor/Glad"
	include "Evadne/vendor/imgui"
	include "vendor/premake"
	include "Evadne/vendor/yaml-cpp"
	include "Evadne/vendor/Bullet3"

group ""

group "Core"
	include "Evadne"
	include "Evadne-ScriptCore"
group ""

group "Tools"
	include "Evadne-Editor"
group ""

