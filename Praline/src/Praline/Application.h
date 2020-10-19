#pragma once

#include "Core.h"
#include "Window.h"

#include "Praline/LayerStack.h"
#include "Events/ApplicationEvent.h"

namespace Praline
{
	class Layer;
	class ImGuiLayer;
	class Shader;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
}

namespace Praline
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// Defined by client
	Application* CreateApplication();
}

