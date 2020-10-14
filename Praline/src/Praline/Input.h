#pragma once

#include "Praline/Core.h"

namespace Praline
{
	class PRALINE_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) const = 0;
		virtual bool IsMouseButtonPressedImpl(int button) const = 0;
		virtual std::pair<float, float> GetMousePositionImpl() const = 0;

	private:
		static Input* s_Instance;

	};
}
