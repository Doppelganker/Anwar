#include "anwpch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Anwar/Core/Input.h"

#include "Anwar/Events/ApplicationEvent.h"
#include "Anwar/Events/MouseEvent.h"
#include "Anwar/Events/KeyEvent.h"

#include "Anwar/Renderer/Renderer.h"

namespace Anwar
{
    static uint16_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        ANW_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        ANW_PROFILE_FUNCTION();

        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        ANW_PROFILE_FUNCTION();

        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        ANW_PROFILE_FUNCTION();

        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        ANW_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0)
        {
            ANW_PROFILE_SCOPE("glfwInit");
            
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            ANW_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            ANW_PROFILE_SCOPE("glfwCreateWindow");
            #if defined(ANW_DEBUG)
            if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
            {
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
            }
            #endif
            m_Window = glfwCreateWindow((int) props.Width, (int) props.Height, m_Data.Title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowCount;
        }
        m_Context = GraphicsContext::Create(m_Window);
        m_Context->Init();


        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVsync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
                                  {
                                      WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                                      data.Width = width;
                                      data.Height = height;

                                      WindowResizeEvent event(width, height);
                                      data.EventCallback(event);
                                  });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
                                   {
                                       WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                                       WindowCloseEvent event;
                                       data.EventCallback(event);
                                   });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
                           {
                               WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                               switch (action)
                               {
                                   case GLFW_PRESS:
                                   {
                                       KeyPressedEvent event(key, 0);
                                       data.EventCallback(event);
                                       break;
                                   }
                                   case GLFW_RELEASE:
                                   {
                                       KeyReleasedEvent event(key);
                                       data.EventCallback(event);
                                       break;
                                   }
                                   case GLFW_REPEAT:
                                   {
                                       KeyPressedEvent event(key, 1);
                                       data.EventCallback(event);
                                       break;
                                   }
                               }
                           });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
                           {
                                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                                KeyTypedEvent event(keycode);
                                data.EventCallback(event);
                           });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
                                   {
                                       WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                                       switch (action)
                                       {
                                           case GLFW_PRESS:
                                           {
                                               MouseButtonPressedEvent event(button);
                                               data.EventCallback(event);
                                               break;
                                           }
                                           case GLFW_RELEASE:
                                           {
                                               MouseButtonReleasedEvent event(button);
                                               data.EventCallback(event);
                                               break;
                                           }
                                       }
                                   });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
                              {
                                  WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                                  MouseScrolledEvent event((float) xoffset, (float) yoffset);
                                  data.EventCallback(event);
                              });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
                                 {
                                     WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                                     MouseMovedEvent event((float) xpos, (float) ypos);
                                     data.EventCallback(event);
                                 });
    }

    void WindowsWindow::Shutdown()
    {
        ANW_PROFILE_FUNCTION();

        glfwDestroyWindow(m_Window);
        --s_GLFWWindowCount;

        if (s_GLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void WindowsWindow::OnUpdate()
    {
        ANW_PROFILE_FUNCTION();

        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetVsync(bool enabled)
    {
        ANW_PROFILE_FUNCTION();

        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVsync() const
    {
        return m_Data.VSync;
    }
}