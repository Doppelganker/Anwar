#include "anwpch.h"
#include "Anwar/Renderer/VertexArray.h"

#include "Anwar/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Anwar
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: ANW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
        }

        ANW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}