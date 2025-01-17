#include "evpch.h"
#include "Evadne/Rendering/VertexArray.h"

#include "Evadne/Rendering/Renderer.h"
#include "Evadne/Platforms/OpenGL/OpenGLVertexArray.h"

namespace Evadne {

    Ref<VertexArray> VertexArray::Create() 
    {
        switch (Renderer::GetAPI()) 
        {
        case RendererAPI::API::None:
            EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        }

        EV_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}