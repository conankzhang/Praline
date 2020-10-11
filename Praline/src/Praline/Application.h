#pragma once

#include "Core.h"

namespace Praline
{
	class PRALINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Defined by client
	Application* CreateApplication();
}
