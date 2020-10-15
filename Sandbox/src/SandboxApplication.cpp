#include <Praline.h>

class ExampleLayer : public Praline::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{

	}

	void OnEvent(Praline::Event& event) override
	{

	}
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

