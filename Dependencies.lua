VULKAN_SDK = os.getenv("VULKAN_SDK")
IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/Evadne/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Evadne/vendor/yaml-cpp/include"
IncludeDir["GLFW"] = "%{wks.location}/Evadne/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Evadne/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Evadne/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Evadne/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/Evadne/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/Evadne/vendor/entt/include"
IncludeDir["shaderc"] = "%{wks.location}/Evadne/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/Evadne/vendor/SPIRV-Cross"
IncludeDir["Bullet3"] = "%{wks.location}/Evadne/vendor/Bullet3/src"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/Evadne/vendor/VulkanSDK/Lib"
LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/Evadne/vendor/VulkanSDK/Bin"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
