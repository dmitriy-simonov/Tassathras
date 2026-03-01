#pragma once
#include <spdlog/spdlog.h>
#include <memory>

namespace Tassathras
{
	class Log
	{
	public:
		static void init();

		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}
//core logger macros
#define TS_CORE_TRACE(...)    ::Tassathras::Log::getCoreLogger()->trace(__VA_ARGS__)
#define TS_CORE_INFO(...)     ::Tassathras::Log::getCoreLogger()->info(__VA_ARGS__)
#define TS_CORE_WARN(...)     ::Tassathras::Log::getCoreLogger()->warn(__VA_ARGS__)
#define TS_CORE_ERROR(...)    ::Tassathras::Log::getCoreLogger()->error(__VA_ARGS__)
#define TS_CORE_CRITICAL(...) ::Tassathras::Log::getCoreLogger()->critical(__VA_ARGS__)

//client logger macros
#define TS_TRACE(...)         ::Tassathras::Log::getClientLogger()->trace(__VA_ARGS__)
#define TS_INFO(...)          ::Tassathras::Log::getClientLogger()->info(__VA_ARGS__)
#define TS_WARN(...)          ::Tassathras::Log::getClientLogger()->warn(__VA_ARGS__)
#define TS_ERROR(...)         ::Tassathras::Log::getClientLogger()->error(__VA_ARGS__)
#define TS_CRITICAL(...)      ::Tassathras::Log::getClientLogger()->critical(__VA_ARGS_