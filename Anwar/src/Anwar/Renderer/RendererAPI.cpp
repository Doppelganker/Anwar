#include "anwpch.h"
#include "Anwar/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Anwar
{
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case Anwar::RendererAPI::API::None:
                ANW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case Anwar::RendererAPI::API::OpenGL:
                return CreateScope<OpenGLRendererAPI>();
        }

        ANW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}