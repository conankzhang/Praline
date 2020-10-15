#pragma once

#include "Praline/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Praline
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

