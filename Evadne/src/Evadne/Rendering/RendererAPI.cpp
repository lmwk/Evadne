#include "evpch.h"
#include "Evadne/Rendering/RendererAPI.h"

#include "Evadne/Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Evadne {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
        case RendererAPI::API::None:    
            EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); 
            return nullptr;
        case RendererAPI::API::OpenGL:  
            return CreateScope<OpenGLRendererAPI>();
        }
        EV_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

}