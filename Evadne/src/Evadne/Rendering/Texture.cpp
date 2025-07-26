#include "evpch.h"
#include "Evadne/Rendering/Texture.h"

#include "Evadne/Rendering/Renderer.h"
#include "Evadne/Platforms/OpenGL/OpenGLTexture.h"

namespace Evadne {



	Ref<Texture2D> Texture2D::Create(const TextureSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    
			EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::API::OpenGL:  
			return CreateRef<OpenGLTexture2D>(specification);
		}
		EV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    
			EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::API::OpenGL:  
			return CreateRef<OpenGLTexture2D>(path);
		}
		EV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

}