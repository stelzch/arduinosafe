#include <AES.h>

AES aes ;

byte key[16];
byte raw[16];
byte result[16];
byte encrypted[16];

void setup() {
  Serial.begin(9600);
  delay(4000);
  for (int i=1;i<17;i++) {
    key[i-1] = i;
    key[i-1] = i;
  }
  Serial.println(aes.set_key(key, 16));
  Serial.println(aes.encrypt(raw, encrypted));
  Serial.println(aes.decrypt(encrypted, result));

  Serial.println("\nkey");
  for (int i=0; i<16; i++) {
    Serial.println(key[i]);
  }
  Serial.println("\nraw");
  for (int i=0; i<16; i++) {
    Serial.println(raw[i]);
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
