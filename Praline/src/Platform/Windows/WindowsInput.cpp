#include "PralinePCH.h"
#include "WindowsInput.h"

#include "Praline/Application.h"
#include <GLFW/glfw3.h>

namespace Praline
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		const int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		const int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}
}
