#pragma once

#include "Evadne/Core/Core.h"

#include "Evadne/Core/Window.h"
#include "Evadne/Core/LayerStack.h"
#include "Evadne/Events/Event.h"
#include "Evadne/Events/ApplicationEvent.h"

#include "Evadne/Core/Timestep.h"
#include "Evadne/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Evadne {
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }


        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        void Run();
        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;

        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication();

}

