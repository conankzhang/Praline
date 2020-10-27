#include <Praline.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Praline::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray = Praline::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Praline::VertexBuffer> vertexBuffer;
		vertexBuffer = Praline::VertexBuffer::Create(vertices, sizeof(vertices));

		Praline::BufferLayout layout = {
			{Praline::ShaderDataType::Float3, "a_Position" },
			{Praline::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Praline::IndexBuffer> indexBuffer;
		indexBuffer = Praline::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray = Praline::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr <Praline::VertexBuffer > squareVertexBuffer;
		squareVertexBuffer = Praline::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVertexBuffer->SetLayout(
			{
				{Praline::ShaderDataType::Float3, "a_Position" },
				{Praline::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Praline::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = Praline::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = Praline::Shader::Create("VertexPosColor", vertexSource, fragmentSource);

		std::string vertexSourceSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSourceSquare = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Praline::Shader::Create("FlatColor", vertexSourceSquare, fragmentSourceSquare);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Praline::Texture2D::Create("assets/textures/Checkerboard.png");
		m_TextureCZ = Praline::Texture2D::Create("assets/textures/CZ.png");

		std::dynamic_pointer_cast<Praline::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Praline::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Praline::Timestep timestep) override
	{
		UpdateCamera(timestep);

		Praline::RenderCommand::SetClearColor({ 0.004f, 0.086f, 0.153f, 1 });
		Praline::RenderCommand::Clear();

		Praline::Renderer::BeginScene(m_Camera);

		std::dynamic_pointer_cast<Praline::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Praline::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.08f));
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				const glm::vec3 position(x * 0.1f, y * 0.1f, 0.0f);
				const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				Praline::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		Praline::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_TextureCZ->Bind();
		Praline::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//Praline::Renderer::Submit(m_Shader, m_VertexArray);

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Praline::Event& event) override
	{

	}
private:
	Praline::ShaderLibrary m_ShaderLibrary;
	Praline::Ref<Praline::Shader> m_Shader;
	Praline::Ref<Praline::VertexArray> m_VertexArray;

	Praline::Ref<Praline::Shader> m_FlatColorShader;
	Praline::Ref<Praline::VertexArray> m_SquareVertexArray;

	Praline::Ref<Praline::Texture> m_Texture;

	Praline::Ref<Praline::Texture> m_TextureCZ;

	Praline::OrthographicCamera m_Camera;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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

