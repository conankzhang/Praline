#include "PralinePCH.h"
#include "OrthographicCameraController.h"

#include "Praline/Core/Input.h"
#include "Praline/Core/KeyCodes.h"

namespace Praline
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		glm::vec3 currentCameraPosition = m_Camera.GetPosition();

		m_CameraTranslationSpeed = m_ZoomLevel;
		const float k_cameraTranslationSpeed = m_CameraTranslationSpeed * timestep;
		if (Input::IsKeyPressed(PRALINE_KEY_W))
		{
			currentCameraPosition.y += k_cameraTranslationSpeed;
		}
		else if (Input::IsKeyPressed(PRALINE_KEY_S))
		{
			currentCameraPosition.y -= k_cameraTranslationSpeed;
		}

		if (Input::IsKeyPressed(PRALINE_KEY_A))
		{
			currentCameraPosition.x -= k_cameraTranslationSpeed;
		}
		else if (Input::IsKeyPressed(PRALINE_KEY_D))
		{
			currentCameraPosition.x += k_cameraTranslationSpeed;
		}

		m_Camera.SetPosition(currentCameraPosition);

		if (m_Rotation)
		{
			const float k_cameraRotationSpeed = m_CameraRotationSpeed * timestep;
			float currentCameraRotation = m_Camera.GetRotation();
			if (Input::IsKeyPressed(PRALINE_KEY_Q))
			{
				currentCameraRotation -= k_cameraRotationSpeed;
			}
			else if (Input::IsKeyPressed(PRALINE_KEY_E))
			{
				currentCameraRotation += k_cameraRotationSpeed;
			}

			m_Camera.SetRotation(currentCameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

}
