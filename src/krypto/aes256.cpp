#include "aes256.h"
#include <cstring>

AES256Krypto::AES256Krypto(string key) {
	char *keyArray;
	strcpy(keyArray, key.c_str());
	aes256_init(&ctx, reinterpret_cast<unsigned char *>(keyArray));
}
string AES256Krypto::encrypt(string txt) {
	char txtArray[txt.size() + 1];
	strcpy(txtArray, txt.c_str()); // Make char Array out of String
	aes256_encrypt_ecb(&ctx, reinterpret_cast<unsigned char *>(txtArray));
	return string(txtArray);
}
string AES256Krypto::decrypt(string txt) {
	char txtArray[txt.size() + 1];
	strcpy(txtArray, txt.c_str()); // Make char Array out of String
	aes256_decrypt_ecb(&ctx, reinterpret_cast<unsigned char *>(txtArray));
	return string(txtArray);
}
AES256Krypto::~AES256Krypto() {
	aes256_done(&ctx);
}