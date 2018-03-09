#include "shared.h"
#include "openssl_w.h"
#include "pkey_store.h"
#include <iostream>

#include "log.h"

void X::init() {
	std::cout << "f2()\n";
}

void X::end() {
	std::cout << "f2()\n";
}
 
void f() {
  std::cout << "f2()\n";
}
 
X::X() {
  std::cout << "X::X()\n";
}
  
void X::mX() {
  std::cout << "X::mX()\n";
}

void X::mXOpenssl() {
	OpenSSLWrapper::createCertificate();

	auto store = std::make_unique<PKeyStore>();
	store->init();

	for (int i = 0; i < 50; i++) {

		EVP_KEY_sptr key = store->getKey();

		ossl_lib::Logger::GetLogger()->error("Key Used");
	}

}