#include "tools.h"
#include "aes.h"
#include "string.h"
#include <stdio.h> // DEBUG only
AES *aes = new AES();
/**
 * Sets the key of the aes encryption engine
 * @param key the key 
 */
void aes_set_key(char *key) {
  if( aes->set_key(chararray_to_bytearray(key), 128) == FAILURE) 
    printf("Error while setting key");
}

/**
 * Encryptes data using AES 
 * @param data the data which will be encrypted
 * @return the encrypted data
 */
char *aes_encrypt(char *data) {
  int txtLength = strlen(data);
  printf("txtLength: %i\n", txtLength);
  char result[txtLength + 1];
  int numEncryptions = txtLength / 16;
  if((txtLength % 16) > 0) {
    numEncryptions++;
  }
  printf("numEncryptions: %i\n", numEncryptions);
  for(int i=0; i<numEncryptions; i++) {
    byte txt[16];
    byte stepResult[16];
      for(int n=0; n<16; n++) {
	if(txtLength > i*16+n) {
	  txt[n] = (byte) data[i*16+n];
	} else {
	  txt[n] = 0x00;
	}
      }
     if (aes->encrypt(txt, stepResult) == FAILURE)
       printf("Error while encrypting");
     strcat(result, (const char *) stepResult);
  }
  return result;
}

/**
 * 
 * Decryptes data using AES 
 * @param data the data which will be decrypted
 * @return the decrypted data
 */
char *aes_decrypt(char *data) {
  int txtLength = strlen(data);
  char result[txtLength + 1];
  int numDecryptions = txtLength / 16;
  if((txtLength % 16) > 0) {
    numDecryptions++;
  }
  
  for(int i=0; i<numDecryptions; i++) {
    byte txt[16];
    byte stepResult[16];
      for(int n=0; n<16; n++) {
	if(txtLength > i*16+n) {
	  txt[n] = (byte) data[i*16+n];
	} else {
	  txt[n] = 0x00;
	}
      }
     if (aes->decrypt(txt, stepResult) == FAILURE)
       printf("Error while decrypting");
     strcat(result, bytearray_to_chararray(stepResult));
  }
  return result;
}