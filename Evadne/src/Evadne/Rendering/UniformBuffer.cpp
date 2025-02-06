#include "evpch.h"
#include "UniformBuffer.h"

#include "Evadne/Rendering/Renderer.h"
#include "Evadne/Platforms/OpenGL/OpenGLUniformBuffer.h"

namespace Evadne {

    Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
    {
        switch(Renderer::GetAPI()) 
        {
        case RendererAPI::API::None:
            EV_CORE_ASSERT(false, "RendererAPI:: None is currently not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLUniformBuffer>(size, binding);
        }
    }

}
