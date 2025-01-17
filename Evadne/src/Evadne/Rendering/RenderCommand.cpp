#include "evpch.h"
#include "RenderCommand.h"

#include "Evadne/Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Evadne {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}