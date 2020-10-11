#pragma once

#ifdef PRALINE_PLATFORM_WINDOWS

extern Praline::Application* Praline::CreateApplication();

int main(int argc, char** argv)
{
	Praline::Log::Init();
	PRALINE_CORE_INFO("Core Initialized");
	PRALINE_INFO("Client Initialized");

	auto application = Praline::CreateApplication();
	application->Run();
	delete application;
}

#endif

