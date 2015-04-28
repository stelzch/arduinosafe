#include "krypto/aes256.h"
#include "compat.h"

int main() {
	AES256Krypto *krypto = new AES256Krypto("Testdfffffffffffffffffffffffffffffffffffffffffffffffff");
	
	string dec = krypto->decrypt(krypto->encrypt("0123456789"));
	
	string s = "test";
	return 0;
}
