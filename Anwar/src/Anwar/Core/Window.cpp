#include "anwpch.h"
#include "Anwar/Core/Window.h"

#ifdef ANW_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif // ANW_PLATFORM_WINDOWS

namespace Anwar
{
    Scope<Window> Window::Create(const WindowProps& props)
    {
        #ifdef ANW_PLATFORM_WINDOWS
        return CreateScope<WindowsWindow>(props);
        #else
        ANW_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
        #endif // ANW_PLATFORM_WINDOWS
    }
}

