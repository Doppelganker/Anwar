#pragma once

#include <sstream>

#include "Anwar/Core/Base.h"
#include "Anwar/Events/Event.h"

namespace Anwar
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "Anwar Engine", uint32_t width = 1600, uint32_t height = 900) : Title(title), Width(width), Height(height)
        {}
    };

    // Interface representing a desktop system based Window
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        // Window attribute
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVsync(bool enabled) = 0;
        virtual bool IsVsync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
}