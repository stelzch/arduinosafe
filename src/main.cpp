#include "krypto/aes256.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	AES256Krypto *krypto = new AES256Krypto("Testdfffffffffffffffffffffffffffffffffffffffffffffffff");
	
	string dec = krypto->decrypt(krypto->encrypt("01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"));
	
	cout << dec << endl;
	return 0;
}
