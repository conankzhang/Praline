#include <Praline.h>

class ExampleLayer : public Praline::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray.reset(Praline::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Praline::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Praline::VertexBuffer::Create(vertices, sizeof(vertices)));

		Praline::BufferLayout layout = {
			{Praline::ShaderDataType::Float3, "a_Position" },
			{Praline::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Praline::IndexBuffer> indexBuffer;
		indexBuffer.reset(Praline::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Praline::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};

		std::shared_ptr <Praline::VertexBuffer > squareVertexBuffer;
		squareVertexBuffer.reset(Praline::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVertexBuffer->SetLayout(
			{
				{Praline::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Praline::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Praline::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

		m_Shader.reset(Praline::Shader::Create(vertexSource, fragmentSource));

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

		m_ShaderBlue.reset(Praline::Shader::Create(vertexSourceSquare, fragmentSourceSquare));
	}

	void OnUpdate(Praline::Timestep timestep) override
	{
		UpdateCamera(timestep);

		Praline::RenderCommand::SetClearColor({ 0.004f, 0.086f, 0.153f, 1 });
		Praline::RenderCommand::Clear();

		Praline::Renderer::BeginScene(m_Camera);

		Praline::Renderer::Submit(m_ShaderBlue, m_SquareVertexArray);
		Praline::Renderer::Submit(m_Shader, m_VertexArray);

		Praline::Renderer::EndScene();
	}

	void UpdateCamera(Praline::Timestep timestep)
	{
		const float k_cameraMovementSpeed = 5.0f * timestep;
		glm::vec3 currentCameraPosition = m_Camera.GetPosition();

		if (Praline::Input::IsKeyPressed(PRALINE_KEY_W))
		{
			currentCameraPosition.y += k_cameraMovementSpeed;
		}
		else if (Praline::Input::IsKeyPressed(PRALINE_KEY_S))
		{
			currentCameraPosition.y -= k_cameraMovementSpeed;
		}

		if (Praline::Input::IsKeyPressed(PRALINE_KEY_A))
		{
			currentCameraPosition.x -= k_cameraMovementSpeed;
		}
		else if (Praline::Input::IsKeyPressed(PRALINE_KEY_D))
		{
			currentCameraPosition.x += k_cameraMovementSpeed;
		}

		const float k_cameraRotationSpeed = 180.0f * timestep;
		float currentCameraRotation = m_Camera.GetRotation();
		if (Praline::Input::IsKeyPressed(PRALINE_KEY_Q))
		{
			currentCameraRotation -= k_cameraRotationSpeed;
		}
		else if (Praline::Input::IsKeyPressed(PRALINE_KEY_E))
		{
			currentCameraRotation += k_cameraRotationSpeed;
		}

		m_Camera.SetPosition(currentCameraPosition);
		m_Camera.SetRotation(currentCameraRotation);
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

