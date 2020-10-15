#include "PralinePCH.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Praline
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		PRALINE_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PRALINE_CORE_ASSERT(status, "Failed to initialize Glad!");

		PRALINE_CORE_INFO("OpenGL Info");
		PRALINE_CORE_INFO("OpenGL Vendor: {0}", glGetString(GL_VENDOR));
		PRALINE_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		PRALINE_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}

