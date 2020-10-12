#pragma once

#include "Core.h"
#include "Window.h"

#include "Praline/LayerStack.h"
#include "Events/ApplicationEvent.h"

class Layer;

namespace Praline
{
	class Application
	{
	public:
		PRALINE_API Application();
		PRALINE_API virtual ~Application();

		PRALINE_API void Run();

		PRALINE_API void OnEvent(Event& e);

		PRALINE_API void PushLayer(Layer* layer);
		PRALINE_API void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Defined by client
	Application* CreateApplication();
}

