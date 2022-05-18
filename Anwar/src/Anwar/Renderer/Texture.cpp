#include "anwpch.h"
#include "Anwar/Renderer/Texture.h"

#include "Anwar/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Anwar
{
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: ANW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
        }

        ANW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: ANW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
        }

        ANW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}