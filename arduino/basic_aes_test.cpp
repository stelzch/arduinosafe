#include <AES.h>

AES aes ;

byte key[16];
byte raw[16];
byte result[16];
byte encrypted[16];

byte* chararray_to_bytearray(char* chararray) {
  return reinterpret_cast<byte*>(chararray);
};

char* bytearray_to_chararray(byte* bytearray) {
  return reinterpret_cast<char*>(bytearray);
}

void setup() {
  Serial.begin(9600);
  delay(4000);
  for (int i=1;i<17;i++) {
    key[i-1] = i;
    raw[i-1] = i;
  }
  char chararr[] = "Hallo Welt!!!??";
  byte* bytearr = chararray_to_bytearray(chararr);
  char* reconverted_chararr = bytearray_to_chararray(bytearr);
  Serial.println(aes.set_key(key, 16));
  Serial.println(aes.encrypt(chararray_to_bytearray(chararr), encrypted));
  Serial.println(aes.decrypt(encrypted, result));

  Serial.println("\nkey");
  for (int i=0; i<16; i++) {
    Serial.println(key[i]);
  }
  Serial.println("\nraw_char");
  for (int i=0; i<16; i++) {
    Serial.println(chararr[i]);
  }
  Serial.println("\nraw_byte");
  for (int i=0; i<16; i++) {
    Serial.println(bytearr[i]);
  }
  Serial.println("\nreconverted_char");
  for (int i=0; i<16; i++) {
    Serial.println(reconverted_chararr[i]);
  }
  Serial.println("\nresult");
  for (int i=0; i<16; i++) {
    Serial.println(result[i]);
  }
  Serial.println("\nencrypted");
  for (int i=0; i<16; i++) {
    Serial.println(encrypted[i]);
  }
};
void loop() {};
