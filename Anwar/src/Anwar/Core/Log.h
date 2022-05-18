#pragma once

#include "Anwar/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warning raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Anwar
{
    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger>& GetCoreLogger()
        {
            return s_CoreLogger;
        }
        static Ref<spdlog::logger>& GetClientLogger()
        {
            return s_ClientLogger;
        }
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
    return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
    return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream operator<<(OStream& os, const glm::qua<T, Q>& quaternion)
{
    return os << glm::to_string(quaternion);
}

// Core log macros
#define ANW_CORE_CRITICAL(...)  ::Anwar::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define ANW_CORE_ERROR(...)  ::Anwar::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ANW_CORE_WARN(...)   ::Anwar::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ANW_CORE_INFO(...)   ::Anwar::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ANW_CORE_TRACE(...)  ::Anwar::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define ANW_CRITICAL(...)  ::Anwar::Log::GetClientLogger()->critical(__VA_ARGS__)
#define ANW_ERROR(...)  ::Anwar::Log::GetClientLogger()->error(__VA_ARGS__)
#define ANW_WARN(...)   ::Anwar::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ANW_INFO(...)   ::Anwar::Log::GetClientLogger()->info(__VA_ARGS__)
#define ANW_TRACE(...)  ::Anwar::Log::GetClientLogger()->trace(__VA_ARGS__)