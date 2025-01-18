#pragma once
#include "Evadne/Core/Core.h"

#ifdef EV_PLATFORM_WINDOWS


extern Evadne::Application* Evadne::CreateApplication();
int main(int argc, char** argv) 
{
    Evadne::Log::Init();

    EV_PROFILE_BEGIN_SESSION("Startup", "EvadneProfile-Startup.json");
    auto app = Evadne::CreateApplication();
    EV_PROFILE_END_SESSION();

    EV_PROFILE_BEGIN_SESSION("Runtime", "EvadneProfile-Runtime.json");
    app->Run();
    EV_PROFILE_END_SESSION();

    EV_PROFILE_BEGIN_SESSION("Shutdown", "EvadneProfile-Shutdown.json");
    delete app;
    EV_PROFILE_END_SESSION();
}

#endif