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
		PRALINE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Praline::Event& event) override
	{
		PRALINE_TRACE("{0}", event);
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

