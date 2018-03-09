#pragma once

#include <queue>
#include <mutex>
#include <atomic>

#include "openssl_defs.h"

class PKeyStore {

public:

	PKeyStore();
	PKeyStore(int keysize);

	~PKeyStore();

	PKeyStore(const PKeyStore&) = delete;
	PKeyStore& operator=(const PKeyStore&) = delete;

	void init();
	EVP_KEY_sptr getKey();

private:

	void fillPool();
	void fillPoolAsync();
	EVP_PKEY* genereateKey();
	void consumerAsync();
	void consumer();

private:
	std::queue<EVP_KEY_sptr>	m_queue;
	std::mutex					m_mutex;
	std::condition_variable		m_cond;
	std::atomic<bool>			m_fillingPool;
	int							m_keysize;
};