#include "evpch.h"
#include "Window.h"

#ifdef EV_PLATFORM_WINDOWS
#include "Evadne/Platforms/Windows/WindowsWindow.h"
#endif

namespace Evadne {

    Scope<Window> Evadne::Window::Create(const WindowProps& props)
    {
    #ifdef EV_PLATFORM_WINDOWS
            return CreateScope<WindowsWindow>(props);
    #else
            EV_CORE_ASSERT(false, "Unknown platform"!);
    #endif
    }
}
