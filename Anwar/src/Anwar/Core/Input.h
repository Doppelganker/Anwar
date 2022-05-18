#pragma once

#include <glm/glm.hpp>

#include "Anwar/Core/KeyCodes.h"
#include "Anwar/Core/MouseCodes.h"

namespace Anwar
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode keycode);

        static bool IsMousePressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}