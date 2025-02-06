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

    struct ApplicationCommandLineArgs 
    {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int index) const 
        {
            EV_CORE_ASSERT(index < Count);
            return Args[index];
        }
    };

    class Application
    {
    public:
        Application(const std::string& name = "Evadne App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
        virtual ~Application();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }

        void Close();

        ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

        inline static Application& Get() { return *s_Instance; }

        ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        void Run();
        ApplicationCommandLineArgs m_CommandLineArgs;
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

    Application* CreateApplication(ApplicationCommandLineArgs args);

}

