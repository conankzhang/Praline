#pragma once

#include "Praline/Input.h"

namespace Praline
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) const override;
		virtual bool IsMouseButtonPressedImpl(int button) const override;
		virtual std::pair<float, float> GetMousePositionImpl() const override;

	};
}

