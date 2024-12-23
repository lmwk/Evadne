#pragma once

#include "Core.h"

namespace Evadne {
    class EVADNE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();

}

