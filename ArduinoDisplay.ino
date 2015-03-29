#include <Bounce2.h>
#include <LiquidCrystal.h> //http://engineeringlearning.blogspot.de/2013/10/interfacing-lcd-without-potentiometer.html


char ch;
int Contrast=15;
int buttonPin = 7;
int rueckgabe;
int i = 1;
char* eintraege[] = {"Menue", "Passwort-Auswahl", "AFA", "MPasswort aendern", "Kiwi"};
char* test[0];

// inits
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Bounce weiterBtn = Bounce(); 

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(buttonPin, INPUT); //Button
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  // Serial.begin(9600);
  digitalWrite(13,LOW);
  delay(1000);
  digitalWrite(13,HIGH);
  weiterBtn.attach(buttonPin);
  weiterBtn.interval(5);
}
void loop()
{
  showMenu(eintraege);
  delay(500);
  schreibeZeile1("ENDE");
  delay(2000);
}

void schreibeZeile1(char content[])
{
lcd.setCursor(0, 0);
lcd.print("                ");
lcd.setCursor(0, 0);
lcd.print(content);
}

void schreibeZeile2(char content[])
{
lcd.setCursor(0, 1);
lcd.print("                ");
lcd.setCursor(0, 1);
lcd.print(content);
}

int showMenu(char* entries[])
{
schreibeZeile1(entries[0]);
boolean endeSchleife = false;
while (endeSchleife == false)
{
  schreibeZeile2(entries[i]);
  
  while(weiterBtn.update() == 0) { };
  
  if(weiterBtn.read() == 1)
  {
    i++;
  }
  
  if (*(entries[i]) == 0)
  {
    i = 1;
  }
}
lcd.clear();
return rueckgabe;
}
