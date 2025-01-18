#pragma once

#include <memory>

#ifdef _WIN32
    #ifdef _WIN64
        #define EV_PLATFORM_WINDOWS
    #else

        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>

    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define EV_PLATFORM_IOS
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #define EV_PLATFORM_MACOS
        #error "MacOS is not supported!"
    #else
        #error "Unknown Apple platform!"
#endif

#elif defined(__ANDROID__)
    #define EV_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__linux__)
#define EV_PLATFORM_LINUX
    #error "Linux is not supported!"
#else

    #error "Unknown platform!"
#endif 

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

#ifdef EV_ENABLE_ASSERTS
    #define EV_ASSERT(x, ...) {if(!(x)) {EV_ERROR("Assertion Failed: {0}", __VA_ARGS__); EV_DEBUGBREAK();}}
    #define EV_CORE_ASSERT(x, ...) {if(!(x)) {EV_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); EV_DEBUGBREAK();}}
#else 
    #define EV_ASSERT(x, ...)
    #define EV_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define EV_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

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