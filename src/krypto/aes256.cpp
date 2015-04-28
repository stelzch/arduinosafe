#include "lib/AES.h"
#include "aes256.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

AES256Krypto::AES256Krypto(string key) {
    if(key.length() < 32) {
      cerr << "Schlüssel zu kurz" << endl;
      exit(-1);
    }
    byte *bytekey = const_cast<byte *>(reinterpret_cast<const byte*>(key.c_str()));
    ctx.set_key(bytekey, 32);
}
string AES256Krypto::encrypt(string txt) {
  string encrypted;
  int txtLength = txt.length();
  int numEncryptions = txtLength / 16;
  if((txtLength % 16) > 0) {
    numEncryptions++;
  }
  for(int i=0;i<numEncryptions;i++) {
    byte data[16];
    byte result[16];
      for(int n=0; n<16; n++) {
	if(txtLength > i*16+n) {
	  data[n] = (byte) txt.c_str()[i*16+n];
	} else {
	  data[n] = 0x00;
	}
      }
    ctx.encrypt(data, result);
    encrypted += string((char *)result);
  }
  return encrypted;
}
string AES256Krypto::decrypt(string txt) {
  string decrypted;
  int txtLength = txt.length();
  int numDecryptions = txtLength / 16;
  if((txtLength % 16) > 0) {
    cerr << "AES Decrypt: Corrupted string - Length not divisible by 16" << endl;
    exit(1);
  }
  for(int i=0;i<numDecryptions;i++) {
    byte data[16];
    byte result[16];
      for(int n=0; n<16; n++) {
	if(txtLength > i*16+n) {
	  data[n] = (byte) txt.c_str()[i*16+n];
	} else {
	  data[n] = 0x00;
	}
      }
    ctx.decrypt(data, result);
    decrypted += string((char *)result);
  }
  return decrypted;
}
AES256Krypto::~AES256Krypto() {
    ctx.clean();
}