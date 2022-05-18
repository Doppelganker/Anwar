#include "anwpch.h"
#include "Anwar/Renderer/Framebuffer.h"

#include "Anwar/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Anwar
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: ANW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
        }

        ANW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}