#pragma once

#include "Evadne.h"

namespace Evadne {

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Evadne::Timestep ts) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Evadne::Event& e) override;
    private:
        Evadne::OrthographicCameraController m_CameraController;

        Evadne::Ref<Evadne::VertexArray> m_SquareVA;
        Evadne::Ref<Evadne::Shader> m_FlatColorShader;
        Evadne::Ref<Evadne::Framebuffer> m_Framebuffer;

        Evadne::Ref<Evadne::Texture2D> m_BackgroundTexture;

        bool m_ViewportFocused = false, m_ViewportHovered = false;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

        glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    };
}



