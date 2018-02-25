#include "log.h"

namespace ossl_lib
{
	s_log Logger::mpLog = nullptr;

	s_log Logger::GetLogger() {

		if (mpLog == nullptr) {
			mpLog = spdlog::basic_logger_mt("ossl_lib", "ossl_lib.log");
			mpLog->flush_on(spdlog::level::err);
		}

		return mpLog;
	}
}