#pragma once

#include "Praline/Core.h"
#include "Layer.h"

#include <vector>
namespace Praline
{
	class LayerStack
	{
	public:
		PRALINE_API LayerStack();
		PRALINE_API ~LayerStack();

		PRALINE_API void PushLayer(Layer* layer);
		PRALINE_API void PushOverlay(Layer* overlay);
		PRALINE_API void PopLayer(Layer* layer);
		PRALINE_API void PopOverlay(Layer* overlay);

		PRALINE_API std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		PRALINE_API std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}

