#include "evpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Evadne/Platforms/OpenGL/OpenGLTexture.h"

namespace Evadne {



    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}
		EV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

}