#pragma once


#include "Evadne/Core/Core.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Evadne {
    class Log
    {
    public:
        static void Init();

        inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}


#define EV_CORE_ERROR(...) ::Evadne::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EV_CORE_WARN(...)  ::Evadne::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EV_CORE_INFO(...)  ::Evadne::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EV_CORE_TRACE(...) ::Evadne::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EV_CORE_CRITICAL(...) ::Evadne::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define EV_ERROR(...) ::Evadne::Log::GetClientLogger()->error(__VA_ARGS__)
#define EV_WARN(...)  ::Evadne::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EV_INFO(...)  ::Evadne::Log::GetClientLogger()->info(__VA_ARGS__)
#define EV_TRACE(...) ::Evadne::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EV_CRITICAL(...) ::Evadne::Log::GetClientLogger()->critical(__VA_ARGS__)