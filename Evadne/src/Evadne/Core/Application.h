#pragma once

#include "Core.h"

#include "Window.h"
#include "Evadne/Core/LayerStack.h"
#include "Evadne/Events/Event.h"
#include "Evadne/Events/ApplicationEvent.h"

#include "Evadne/Core/Timestep.h"
#include "Evadne/ImGui/ImGuiLayer.h"



namespace Evadne {
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }


        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;

        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();

}

