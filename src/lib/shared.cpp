#include "shared.h"
#include "openssl_w.h"

#include <iostream>
 
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