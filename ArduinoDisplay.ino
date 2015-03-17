
#include <LiquidCrystal.h>  //http://engineeringlearning.blogspot.de/2013/10/interfacing-lcd-without-potentiometer.html
char ch;
int Contrast=15;

int buttonPin = 7;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  pinMode(13,OUTPUT);
  
  pinMode(buttonPin, INPUT); //Button
  
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  
   digitalWrite(13,LOW);
   delay(1000);
   digitalWrite(13,HIGH);
}

void loop() 
{
   
   char* eintraege[] = {"Menue", "Baskettball", "Kiwi", "AlleFischeBlubb"};
   showMenu(eintraege);
}

void schreibeZeile1(char content[])
{
  lcd.setCursor(0, 1);
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

void showMenu(char* entries[])
{
	schreibeZeile1(entries[0]);
	int i = 1;
	while (*(entries[i]) != 0)
	{
		schreibeZeile2(entries[i]);
                if(digitalRead(buttonPin) == true)
                {
                  i++;
                  delay(1000);
                }
	}

        lcd.clear();
}



