#include "evpch.h"
#include "Evadne/Core/Application.h"

#include "Evadne/Core/Log.h"

#include "Evadne/Rendering/Renderer.h"

#include "Evadne/Input/Input.h"

#include <GLFW/glfw3.h>

namespace Evadne {

    Application* Application::s_Instance = nullptr;

    Application::Application() 
    {
        EV_PROFILE_FUNCTION();

        EV_CORE_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(EV_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

    }

    Application::~Application() 
    {
        EV_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::OnEvent(Event& e) 
    {
        EV_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(EV_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(EV_BIND_EVENT_FN(Application::OnWindowResize));

        for(auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) 
        {
            (*it)->OnEvent(e);
            if (e.m_Handled)
                break;
        }
    }

    void Application::Run() 
    {
        EV_PROFILE_FUNCTION();

        while (m_Running) 
        {
            EV_PROFILE_SCOPE("RunLoop");

            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized)
            {
                {
                    EV_PROFILE_SCOPE("LayerStack OnUpdate");

                    for (Layer* layer : m_LayerStack)
                        layer->OnUpdate(timestep);
                }

                m_ImGuiLayer->Begin();

                {
                    EV_PROFILE_SCOPE("LayerStack OnImGuiRender");

                    for (Layer* layer : m_LayerStack)
                        layer->OnImGuiRender();
                }

                m_ImGuiLayer->End();
            }

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        EV_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        EV_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        EV_PROFILE_FUNCTION();

        if(e.GetWidth() == 0 || e.GetHeight() == 0) 
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

}