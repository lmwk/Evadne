#include "evpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Evadne/Platforms/OpenGL/OpenGLBuffer.h"

namespace Evadne {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) 
    {
        switch(Renderer::GetAPI()) 
        {
        case RendererAPI::API::None:
            EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }

        EV_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) 
    {
        switch (Renderer::GetAPI()) 
        {
        case RendererAPI::API::None:
            EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
        }

        EV_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

}