#pragma once

#ifdef PRALINE_PLATFORM_WINDOWS

extern Praline::Application* Praline::CreateApplication();

int main(int argc, char** argv)
{
	Praline::Log::Init();

	auto application = Praline::CreateApplication();
	application->Run();
	delete application;
}

#endif

