#pragma once

#include "Evadne/Layer.h"

namespace Evadne {

    class EVADNE_API ImGuiLayer : public Layer
    {
    public:

        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);

    private:

        float m_Time = 0.0f;

    };

}

