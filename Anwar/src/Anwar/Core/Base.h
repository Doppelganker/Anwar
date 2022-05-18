#pragma once

#include <memory>

#include "Anwar/Core/PlatformDetection.h"

#ifdef ANW_DEBUG
#if defined(ANW_PLATFORM_WINDOWS)
#define ANW_DEBUGBREAK() __debugbreak()
#elif defined(ANW_PLATFORM_LINUX)
#include <signal.h>
#define ANW_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define ANW_ENABLE_ASSERTS
#else
#define ANW_DEBUGBREAK()
#endif

#define ANW_EXPAND_MACRO(x) x
#define ANW_STRINGIFY_MACRO(x) #x

#define BIT(x) (1<<x)

#define ANW_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}

namespace Anwar
{
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

#include "Anwar/Core/Log.h"
#include "Anwar/Core/Assert.h"
#include "Anwar/Debug/Instrumentor.h"