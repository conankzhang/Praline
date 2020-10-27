#pragma once

#include "Praline.h"

class Sandbox2D: public Praline::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Praline::Timestep timestep) override;
	virtual void OnEvent(Praline::Event& event) override;
	virtual void OnImGuiRender() override;

private:
	Praline::OrthographicCameraController m_CameraController;

	Praline::Ref<Praline::VertexArray> m_SquareVertexArray;
	Praline::Ref<Praline::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

