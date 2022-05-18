#pragma once

#include "Anwar/Core/Window.h"
#include "Anwar/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Anwar
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override
        {
            return m_Data.Width;
        }
        unsigned int GetHeight() const override
        {
            return m_Data.Height;
        }

        // Window attributes
        void SetEventCallback(const EventCallbackFn& callback) override
        {
            m_Data.EventCallback = callback;
        }
        void SetVsync(bool enabled) override;
        bool IsVsync() const override;

        virtual void* GetNativeWindow() const
        {
            return m_Window;
        }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;
        Scope<GraphicsContext> m_Context;
        
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}

