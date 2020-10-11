#pragma once

#include "Core.h"
#include "Window.h"

namespace Praline
{
	class Application
	{
	public:
		PRALINE_API Application();
		PRALINE_API virtual ~Application();

		PRALINE_API void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// Defined by client
	Application* CreateApplication();
}

