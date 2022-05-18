#pragma once

#include "Anwar/Core/Base.h"
#include "Anwar/Core/Application.h"

#ifdef ANW_PLATFORM_WINDOWS

extern Anwar::Application* Anwar::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    Anwar::Log::Init();

    ANW_PROFILE_BEGIN_SESSION("Startup", "AnwarProfile-Startup.json");
    auto app = Anwar::CreateApplication({argc, argv});
    ANW_PROFILE_END_SESSION();


    ANW_PROFILE_BEGIN_SESSION("Runtime", "AnwarProfile-Runtime.json");
    app->Run();
    ANW_PROFILE_END_SESSION();


    ANW_PROFILE_BEGIN_SESSION("Shutdown", "AnwarProfile-Shutdown.json");
    delete app;
    ANW_PROFILE_END_SESSION();
}

#endif // ANW_PLATFORM_WINDOWS
