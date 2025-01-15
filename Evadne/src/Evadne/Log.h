#pragma once


#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Evadne {
    class EVADNE_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

//core log macros
#define EV_CORE_ERROR(...) ::Evadne::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EV_CORE_WARN(...)  ::Evadne::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EV_CORE_INFO(...)  ::Evadne::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EV_CORE_TRACE(...) ::Evadne::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EV_CORE_FATAL(...) ::Evadne::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//core log macros
#define EV_ERROR(...) ::Evadne::Log::GetClientLogger()->error(__VA_ARGS__)
#define EV_WARN(...)  ::Evadne::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EV_INFO(...)  ::Evadne::Log::GetClientLogger()->info(__VA_ARGS__)
#define EV_TRACE(...) ::Evadne::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EV__FATAL(...) ::Evadne::Log::GetClientLogger()->fatal(__VA_ARGS__)