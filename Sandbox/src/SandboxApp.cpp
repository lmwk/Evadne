#include <Evadne.h>
#include <Evadne/Core/EntryPoint.h>

#include "Evadne/Platforms/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"

#include "Layers/ExampleLayer.h"


class Sandbox : public Evadne::Application 
{
public: 
    Sandbox()
    {
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() 
    {
        
    }
};

Evadne::Application* Evadne::CreateApplication() 
{
    return new Sandbox();
}