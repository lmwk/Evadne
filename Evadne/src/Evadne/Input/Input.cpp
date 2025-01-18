#include "evpch.h"
#include "Input.h"

#ifdef EV_PLATFORM_WINDOWS
    #include "Evadne/Platforms/Windows/WindowsInput.h"
#endif

namespace Evadne {

    Scope<Input> Input::s_Instance = Input::Create();

    Scope<Input> Evadne::Input::Create()
    {
    #ifdef EV_PLATFORM_WINDOWS
            return CreateScope<WindowsInput>();
    #else
            EV_CORE_ASSERT(false, "Unknon platform!");
            return nullptr;
    #endif
    }

}


