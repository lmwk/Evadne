#include "evpch.h"
#include "RenderCommand.h"

#include "Evadne/Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Evadne {

    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}