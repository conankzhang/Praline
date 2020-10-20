#include <Praline.h>

#include <Praline/Renderer/Renderer.h>
#include <Praline/Renderer/Shader.h>
#include <Praline/Renderer/OrthographicCamera.h>

class ExampleLayer : public Praline::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		using namespace Praline;

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVertexBuffer->SetLayout(
			{
				{ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Shader::Create(vertexSource, fragmentSource));

		std::string vertexSourceSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSourceSquare = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_ShaderBlue.reset(Shader::Create(vertexSourceSquare, fragmentSourceSquare));
	}

	void OnUpdate() override
	{
		using namespace Praline;

		RenderCommand::SetClearColor({ 0.004f, 0.086f, 0.153f, 1 });
		RenderCommand::Clear();

		Renderer::BeginScene(m_Camera);

		Renderer::Submit(m_ShaderBlue, m_SquareVertexArray);
		Renderer::Submit(m_Shader, m_VertexArray);

		Renderer::EndScene();

		OnInput();
	}

	void OnInput()
	{
		const float k_cameraSpeed = 0.1f;
		if (Praline::Input::IsKeyPressed(PRALINE_KEY_W))
		{
			glm::vec3 currentCameraPosition = m_Camera.GetPosition();
			currentCameraPosition.y += k_cameraSpeed;

			m_Camera.SetPosition(currentCameraPosition);
		}

		if (Praline::Input::IsKeyPressed(PRALINE_KEY_A))
		{
			glm::vec3 currentCameraPosition = m_Camera.GetPosition();
			currentCameraPosition.x -= k_cameraSpeed;

			m_Camera.SetPosition(currentCameraPosition);
		}

		if (Praline::Input::IsKeyPressed(PRALINE_KEY_S))
		{
			glm::vec3 currentCameraPosition = m_Camera.GetPosition();
			currentCameraPosition.y -= k_cameraSpeed;

			m_Camera.SetPosition(currentCameraPosition);
		}

		if (Praline::Input::IsKeyPressed(PRALINE_KEY_D))
		{
			glm::vec3 currentCameraPosition = m_Camera.GetPosition();
			currentCameraPosition.x += k_cameraSpeed;

			m_Camera.SetPosition(currentCameraPosition);
		}
	}

	void OnEvent(Praline::Event& event) override
	{

	}
private:
	std::shared_ptr<Praline::Shader> m_Shader;
	std::shared_ptr<Praline::VertexArray> m_VertexArray;

	std::shared_ptr<Praline::Shader> m_ShaderBlue;
	std::shared_ptr<Praline::VertexArray> m_SquareVertexArray;

	Praline::OrthographicCamera m_Camera;
};

class Sandbox : public Praline::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Praline::Application* Praline::CreateApplication()
{
	return new Sandbox();
}

