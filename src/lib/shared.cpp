#include "shared.h"
#include "openssl_w.h"

#include <iostream>

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
}