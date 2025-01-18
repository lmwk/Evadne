#include "evpch.h"
#include "Evadne/Rendering/Buffer.h"

#include "Evadne/Rendering/Renderer.h"

#include "Evadne/Platforms/OpenGL/OpenGLBuffer.h"

namespace Evadne {
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(size);
        }

        EV_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch(Renderer::GetAPI()) 
        {
        case RendererAPI::API::None:
            EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        EV_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) 
    {
        switch (Renderer::GetAPI()) 
        {
        case RendererAPI::API::None:
            EV_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(indices, count);
        }

        EV_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

}