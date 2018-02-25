#include "shared.h"
#include "spdlog/spdlog.h"
#include <openssl\ssl.h>

#include <map>

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

auto g_my_logger = spd::basic_logger_mt("basic_logger", "basic-log.log");

class TestClass
{
	// Access specifier
public:
	TestClass() {
		g_my_logger->error("Constructor called");
		id = 999;
	}
	TestClass(int _id) {
		g_my_logger->error("Constructor called");
		id = _id;
	}
	~TestClass() {
		g_my_logger->error("Deleter called");
	}

	TestClass(const TestClass& testClass) {
		g_my_logger->error("Copy Constructor called");
		id = testClass.id;
	}
	TestClass& operator=(const TestClass& testClass) {
		g_my_logger->error("Assignment called");
		id = testClass.id;
	}
	TestClass(TestClass&& testClass) {
		g_my_logger->error("Move Constructor called");
		id = std::move(testClass.id);
	}
	TestClass(const TestClass&& testClass) {
		g_my_logger->error("const Move Constructor called");
		id = std::move(testClass.id);
	}

	// Data Members
	int id;
};

void TestFunc() {

	std::map<int, std::unique_ptr<TestClass>> myMap;

	// Create unique ptr on map
	myMap[0] = std::make_unique<TestClass>(0);

	// Get Unique Ptr
	std::unique_ptr<TestClass> myPointer = std::move(myMap[0]);

	g_my_logger->error("Pointer Value: "+std::to_string(myPointer->id));
}

int main() {

	/*my_logger->flush_on(spd::level::err);

	TestFunc();*/

	auto console = spd::stdout_color_mt("console");
	console->info("Welcome to spdlog!");

	/*auto my_logger = spd::basic_logger_mt("basic_logger", "basic-log.log");
	my_logger->flush_on(spd::level::err);
	my_logger->error("Some log message");
	my_logger->info("Some log message");*/

	f();
	X x;
	x.mX();
	x.mXOpenssl();

	//my_logger->error("--------------------------------------------------------------");

	// Release and close all loggers
	spd::drop_all();

  return 0;
}
 