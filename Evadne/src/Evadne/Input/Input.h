#pragma once

#include "Evadne/Core/Core.h"
#include "Evadne/Input/KeyCodes.h"
#include "Evadne/Input/MouseCodes.h"

#include <utility>

namespace Evadne {

    class Input 
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };

}