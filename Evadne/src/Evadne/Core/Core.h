#pragma once

#include <memory>

#include "Evadne/Core/PlatformDetection.h"

#ifdef EV_DEBUG
    #if defined(EV_PLATFORM_WINDOWS)
        #define EV_DEBUGBREAK() __debugbreak()
    #elif defined(EV_PLATFORM_LINUX)
        #include <signal.h>
        #define EV_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define EV_ENABLE_ASSERTS
#else
    #define EV_DEBUGBREAK()
#endif

#define EV_EXPAND_MACRO(x) x
#define EV_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)
#define EV_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Evadne {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}

#include "Evadne/Core/Log.h"
#include "Evadne/Core/Assert.h"