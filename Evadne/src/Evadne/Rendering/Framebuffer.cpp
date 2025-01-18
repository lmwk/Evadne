#include "evpch.h"
#include "Framebuffer.h"

#include "Evadne/Rendering/Renderer.h"

#include "Evadne/Platforms/OpenGL/OpenGLFramebuffer.h"

namespace Evadne {

    Ref<Framebuffer> Evadne::Framebuffer::Create(const FramebufferSpecification& spec)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    
			EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); 
			return nullptr;
		case RendererAPI::API::OpenGL:  
			return CreateRef<OpenGLFramebuffer>(spec);
		}
		EV_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }
}