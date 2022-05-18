#include <Anwar.h>
#include <Anwar/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Anwar
{

    class AnwarEditor : public Application
    {
    public:
        AnwarEditor(ApplicationCommandLineArgs args) : Application("Anwar Editor")
        {
            PushLayer(new EditorLayer());
        }
        ~AnwarEditor()
        {}
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        return new AnwarEditor(args);
    }
}