#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({0.2f, 0.3f, 0.8f, 1.0f})
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
	
	Evadne::Renderer2D::ResetStats();
	{
		EV_PROFILE_SCOPE("Renderer Prep");
		Evadne::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Evadne::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		EV_PROFILE_SCOPE("Renderer Draw");

		Evadne::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Evadne::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Evadne::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Evadne::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Evadne::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_BackgroundTexture, 10.0f);
		Evadne::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_BackgroundTexture, 20.0f);
		Evadne::Renderer2D::EndScene();

		Evadne::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Evadne::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Evadne::Renderer2D::EndScene();
	}
}
void Sandbox2D::OnImGuiRender()
{
	EV_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	auto stats = Evadne::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
void Sandbox2D::OnEvent(Evadne::Event& e)
{
	m_CameraController.OnEvent(e);
}