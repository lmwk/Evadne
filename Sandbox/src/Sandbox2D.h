#pragma once

#include "Evadne.h"

class Sandbox2D : public Evadne::Layer 
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Evadne::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Evadne::Event& e) override;
private:
    Evadne::OrthographicCameraController m_CameraController;

    Evadne::Ref<Evadne::VertexArray> m_SquareVA;
    Evadne::Ref<Evadne::Shader> m_FlatColorShader;

    Evadne::Ref<Evadne::Texture2D> m_BackgroundTexture;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};




