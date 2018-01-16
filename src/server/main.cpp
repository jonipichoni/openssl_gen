#include "shared.h"
#include "spdlog/spdlog.h"
#include <openssl\ssl.h>

namespace spd = spdlog;

//OpenSSL 1.0.2n
#if (OPENSSL_VERSION_NUMBER < 0x10002FFFFL)
#ifdef _WIN32
extern "C"
{
#undef APPMACROS_ONLY 
#include <openssl/applink.c> 
}
#endif
#endif

int main() {

	auto console = spd::stdout_color_mt("console");
	console->info("Welcome to spdlog!");

	auto my_logger = spd::basic_logger_mt("basic_logger", "basic-log.log");
	my_logger->flush_on(spd::level::err);
	my_logger->error("Some log message");
	my_logger->info("Some log message");

	f();
	X x;
	x.mX();
	x.mXOpenssl();

  return 0;
}
 