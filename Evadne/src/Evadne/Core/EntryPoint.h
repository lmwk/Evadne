#pragma once
#include "Evadne/Core/Core.h"

#ifdef EV_PLATFORM_WINDOWS


extern Evadne::Application* Evadne::CreateApplication();
int main(int argc, char** argv) 
{
    Evadne::Log::Init();
    EV_CORE_WARN("Initialized Logging");
    int a = 5;
    EV_INFO("I see you {0}", a);

    auto app = Evadne::CreateApplication();
    app->Run();
    delete app;
}

#endif