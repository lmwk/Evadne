#pragma once

#include <memory>

#ifdef EV_PLATFORM_WINDOWS
#if EV_DYNAMIC_LINK
    #ifdef EV_BUILD_DLL
        #define EVADNE_API __declspec(dllexport)
    #else
    #define EVADNE_API __declspec(dllimport)
    #endif 
#else 
    #define EVADNE_API
#endif
#else
    #error Windows only supported at this time
#endif

#ifdef EV_DEBUG
#define EV_ENABLE_ASSERTS
#endif

#ifdef EV_ENABLE_ASSERTS
    #define EV_ASSERT(x, ...) {if(!(x)) {EV_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
    #define EV_CORE_ASSERT(x, ...) {if(!(x)) {EV_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else 
    #define EV_ASSERT(x, ...)
    #define EV_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define EV_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Evadne {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

}