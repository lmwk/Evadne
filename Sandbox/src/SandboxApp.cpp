#include <Evadne.h>

class Sandbox : public Evadne::Application 
{
public: 
    Sandbox()
    {

    }

    ~Sandbox() 
    {

    }
};

Evadne::Application* Evadne::CreateApplication() 
{
    return new Sandbox();
}