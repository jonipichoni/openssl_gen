#pragma once

#include "spdlog/spdlog.h"
namespace spd = spdlog;

namespace ossl_lib
{
	typedef std::shared_ptr<spdlog::logger> s_log;

	class Logger
	{
	public:
		static s_log GetLogger();
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger() = delete;

	private:
		
		static s_log mpLog;
	};
}