#ifndef KRYPTO_H_
#define KRYPTO_H_

#include "../compat.h"

class Krypto {
public:
	virtual string encrypt(string text) = 0;
	virtual string decrypt(string text) = 0;
};

#endif