#pragma once

#include <glm/glm.hpp>

#include "Evadne/Input/KeyCodes.h"
#include "Evadne/Input/MouseCodes.h"

#include <utility>

namespace Evadne {

    class Input 
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };

}