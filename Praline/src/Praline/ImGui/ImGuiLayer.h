#pragma once

#include "Praline/Layer.h"

struct GLFWwindow;

namespace Praline
{
	class MouseButtonPressedEvent;
	class MouseButtonReleasedEvent;
	class MouseMovedEvent;
	class MouseScrolledEvent;
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class KeyTypedEvent;
	class WindowResizeEvent;
}

namespace Praline
{
	class ImGuiLayer : public Layer
	{
	public:
		PRALINE_API ImGuiLayer();
		PRALINE_API ~ImGuiLayer();

		PRALINE_API void OnAttach();
		PRALINE_API void OnDetach();
		PRALINE_API void OnUpdate();
		PRALINE_API void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};
}

