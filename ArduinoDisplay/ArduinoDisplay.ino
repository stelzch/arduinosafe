#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   8  // Data/command line for TFT
#define TFT_RST  -1  // Reset line for TFT (or connect to +5V)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_ST7735 tftHL = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_RIGHT 2
#define BUTTON_SELECT 3
#define BUTTON_UP 4
#define BUTTON_LEFT 5

const int LINE_HIGH = 8;
const int X_START_POSOTION = 25;
const int Y_START_POSOTION = 0;

char ch;
char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
char* mainMenu[] = { "Menue", "Passwort-Auswahl", "AFA", "MPasswort aendern", "Kiwi", "" };
char* mainMenu2[] = { "hallo", "ghfhia-Auswahl", "test", "test2", "ananas", "" };
// inits

void setup()
{
	Serial.begin(9600);
	digitalWrite(13, LOW);
	digitalWrite(13, HIGH);
        // Initialize 1.8" TFT
        tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
        Serial.println("OK!");
        tft.fillScreen(ST7735_BLACK);
        tft.setRotation(1);
        
                // Initialize 1.8" TFT
        tftHL.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
        Serial.println("OK!");
        tftHL.fillScreen(ST7735_BLACK);
        tftHL.setRotation(1);
        
}

uint8_t readButton(void) {
  float a = analogRead(3);
  
  a *= 5.0;
  a /= 1024.0;
  
  if (a < 0.2) return BUTTON_RIGHT;
  if (a < 1.0) return BUTTON_UP;
  if (a < 1.5) return BUTTON_SELECT;
  if (a < 2.0) return BUTTON_LEFT;
  if (a < 3.2) return BUTTON_DOWN;
  else return BUTTON_NONE;
}

int i = 0;
void loop(){
   if (showMenu(mainMenu) == 3) {
     showMenu(mainMenu2);
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

void highlightRaw (int n) { //n = 1 erste Zeile     n = 0 nichts markiert
    tftHL.fillScreen(ST7735_BLACK);
    tftHL.setCursor(0, Y_START_POSOTION + (n-1)*LINE_HIGH);
    tftHL.print("->");
}
void writeList(char* content[]) {
   int arraySize = sizeArray(content);
   for (int i = 0; i < arraySize; i++) {
     tft.setCursor(X_START_POSOTION, Y_START_POSOTION + i*LINE_HIGH);
     tft.print(content[i]);
   }
}
//---------------------------------------------------------------


//char* input(char* headline, char* alphabet, int inputLength)  //inputLength > 7
//{
//        tft.fillScreen(ST7735_BLACK);
//	char buffer[inputLength];
//	char scroll[8] = "";
//	char output[8] = "       ";
//        int letter_pos = 0;
//	int pos = 0;
//	int i = 0;
//	int p; //Hilfsvar
//	int alphabetLength = 62;           //sizeArray(alphabet);
//	int start = 0;
//
//	Serial.println("laenge Alpha. :" + alphabetLength);
//
//	
//        writeLine1(headline);
//        writeLine2(scroll, 9);
//	writeLine2("||", 7);
//        for (int i = 0; i < inputLength; i++){
//          buffer[i] = ' ';
//        }
//	while (i < inputLength)
//	{
//		//--------------Ausgabe letzter 7 Ziffern
//		start = i - 7;
//		if (i < 0) start = 0;
//		
//		int z = 6;
//
//		for (int y = 0; y<7; y++)
//		{
//			output[y] = buffer[start + y];      //leer machen
//		}
//		output[7] = '\0';
//
//		//--------------Scrolling
//
//		
//
//		//for (int y = 3; y >= 0; y--)
//		//{
//		//	if (pos - y < 0)
//		//	{
//		//		p = alphabetLength - y;
//		//	}
//		//	else{
//		//		p = pos - y;
//		//	}
//
//		//	scroll[z] = alphabet[p];
//		//	z++;
//		//}
//
//		//scroll[7] = '\0';
//
//		//for (int y = 1; y <= 3; y++)
//		//{
//		//	if (pos + y > alphabetLength - 1)
//		//	{
//		//		p = (pos + y) - alphabetLength;
//		//	}
//		//	else{
//		//		p = pos + y;
//		//	}
//
//		//	scroll[z] = alphabet[p];
//		//	z++;
//		//}
//
//		for (int y = -3; y <= 3; y++)
//		{
//			if (pos - y < 0)
//			{
//				p = alphabetLength - y;
//			}
//			else if (pos-y > alphabetLength - 1)
//			{
//				p = (pos - y) - alphabetLength;
//			}
//			else 
//			{
//				p = pos - y;
//			}
//
//			scroll[z] = alphabet[p];
//			z--;
//		}
//
//
//		scroll[7] = '\0';
//
//		//   Serial.println(scroll + '|' + pos);
//
//		//--------------
//                
//                uint8_t b;
//                b = readButton();
//                if (b == BUTTON_DOWN) {
//			pos++;
//                        delay(500);
//                }
//                if (b == BUTTON_LEFT) {
//                }
//                if (b == BUTTON_UP) {
//			pos--;
//                        delay(500);
//                }
//                if (b == BUTTON_RIGHT) {
//                }
//
//		if (pos < 0)
//		{
//			pos = alphabetLength - abs(pos);
//		}
//		if (pos > alphabetLength - 1)
//		{
//			pos = pos - alphabetLength;
//		}
//                if (b == BUTTON_SELECT) {
//                        buffer[letter_pos] = alphabet[pos];
//                        letter_pos++;
//                }                
//                if (b != BUTTON_NONE) {
//                   tft.fillScreen(ST7735_BLACK);
//                   writeLine1(headline);
//                   writeLine2(scroll, 9);
//		   writeLine2("||", 7);
//                   writeLine2(output);
//                   Serial.println(output);
//                   delay(200);
//                }
//		//--------------
//
//	}
//}

//---------------------------------------------------------------

int showMenu(char* entries[])
{
	boolean endLoop = false;
	int rueckgabe;
	int i = 1;
        highlightRaw(i);
        writeList(entries);
        

	while (endLoop == false)
	{
                uint8_t b;
		b = readButton();

                if (b == BUTTON_DOWN) {
			i++;
			if (sizeArray(entries) < i)
			{
				i = 1;
                            
			}
                                highlightRaw(i);
                                writeList(entries);
                }
                if (b == BUTTON_LEFT) {
                }
                if (b == BUTTON_UP) {
			i--;
			if (i == 0)
			{
				i = sizeArray(entries);
                             
			}
                                 highlightRaw(i);
                                writeList(entries);
                }
                if (b == BUTTON_RIGHT) {
                }

		if (b == BUTTON_SELECT)
		{
			endLoop = true;
		}
                if (b != BUTTON_NONE) {
                  delay(500);
                }
                Serial.println("A");
	}
	return i;
}
