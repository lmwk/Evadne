#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}
void Sandbox2D::OnAttach()
{
	EV_PROFILE_FUNCTION();

	m_BackgroundTexture = Evadne::Texture2D::Create("assets/textures/IMG_0467.jpg");
}
void Sandbox2D::OnDetach()
{
	EV_PROFILE_FUNCTION();
}
void Sandbox2D::OnUpdate(Evadne::Timestep ts)
{
	EV_PROFILE_FUNCTION();


	m_CameraController.OnUpdate(ts);
	

	{
		EV_PROFILE_SCOPE("Renderer Prep");
		Evadne::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Evadne::RenderCommand::Clear();
	}

	{
		EV_PROFILE_SCOPE("Renderer Draw");

		Evadne::Renderer2D::BeginScene(m_CameraController.GetCamera());
		// Evadne::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Evadne::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Evadne::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Evadne::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_BackgroundTexture, 10.0f);
		Evadne::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_BackgroundTexture, 20.0f);

		Evadne::Renderer::EndScene();
	}
}
void Sandbox2D::OnImGuiRender()
{
	EV_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}
void Sandbox2D::OnEvent(Evadne::Event& e)
{
	m_CameraController.OnEvent(e);
}