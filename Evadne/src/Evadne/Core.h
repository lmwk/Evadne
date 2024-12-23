#pragma once

#ifdef EV_PLATFORM_WINDOWS
    #ifdef EV_BUILD_DLL
        #define EVADNE_API __declspec(dllexport)
    #else
    #define EVADNE_API __declspec(dllimport)
    #endif 
#else
    #error Windows only supported at this time
#endif