#pragma once

#include "Evadne/Core/Core.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

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

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
    return os << glm::to_string(vector);
}
template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
    return os << glm::to_string(matrix);
}
template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
    return os << glm::to_string(quaternion);
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