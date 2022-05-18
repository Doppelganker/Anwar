#include "anwpch.h"
#include "Anwar/Renderer/GraphicsContext.h"

#include "Anwar/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"


namespace Anwar
{
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: ANW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        ANW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}