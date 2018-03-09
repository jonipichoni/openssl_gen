#pragma once

#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <memory>

using BN_ptr = std::unique_ptr<BIGNUM, decltype(&::BN_free)>;
using RSA_ptr = std::unique_ptr<RSA, decltype(&::RSA_free)>;
using EVP_KEY_ptr = std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)>;
using BIO_FILE_ptr = std::unique_ptr<BIO, decltype(&::BIO_free)>;

using BN_sptr = std::shared_ptr<BIGNUM>;
using RSA_sptr = std::shared_ptr<RSA>;
using EVP_KEY_sptr = std::shared_ptr<EVP_PKEY>;
using BIO_FILE_sptr = std::shared_ptr<BIO>;
