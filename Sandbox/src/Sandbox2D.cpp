#include "Sandbox2D.h"

#include <ImGui/imgui.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)

{

}

void Sandbox2D::OnAttach()
{
	m_SquareVertexArray = Praline::VertexArray::Create();
	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	std::shared_ptr <Praline::VertexBuffer > squareVertexBuffer;
	squareVertexBuffer = Praline::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

	squareVertexBuffer->SetLayout(
		{
			{Praline::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Praline::IndexBuffer> squareIndexBuffer = Praline::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

	m_FlatColorShader = Praline::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Praline::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);

	Praline::RenderCommand::SetClearColor({ 0.004f, 0.086f, 0.153f, 1 });
	Praline::RenderCommand::Clear();

	Praline::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Praline::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Praline::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Praline::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Praline::Renderer::EndScene();

}

void Sandbox2D::OnEvent(Praline::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

