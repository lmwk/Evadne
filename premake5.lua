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
IncludeDir["GLFW"] = "Evadne/vendor/GLFW/include"
IncludeDir["Glad"] = "Evadne/vendor/Glad/include"
IncludeDir["ImGui"] = "Evadne/vendor/imgui/"
IncludeDir["glm"] = "Evadne/vendor/glm"
IncludeDir["stb_image"] = "Evadne/vendor/stb_image"
IncludeDir["entt"] = "Evadne/vendor/entt/include"


group "Dependencies"

	include "Evadne/vendor/GLFW"
	include "Evadne/vendor/Glad"
	include "Evadne/vendor/imgui"

group ""

project "Evadne"
	location "Evadne"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "evpch.h"
	pchsource "Evadne/src/evpch.cpp"
	
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
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
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
		buildoptions {"/utf-8"}

	filter "configurations:Debug"
		defines "EV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EV_DIST"
		runtime "Release"
		optimize "on"

project "Evadne-Editor"
	location "Evadne-Editor"
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
		"Evadne/vendor/spdlog/include",
		"Evadne/src",
		"Evadne/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}
	links
	{
		"Evadne"
	}
	filter "system:windows"
		systemversion "latest"
		buildoptions {"/utf-8"}
		
	filter "configurations:Debug"
		defines "EV_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "EV_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "EV_DIST"
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
		"Evadne/vendor/spdlog/include",
		"Evadne/src",
		"Evadne/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Evadne"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions {"/utf-8"}

	filter "configurations:Debug"
		defines "EV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EV_DIST"
		runtime "Release"
		optimize "on"