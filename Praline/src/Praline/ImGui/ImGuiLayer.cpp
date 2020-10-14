#include "PralinePCH.h"
#include "ImGuiLayer.h"

#include "Praline/Application.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "Praline/Events/MouseEvent.h"
#include "Praline/Events/KeyEvent.h"
#include "Praline/Events/ApplicationEvent.h"

#include "Praline/KeyCodes.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Praline
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = PRALINE_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = PRALINE_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = PRALINE_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = PRALINE_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = PRALINE_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = PRALINE_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = PRALINE_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = PRALINE_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = PRALINE_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = PRALINE_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = PRALINE_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = PRALINE_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = PRALINE_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = PRALINE_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = PRALINE_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = PRALINE_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = PRALINE_KEY_A;
		io.KeyMap[ImGuiKey_C] = PRALINE_KEY_C;
		io.KeyMap[ImGuiKey_V] = PRALINE_KEY_V;
		io.KeyMap[ImGuiKey_X] = PRALINE_KEY_X;
		io.KeyMap[ImGuiKey_Y] = PRALINE_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = PRALINE_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		Application& app = Application::Get();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		const float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}


	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		// Modifiers are not reliable across systems
		io.KeyCtrl = io.KeysDown[PRALINE_KEY_LEFT_CONTROL] || io.KeysDown[PRALINE_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[PRALINE_KEY_LEFT_SHIFT] || io.KeysDown[PRALINE_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[PRALINE_KEY_LEFT_ALT] || io.KeysDown[PRALINE_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[PRALINE_KEY_LEFT_SUPER] || io.KeysDown[PRALINE_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		// Modifiers are not reliable across systems
		io.KeyCtrl = io.KeysDown[PRALINE_KEY_LEFT_CONTROL] || io.KeysDown[PRALINE_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[PRALINE_KEY_LEFT_SHIFT] || io.KeysDown[PRALINE_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[PRALINE_KEY_LEFT_ALT] || io.KeysDown[PRALINE_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[PRALINE_KEY_LEFT_SUPER] || io.KeysDown[PRALINE_KEY_RIGHT_SUPER];

		return true;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		const int keyCode = e.GetKeyCode();
		if (keyCode > 0 && keyCode < 0x10000)
		{
			io.AddInputCharacter((unsigned short)keyCode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

}
