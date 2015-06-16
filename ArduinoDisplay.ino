#include <Bounce2.h>
#include <LiquidCrystal.h> //http://engineeringlearning.blogspot.de/2013/10/interfacing-lcd-without-potentiometer.html

#define rightBtnPin 7
#define leftBtnPin 10
#define okBtnPin 8
#define backBtnPin 9

char ch;
int Contrast = 15;
char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
char* mainMenu[] = { "Menue", "Passwort-Auswahl", "AFA", "MPasswort aendern", "Kiwi", "" };
// inits
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


Bounce rightBtn = Bounce();
Bounce leftBtn = Bounce();
Bounce okBtn = Bounce();
Bounce backBtn = Bounce();

void setup()
{
	analogWrite(6, Contrast);
	lcd.begin(16, 2);
	Serial.begin(9600);
	digitalWrite(13, LOW);
	delay(1000);
	digitalWrite(13, HIGH);

	rightBtn.attach(rightBtnPin);
	rightBtn.interval(5);

	leftBtn.attach(leftBtnPin);
	leftBtn.interval(5);                //da falsch verkabelt

	okBtn.attach(okBtnPin);
	okBtn.interval(5);

	backBtn.attach(backBtnPin);
	backBtn.interval(5);
}

void loop()
{
	if (showMenu(mainMenu) == 2)
	{
		input("HalloWelt", alphabet, 15);
	}
}

int sizeArray(char array[])
{
	return sizeof(array) / sizeof(char);
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

void writeLine1(char content[], int pos)
{
	lcd.setCursor(pos, 0);
	lcd.print(content);
}

void writeLine2(char content[])
{
	lcd.setCursor(0, 1);
	lcd.print("                ");
	lcd.setCursor(0, 1);
	lcd.print(content);
}

void writeLine2(char content[], int pos)
{
//
  if(content[0]!='\0'){
//
	lcd.setCursor(pos, 1);
	lcd.print(content);

//
  }
//

}

//---------------------------------------------------------------




boolean xSecSwitch(Bounce btn, int howLong)
{
	unsigned long timer = millis();
	while (btn.read());
	timer = millis() - timer;

	return(timer >= howLong * 1000);
}

char* input(char* headline, char* alphabet, int inputLength)  //inputLength > 7
{
	char buffer[inputLength];
	char scroll[8] = "";
	char output[8] = "";
	int pos = 0;
	int i = 0;
	int alphabetLength = 62;           //sizeArray(alphabet);
	int start = 0;

	Serial.println("laenge Alpha. :" + alphabetLength);

	writeLine1(headline);

	while (i < inputLength)
	{
		// Auswahlstrich zeichnen
                lcd.setCursor(12,1);
                lcd.cursor();
                // letzte 7 Zeichen des Pwd in output array
                start = i - 7;
                if (start<0) start = 0;
		for (int y = 0; y<7; y++)
		{
                  output[y] = buffer[start + y];      //leer machen
		}
		output[7] = '\0';
                // 7 zeichen aus dem alphabet anzeigen
                for(int y=-3; y<=3; y++)
                {
                  int h = pos + y;
                  if(h<0)
                  {
                    h = alphabetLength + h;
                  } 
                  else if(h>=alphabetLength)
                  {
                    h = h-alphabetLength;
                  }
                  scroll[y+3] = alphabet[h];
                }
                scroll[7] = '\0';
                // ausgabe auf lcd
                writeLine2(output, 0);
		writeLine2("||", 7);
                writeLine2(scroll, 9);
                
                lcd.setCursor(12,1);
                
                // knöpfe gedöns
		while (rightBtn.update() == 0 && leftBtn.update() == 0 && okBtn.update() == 0 && backBtn.update() == 0);

		if (rightBtn.read() == 1)
		{
			pos++;
		}

		if (leftBtn.read() == 1)
		{
			pos--;
		}

		if (pos < 0)
		{
			pos = (alphabetLength-1) - abs(pos);
		} 
                else if (pos >= alphabetLength)
		{
			pos = pos - alphabetLength;
		}
                
                if(okBtn.read() == 1)
                {
                  buffer[i] = alphabet[pos];
                  i++;
                }
		//--------------

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

		while (rightBtn.update() == 0 && leftBtn.update() == 0 && okBtn.update() == 0 && backBtn.update() == 0);

		if (rightBtn.read() == 1)
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
