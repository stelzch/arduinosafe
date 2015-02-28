#ifndef KRYPTO_H_
#define KRYPTO_H_

#include <string>
using std::string;

class Krypto {
public:
	virtual string encrypt(string text) = 0;
	virtual string decrypt(string text) = 0;
};

#endif