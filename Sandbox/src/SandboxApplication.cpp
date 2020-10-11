#include <Praline.h>

class Sandbox : public Praline::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Praline::Application* Praline::CreateApplication()
{
	return new Sandbox();
}
