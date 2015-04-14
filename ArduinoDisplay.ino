#include <Bounce2.h>
#include <LiquidCrystal.h> //http://engineeringlearning.blogspot.de/2013/10/interfacing-lcd-without-potentiometer.html

#define weiterBtnPin 7
#define zurueckBtnPin 10
#define okBtnPin 8
#define aufwaertsBtnPin 9

char ch;
int Contrast=15;
int i = 1;


char* eintraege[] = {"Menue", "Passwort-Auswahl", "AFA", "MPasswort aendern", "Kiwi", ""};


char* test[0];

// inits
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


Bounce weiterBtn = Bounce(); 
Bounce zurueckBtn = Bounce(); 
Bounce okBtn = Bounce(); 
Bounce aufwaertsBtn = Bounce(); 



void setup()
{
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  Serial.begin(9600);
  digitalWrite(13,LOW);
  delay(1000);
  digitalWrite(13,HIGH);

  weiterBtn.attach(weiterBtnPin);
  weiterBtn.interval(5);

  zurueckBtn.attach(zurueckBtnPin);
  zurueckBtn.interval(5);

  okBtn.attach(okBtnPin);
  okBtn.interval(5);

  aufwaertsBtn.attach(aufwaertsBtnPin);
  aufwaertsBtn.interval(5);
}

void loop()
{
  Serial.println(showMenu(eintraege));
}

int groesseArray(char* array[])
{
  int y = 0;
  while (*(array[y]) != 0)
  {
    y++;
  }
  return y;
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

char* eingabe()
{
  
}

int showMenu(char* entries[])
{
  schreibeZeile1(entries[0]);
  boolean endeSchleife = false;
  int rueckgabe;
  
  while (endeSchleife == false)
  {
    schreibeZeile2(entries[i]);

    while(weiterBtn.update() == 0 && zurueckBtn.update() == 0 && okBtn.update() == 0 && aufwaertsBtn.update() == 0);

    if(weiterBtn.read() == 1)
    {
      i++;
      if (*(entries[i]) == 0)
      {
        i = 1;
      }
    }

    if (zurueckBtn.read() == 1)
    {
      i--;
      if (i == 0)
      {
        i = groesseArray(entries) - 1;
      }
    }

    if (okBtn.read() == 1)
    {
      //schreibeZeile1(entries[i]);
      endeSchleife = true;
    }
  }
  lcd.clear();
  return i;
}

