#include "evpch.h"
#include "OrthographicCameraController.h"

#include "Evadne/Input/Input.h"
#include "Evadne/Input/KeyCodes.h"

Evadne::OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    :m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
{
}

void Evadne::OrthographicCameraController::OnUpdate(Timestep ts)
{
	
	if (Input::IsKeyPressed(EV_KEY_A))
		m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
	else if (Input::IsKeyPressed(EV_KEY_D))
		m_CameraPosition.x += m_CameraTranslationSpeed * ts;
	if (Input::IsKeyPressed(EV_KEY_W))
		m_CameraPosition.y += m_CameraTranslationSpeed * ts;
	else if (Input::IsKeyPressed(EV_KEY_S))
		m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
	if (m_Rotation)
	{
		if (Input::IsKeyPressed(EV_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Input::IsKeyPressed(EV_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		m_Camera.SetRotation(m_CameraRotation);
	}
	m_Camera.SetPosition(m_CameraPosition);
	m_CameraTranslationSpeed = m_ZoomLevel;
}

void Evadne::OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(EV_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(EV_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool Evadne::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool Evadne::OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}
