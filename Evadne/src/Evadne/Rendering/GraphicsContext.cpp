#include "evpch.h"
#include "Evadne/Rendering/GraphicsContext.h"

#include "Evadne/Rendering/Renderer.h"
#include "Evadne/Platforms/OpenGL/OpenGLContext.h"

namespace Evadne {

    Scope<GraphicsContext> Evadne::GraphicsContext::Create(void* window)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    
			EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); 
			return nullptr;
		case RendererAPI::API::OpenGL:  
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		EV_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }

}


