#include "anwpch.h"
#include "Anwar/Renderer/RenderCommand.h"

namespace Anwar
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}