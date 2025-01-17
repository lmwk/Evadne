#include "evpch.h"
#include "Shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "Evadne/Platforms/OpenGL/OpenGLShader.h"

namespace Evadne {

    

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch(Renderer::GetAPI()) 
        {
        case RendererAPI::API::None:
            EV_CORE_ASSERT(false, "RendererAPI::None is currently");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        EV_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }



}