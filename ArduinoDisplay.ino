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
	leftBtn.interval(5);

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
	lcd.setCursor(pos, 1);
	lcd.print(content);
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
	int p; //Hilfsvar
	int alphabetLength = 62;           //sizeArray(alphabet);
	int start = 0;

	Serial.println("laenge Alpha. :" + alphabetLength);

	writeLine1(headline);

	while (i < inputLength)
	{
		//--------------Ausgabe letzter 7 Ziffern
		start = i - 7;
		if (i < 0) start = 0;
		
		int z = 6;

		for (int y = 0; y<7; y++)
		{
			output[y] = buffer[start + y];      //leer machen
		}
		output[7] = '\0';

		//--------------Scrolling

		

		//for (int y = 3; y >= 0; y--)
		//{
		//	if (pos - y < 0)
		//	{
		//		p = alphabetLength - y;
		//	}
		//	else{
		//		p = pos - y;
		//	}

		//	scroll[z] = alphabet[p];
		//	z++;
		//}

		//scroll[7] = '\0';

		//for (int y = 1; y <= 3; y++)
		//{
		//	if (pos + y > alphabetLength - 1)
		//	{
		//		p = (pos + y) - alphabetLength;
		//	}
		//	else{
		//		p = pos + y;
		//	}

		//	scroll[z] = alphabet[p];
		//	z++;
		//}

		for (int y = -3; y <= 3; y++)
		{
			if (pos - y < 0)
			{
				p = alphabetLength - y;
			}
			else if (pos-y > alphabetLength - 1)
			{
				p = (pos - y) - alphabetLength;
			}
			else 
			{
				p = pos - y;
			}

			scroll[z] = alphabet[p];
			z--;
		}


		scroll[7] = '\0';
		writeLine2(scroll, 9);
		writeLine2("||", 7);

		//   Serial.println(scroll + '|' + pos);

		//--------------

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
			pos = alphabetLength - abs(pos);
		}
		if (pos > alphabetLength - 1)
		{
			pos = pos - alphabetLength;
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
