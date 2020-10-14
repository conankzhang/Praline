#pragma once

#include "Praline/Window.h"
#include <GLFW/glfw3.h>

namespace Praline
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }


		inline virtual void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() override { return m_Window; };

	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width = 0;
			unsigned int Height = 0;
			bool VSync = false;

			EventCallbackFunction EventCallback;
		};

		WindowData m_Data;
	};
}

