#pragma once

#include "Core.h"
#include "Window.h"

#include "Praline/LayerStack.h"
#include "Events/ApplicationEvent.h"

namespace Praline
{
	class Layer;
	class ImGuiLayer;
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

		unsigned int m_VertexArray;
		unsigned int m_IndexArray;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// Defined by client
	Application* CreateApplication();
}

