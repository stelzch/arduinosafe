#ifndef AES256_H_
#define AES256_H_

#include "lib/AES.h"
#include "krypto.h"
#include <string>

class AES256Krypto : public Krypto {
public:
	AES256Krypto(string key);
	string encrypt(string txt);
	string decrypt(string txt);
	virtual ~AES256Krypto();
private:
	AES ctx;
};

#endif