#include <Anwar.h>
#include <Anwar/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Anwar::Application
{
public:
    Sandbox(Anwar::ApplicationCommandLineArgs args)
    {
        PushLayer(new Sandbox2D());
    }
    ~Sandbox()
    {}
};

Anwar::Application* Anwar::CreateApplication(Anwar::ApplicationCommandLineArgs args)
{
    return new Sandbox(args);
}
