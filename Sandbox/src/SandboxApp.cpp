#include <Evadne.h>

class ExampleLayer : public Evadne::Layer 
{
public:
    ExampleLayer()
        : Layer("Example") 
    {
    }

    void OnUpdate() override 
    {
        EV_INFO("ExampleLayer:Update");
    }

    void OnEvent(Evadne::Event& event) override 
    {
        EV_TRACE("{0}", event.GetName());
    }
};

class Sandbox : public Evadne::Application 
{
public: 
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Evadne::ImGuiLayer());
    }

    ~Sandbox() 
    {
        
    }
};

Evadne::Application* Evadne::CreateApplication() 
{
    return new Sandbox();
}