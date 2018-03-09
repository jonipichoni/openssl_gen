#include "pkey_store.h"

#include <thread>
#include "log.h"

#define POOL_SIZE 5
#define DEF_PKEY_SIZE 2048

PKeyStore::PKeyStore() : 
	PKeyStore(DEF_PKEY_SIZE)
{}

PKeyStore::PKeyStore(int keysize) :
	m_fillingPool(false),
	m_keysize(keysize)
{}

PKeyStore::~PKeyStore()
{}

void PKeyStore::init()
{
	ossl_lib::Logger::GetLogger()->error(
		"Initialize Private Key Store called");

	fillPool();

	consumerAsync();
}


EVP_KEY_sptr PKeyStore::getKey()
{

	std::unique_lock<std::mutex> mlock(m_mutex);

	while (m_queue.empty())
	{
		m_cond.wait(mlock);
	}

	auto item = m_queue.front();

	m_queue.pop();

	fillPoolAsync();

	return item;
}

EVP_PKEY* PKeyStore::genereateKey()
{
	// EVP_PKEY is an store of a key
	// independent of the algorithm used
	EVP_PKEY * pkey = EVP_PKEY_new();
	if (!pkey)
	{
		ossl_lib::Logger::GetLogger()->error(
			"Unable to create EVP_PKEY structure.");
		return nullptr;
	}

	RSA * rsa = RSA_generate_key(m_keysize, RSA_F4, NULL, NULL);
	if (!EVP_PKEY_assign_RSA(pkey, rsa))
	{
		ossl_lib::Logger::GetLogger()->error(
			"Unable to generate 2048-bit RSA key.");
		EVP_PKEY_free(pkey);
		return nullptr;
	}

	return pkey;
}

void PKeyStore::fillPool()
{
	m_fillingPool = true;

	while(m_queue.size() < POOL_SIZE)
	{
		EVP_PKEY* key = genereateKey();

		if (!key) {
			ossl_lib::Logger::GetLogger()->error(
				"Key Generation failed");

			break;
		}

		EVP_KEY_sptr skey(key, EVP_PKEY_free);

		std::unique_lock<std::mutex> mlock(m_mutex);

		m_queue.push(skey);

		mlock.unlock();

		m_cond.notify_one();

		ossl_lib::Logger::GetLogger()->error(
			"Key Generated");
	}	

	m_fillingPool = false;
}

void PKeyStore::fillPoolAsync()
{
	if (!m_fillingPool)
	{
		std::thread threadObj(&PKeyStore::fillPool, this);
		threadObj.detach();
	}
}

void PKeyStore::consumer()
{
	for(int i = 0; i < 10; i++) {
		getKey();
		ossl_lib::Logger::GetLogger()->error(
			"Key Consumed");
	}
}

void PKeyStore::consumerAsync()
{
	for (int i = 0; i < 4; i++) {
		std::thread threadObj(&PKeyStore::consumer, this);
		threadObj.detach();
	}
}