
#include <LiquidCrystal.h>  //http://engineeringlearning.blogspot.de/2013/10/interfacing-lcd-without-potentiometer.html
char ch;
int Contrast=15;

int buttonPin = 7;
int rueckgabe;
	int i = 1;
char* eintraege[] = {"Menue", "Passwort-Auswahl", "AFA", "MPasswort ändern", "Kiwi"};
char* test[0];

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  pinMode(13,OUTPUT);
  
  pinMode(buttonPin, INPUT); //Button
  
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
//  Serial.begin(9600);
  
   digitalWrite(13,LOW);
   delay(1000);
   digitalWrite(13,HIGH);
}

void loop() 
{
   
   test[1] = (char *)showMenu(eintraege)+48;
   delay(2000);
   schreibeZeile1((char *)test);
   delay(2000);
}

int prellfreiesDruecken(int pinBtn)
{
  if (digitalRead(pinBtn) == true)
  {
    int c = 0;
    
    while (c<30)   
    {
      while(digitalRead(pinBtn) == true)
      {     
        delay(1);
        c++;
      }
    }
    
    return c;
  }
  
  return 0;
}


/* int druck(int pinBtn)
{
  
  //Serial.println("DruckKurz aufgerufen");
  
  if (digitalRead(pinBtn)==false)
  {
    return 1;
  }
  if (digitalRead(pinBtn)==true)
  {
    delay(700);
    if (digitalRead(pinBtn) == false)
    {
      //Serial.println("kurzer Druck");
      return 2;
    }
    else
    {
      return 3;
    }
  }
}
*/

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

int showMenu(char* entries[])
{
	
        schreibeZeile1(entries[0]);

        boolean endeSchleife = false;
        
	while (endeSchleife == false)
	{
		schreibeZeile2(entries[i]);
                while(digitalRead(buttonPin) == false) 
                { } ;
                
                if (prellfreiesDruecken(buttonPin) < 1000)
                {
                  i++ ;
                  delay (400);
                }
                else if (prellfreiesDruecken(buttonPin) > 1000)
                {
                  rueckgabe = i;
                  endeSchleife = true;
                }
                
                if (*(entries[i]) != 0)
                {
                  i = 1;
                }
	}

        lcd.clear();
        
        return rueckgabe;
}



