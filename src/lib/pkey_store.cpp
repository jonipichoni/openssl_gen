#include "pkey_store.h"

#include <thread>
#include "log.h"

#define POOL_SIZE 5

PKeyStore::PKeyStore() {

}
PKeyStore::~PKeyStore() {

}

void PKeyStore::init() {

	ossl_lib::Logger::GetLogger()->error("Initialize Private Key Store called");

	fillPool();
}


EVP_KEY_sptr PKeyStore::getKey() {

	std::unique_lock<std::mutex> mlock(m_mutex);

	while (m_queue.empty())
	{
		m_cond.wait(mlock);
	}

	auto item = m_queue.front();

	m_queue.pop();

	fillPoolThreaded();

	return item;
}


/* Generates a 2048-bit RSA key. */
EVP_PKEY* PKeyStore::genereateKey()
{
	/* Allocate memory for the EVP_PKEY structure. */
	EVP_PKEY * pkey = EVP_PKEY_new();
	if (!pkey)
	{
		ossl_lib::Logger::GetLogger()->error("Unable to create EVP_PKEY structure.");
		return nullptr;
	}

	/* Generate the RSA key and assign it to pkey. */
	RSA * rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	if (!EVP_PKEY_assign_RSA(pkey, rsa))
	{
		ossl_lib::Logger::GetLogger()->error("Unable to generate 2048-bit RSA key.");
		EVP_PKEY_free(pkey);
		return nullptr;
	}

	/* The key has been generated, return it. */
	return pkey;
}

void PKeyStore::fillPool()
{
	std::unique_lock<std::mutex> mlock(m_mutex);

	while(m_queue.size() < POOL_SIZE)
	{
		EVP_PKEY* key = genereateKey();

		ossl_lib::Logger::GetLogger()->error("Key Generated");

		if (!key) {
			break;
		}

		EVP_KEY_sptr skey(key, EVP_PKEY_free);
		m_queue.push(skey);
	}

	mlock.unlock();

	m_cond.notify_one();
}

void PKeyStore::fillPoolThreaded()
{
	std::thread threadObj(&PKeyStore::fillPool,this);
	threadObj.detach();
}