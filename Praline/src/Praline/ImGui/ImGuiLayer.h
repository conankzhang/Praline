#pragma once

#include "Praline/Layer.h"

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
		float m_Time = 0.0f;
	};
}

