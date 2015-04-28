#include "lib/AES.h"
#include <iostream>

using namespace std;
AES aes;

byte *key;
byte raw[16];
byte result[16];
byte encrypted[16];

inline byte* chararray_to_bytearray(char* chararray) {
  return reinterpret_cast<byte*>(chararray);
};
char* bytearray_to_chararray(byte* bytearray) {
  return reinterpret_cast<char*>(bytearray);
}

int main() {
	char stringkey[16] = "foobar         ";
	key = chararray_to_bytearray(stringkey);
	char chararr[] = "Hallo Welt";
	aes.set_key(key, 16);
	// ========= ENCRYPT ==================
	aes.encrypt(chararray_to_bytearray(chararr), encrypted);
	cout << "Schlüssel: ";
	for(int i=0; i<16; i++) {
		cout << std::hex << (int) key[i];
	}
	cout << endl;
	
	cout << "Cipher: ";
	for(int i=0; i<16; i++) {
                cout << std::hex << (int) encrypted[i] << "." << std::dec;
        }
	cout << endl;
	
	// ========= DECRYPT ===================
	aes.decrypt(encrypted, result);
	
	cout << "Klartext: ";
	for(int i=0; i<16; i++) {
                cout << (int) result[i] << ".";
        }
	cout << endl;
}
