#pragma once

#ifdef EV_PLATFORM_WINDOWS

extern Evadne::Application* Evadne::CreateApplication();
int main(int argc, char** argv) 
{
    printf("Evadne Engine\n");
    auto app = Evadne::CreateApplication();
    app->Run();
    delete app;
}

#endif