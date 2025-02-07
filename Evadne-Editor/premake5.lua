project "Evadne-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"src/**.h",
		"src/**.cpp"
	}
	includedirs
	{
		"%{wks.location}/Evadne/vendor/spdlog/include",
		"%{wks.location}/Evadne/src",
		"%{wks.location}/Evadne/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
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
		
		postbuildcommands
		{
			"{COPYDIR} \"%{LibraryDir.VulkanSDK_DebugDLL}\" \"%{cfg.targetdir}\""
		}
		
	filter "configurations:Release"
		defines "EV_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "EV_DIST"
		runtime "Release"
		optimize "on"
