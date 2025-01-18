#pragma once

#include "Evadne/Core/Layer.h"

#include "Evadne/Events/ApplicationEvent.h"
#include <Evadne/Events/MouseEvent.h>
#include <Evadne/Events/KeyEvent.h>

namespace Evadne {

    class ImGuiLayer : public Layer
    {
    public:

        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& e) override;

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }
    private:
        bool m_BlockEvents = true;

    };

}

