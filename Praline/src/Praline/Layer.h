#pragma once

#include "Praline/Core.h"
#include "Praline/Events/Event.h"

namespace Praline
{
	class Layer
	{
	public:
		PRALINE_API Layer(const std::string& name = "Layer");
		PRALINE_API virtual ~Layer();

		PRALINE_API virtual void OnAttach() {}
		PRALINE_API virtual void OnDetach() {}
		PRALINE_API virtual void OnUpdate() {}
		PRALINE_API virtual void OnEvent(Event& event) {}

		PRALINE_API inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}

