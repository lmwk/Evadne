#pragma once

#include "Evadne/Input/Input.h"

namespace Evadne {

    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int button) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };

}

