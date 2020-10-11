#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Praline
{
	class PRALINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

// Core Log Macros-----------------------------------------------------------------------------------------------------
#define PRALINE_CORE_TRACE(...) ::Praline::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PRALINE_CORE_INFO(...) ::Praline::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PRALINE_CORE_WARN(...) ::Praline::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PRALINE_CORE_ERROR(...) ::Praline::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PRALINE_CORE_FATAL(...) ::Praline::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros-----------------------------------------------------------------------------------------------------
#define PRALINE_CLIENT_TRACE(...) ::Praline::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PRALINE_CLIENT_INFO(...) ::Praline::Log::GetClientLogger()->info(__VA_ARGS__)
#define PRALINE_CLIENT_WARN(...) ::Praline::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PRALINE_CLIENT_ERROR(...) ::Praline::Log::GetClientLogger()->error(__VA_ARGS__)
#define PRALINE_CLIENT_FATAL(...) ::Praline::Log::GetClientLogger()->fatal(__VA_ARGS__)

