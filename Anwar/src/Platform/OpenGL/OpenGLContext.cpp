#include "anwpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Anwar
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
    {
        ANW_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        ANW_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        ANW_CORE_ASSERT(status, "Failed to initialize Glad!");

        ANW_CORE_INFO("OpenGL Info");
        ANW_CORE_INFO("  Vendor  : {0}", glGetString(GL_VENDOR));
        ANW_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        ANW_CORE_INFO("  Version : {0}", glGetString(GL_VERSION));

        ANW_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Anwar requires at least OpenGL version 4.5!");
    }

    void OpenGLContext::SwapBuffers()
    {
        ANW_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }
}