#pragma once

#include "Evadne.h"

class ExampleLayer : public Evadne::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Evadne::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Evadne::Event& e) override;
private:
	Evadne::ShaderLibrary m_ShaderLibrary;
	Evadne::Ref<Evadne::Shader> m_Shader;
	Evadne::Ref<Evadne::VertexArray> m_VertexArray;
	Evadne::Ref<Evadne::Shader> m_FlatColorShader;
	Evadne::Ref<Evadne::VertexArray> m_SquareVA;

	Evadne::Ref<Evadne::Texture2D> m_Texture, m_MinecraftSkinTexture;

	Evadne::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
