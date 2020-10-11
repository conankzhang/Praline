#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Praline
{
	class Log
	{
	public:
		PRALINE_API static void Init();

		PRALINE_API inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		PRALINE_API inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

// Core Log Macros-----------------------------------------------------------------------------------------------------
#define PRALINE_CORE_TRACE(...) ::Praline::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PRALINE_CORE_INFO(...)  ::Praline::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PRALINE_CORE_WARN(...)  ::Praline::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PRALINE_CORE_ERROR(...) ::Praline::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PRALINE_CORE_FATAL(...) ::Praline::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros-----------------------------------------------------------------------------------------------------
#define PRALINE_TRACE(...) ::Praline::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PRALINE_INFO(...)  ::Praline::Log::GetClientLogger()->info(__VA_ARGS__)
#define PRALINE_WARN(...)  ::Praline::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PRALINE_ERROR(...) ::Praline::Log::GetClientLogger()->error(__VA_ARGS__)
#define PRALINE_FATAL(...) ::Praline::Log::GetClientLogger()->fatal(__VA_ARGS__)


