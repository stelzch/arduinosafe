#include <Bounce2.h>
#include <LiquidCrystal.h> //http://engineeringlearning.blogspot.de/2013/10/interfacing-lcd-without-potentiometer.html

#define rightBtnPin 7
#define leftBtnPin 10
#define okBtnPin 8
#define backBtnPin 9

char ch;
int Contrast=15;
char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
char* mainMenu[] = {"Menue", "Passwort-Auswahl", "AFA", "MPasswort aendern", "Kiwi", ""};
// inits
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


Bounce rightBtn = Bounce(); 
Bounce leftBtn = Bounce(); 
Bounce okBtn = Bounce(); 
Bounce backBtn = Bounce(); 

void setup()
{
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  Serial.begin(9600);
  digitalWrite(13,LOW);
  delay(1000);
  digitalWrite(13,HIGH);

  rightBtn.attach(rightBtnPin);
  rightBtn.interval(5);

  leftBtn.attach(leftBtnPin);
  leftBtn.interval(5);

  okBtn.attach(okBtnPin);
  okBtn.interval(5);

  backBtn.attach(backBtnPin);
  backBtn.interval(5);
}

void loop()
{
  Serial.println(showMenu(mainMenu));
}

int sizeArray(char array[])
{
  return sizeof(array)/sizeof(char);
}

int sizeArray(char* array[])
{
  int y = 0;
  while (*(array[y]) != 0)
  {
    y++;
  }
  return y;
}

void writeLine1(char content[])
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(content);
}

void writeLine2(char content[])
{
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(content);
}

//---------------------------------------------------------------




boolean xSecSwitch(Bounce btn, int howLong)
{
  unsigned long timer = millis();
  while(btn.read());
  timer = millis() - timer;
  
  return(timer >= howLong*1000);
}

char* input(char* headline, char* alphabet, int inputLenght)  //inputLengh > 7
{
  char buffer[inputLenght];
  char output[7];
  int i = 0;
  int p = 0;
  int alphabetLenght = sizeArray(alphabet);
  int start = 0;
  
  writeLine1(headline);
  
  while(i < inputLenght)
  {
    //--------------Ausgabe letzter 7 Ziffern
    start = i - 7;
    if (i < 0) start = 0;
    
    for (int y = 0; y<7; y++)
    {
      output[y] = buffer[start + y];      
    }  
    
    //--------------Scrolling
    
    //Note: negativer Modulo?!!!!!!!!!!!!!!
    
  }
}

//---------------------------------------------------------------

int showMenu(char* entries[])
{
  writeLine1(entries[0]);
  boolean endLoop = false;
  int rueckgabe;
  int i = 1;
  
  while (endLoop == false)
  {
    writeLine2(entries[i]);

    while(rightBtn.update() == 0 && leftBtn.update() == 0 && okBtn.update() == 0 && backBtn.update() == 0);

    if(rightBtn.read() == 1)
    {
      i++;
      if (*(entries[i]) == 0)
      {
        i = 1;
      }
    }

    if (leftBtn.read() == 1)
    {
      i--;
      if (i == 0)
      {
        i = sizeArray(entries) - 1;
      }
    }

    if (okBtn.read() == 1)
    {
      //writeLine1(entries[i]);
      endLoop = true;
    }
  }
  lcd.clear();
  return i;
}
