#pragma once

#include <queue>
#include <mutex>

#include "openssl_defs.h"

class PKeyStore {

public:
	PKeyStore();
	~PKeyStore();
	void init();
	EVP_KEY_sptr getKey();

private:

	void fillPool();

	void fillPoolThreaded();

	EVP_PKEY* genereateKey();



private:
	std::queue<EVP_KEY_sptr> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cond;
};