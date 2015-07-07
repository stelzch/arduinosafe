#include <Bounce2.h>
#include <LiquidCrystal.h> //http://engineeringlearning.blogspot.de/2013/10/interfacing-lcd-without-potentiometer.html

#define rightBtnPin 7
#define leftBtnPin 10
#define okBtnPin 8
#define backBtnPin 9

char ch;
int Contrast = 15;
// inits
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


Bounce rightBtn = Bounce();
Bounce leftBtn = Bounce();
Bounce okBtn = Bounce();
Bounce backBtn = Bounce();



/* DEBUG */
struct DBEntry {
  int id;
  char *pw;
  char *username;
  char *service;
};
char EEPROM_read(int pos) {
  char *mpw = "Masterpasswort";
  return mpw[pos];
}
char* userinput(char* headline, int inputLength)  //inputLength > 7
{
        char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	char buffer[inputLength + 1];
        buffer[inputLength] = '\0';
	char scroll[8] = "";
	char output[8] = "";
	int pos = 0;
	int i = 0;
	int alphabetLength = 62;           //sizeArray(alphabet);
	int start = 0;
        
        for(int z = 0; z < inputLength; z++)
        {
          buffer[z] = ' ';
        }
        
        
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
                  int millisek = millis();
                  while(okBtn.update() == 0) { };
                  int time = (millis() - millisek)/1000;           //Zeit des Knopfdrückens in sek
                  
                  if(time < 2)
                  {
                    buffer[i] = alphabet[pos];
                    i++;
                  } else {
                    
                    char pwd[i];
                    for(int y = 0; y < i; y++)
                    {
                       pwd[y] = buffer[y];
                    }
                    pwd[i] = '\0';
                    
                    return pwd;
                  }
                }
                
                
                if(okBtn.read() == 1)
                {
                  buffer[i] = alphabet[pos];
                  i++;
                }
                
                if(backBtn.read() == 1)            //1 Zeichen löschen
                {
                  buffer[i-1] = ' ';
                  i--; 
                }
		//--------------
	}
    
    char pwd[i];
    for(int y = 0; y < i; y++)
    {
      pwd[y] = buffer[y];
    }
    pwd[i] = '\0';    
    Serial.print("S: ");
    Serial.println(pwd);
    return pwd;
}

//---------------------------------------------------------------

int showMenu(char title[], char* entries[])
{
	writeLine1(title);
	boolean endLoop = false;
	int rueckgabe;
	int i = 0;

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
void keyboard_send(char text[]) {
  Serial.println(text);
}
void display(char text[]) {
  Serial.println(text);
}
char** db_listTitles() {
  // TODO: IDs
  char* titleList[] = {"facebook user", "google user", "mac user"};
  return titleList;
}
void db_newPW(char* newServiceName, char* newUsername, char* newPW){

}
void db_editPW(int id, char* newPW) {

}
void db_editMPW(char* newMPW) {

}

struct DBEntry db_getEntry(int id) {
  struct DBEntry entry;
  entry.id = id;
  entry.pw = "password";
  entry.username = "username";
  entry.service = "muster";
  return entry;
}

/*   PROTOTYPES   */
int callState(int);
int enterMasterPassword();
int mainMenu();
int selectPW();
int displayPW();
int newPW();
int editPW();
int editMPW();

char* enterPW();
char* generatePW();

const int MAX_MPW_LENGTH = 31;

enum STATE {
  ENTER_MASTER_PASSWORD,
  MAIN_MENU,
  SELECT_PW,
  DISPLAY_PW,
  NEW_PW,
  EDIT_PW,
  EDIT_MPW
};

typedef int (*StateFunction)(void) ;
StateFunction stateArray[] = {
  &enterMasterPassword,
  &mainMenu,
  &selectPW,
  &displayPW,
  &newPW,
  &editPW,
  &editMPW
};

struct Context {
  int selected_pw;
  int last_interaction;
  /*
   * TODO: Reference Password Database, User Interface
   */
  
} ctx;
int nextState = ENTER_MASTER_PASSWORD;


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

/*   MAIN         */
void loop() { 
  while(1) {
   nextState = callState(nextState);
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

int callState(int s) {
  return stateArray[s]();
}
/*   STATE FUNCTIONS */
int enterMasterPassword() {
  char *headline = "MPW eingeben";
  char *mpw = userinput(headline, 64);
  char actual_mpw[MAX_MPW_LENGTH];
  char tmp;
  int pos = 0;
  while ((tmp = EEPROM_read(pos++)) != '\0') {
    actual_mpw[pos] = tmp;
  }
  actual_mpw[pos] = '\0';
  Serial.print("Before compare\n");
  if (/*strncmp(mpw, actual_mpw, pos)*/0 == 0) { // TODO: fix strcmp
    return MAIN_MENU; 
  }
  Serial.print("After compare\n");
  return ENTER_MASTER_PASSWORD;
}
int mainMenu() {
  Serial.print("Main Menu\n");
  char title[] = "Hauptmenue";			     
  char *mainMenuEntries[] = {"PW-Auswahl",
			     "Neues PW",
			     "MPW aendern"};
  int ret = showMenu(title, mainMenuEntries);
  
  switch (ret) {
  case 0: return SELECT_PW;
  case 1: return NEW_PW;
  case 2: return EDIT_MPW;
  default: return MAIN_MENU;
  }
  
  return MAIN_MENU;
}
int selectPW() {
  Serial.print("Select PW\n");
  char title[] = "PW Auswahl";
  int ret = showMenu(title, db_listTitles());
  if (ret < 0) {
    return MAIN_MENU;
  }
  ctx.selected_pw = ret;
  return DISPLAY_PW;
}
int displayPW() {
  Serial.print("Display PW\n");
  struct DBEntry entry = db_getEntry(ctx.selected_pw);
  char *title = entry.service;
  char *displayPWEntries[] = {"PW senden",
			      "Benutzername senden",
			      "PW anzeigen",
			      "PW aendern"};
  int ret = showMenu(title, displayPWEntries);
  if (ret < 0) {
    return SELECT_PW;
  }
  switch (ret) {
  case 0: keyboard_send(entry.pw);break;
  case 1: keyboard_send(entry.username);break;
  case 2: display(entry.pw);break;
  case 3: return EDIT_PW;
  }
  return DISPLAY_PW;
}
int newPW(){
  Serial.print("New PW\n");
  char title[] = "Neues PW";
  char* headline = "servicename";
  char* newServiceName = userinput(headline, 64);
  headline = "username";
  char* newUsername = userinput(headline, 64);
  headline = "Eingabetyp waehlen";
  char* PWNewEntries[] = {"PW generieren", 
			  "PW eingeben"};
  int ret = showMenu(headline, PWNewEntries);
  if (ret < 0){
    return DISPLAY_PW;
  }
  char* newPW;
  switch (ret){
  case 0: newPW = generatePW();break;
  case 1: newPW = enterPW();break;
  }
  db_newPW(newServiceName, newUsername, newPW);
  return MAIN_MENU;
}
int editPW(){
  Serial.print("Edit PW\n");
  char headline[] = "Eingabetyp waehlen";
  char* editPWEntries[] = {"PW generieren", 
			   "PW eingeben"};
  int ret = showMenu(headline, editPWEntries);
  if (ret < 0) {
    return DISPLAY_PW;
  }
  char* newPW;
  switch (ret){
  case 0: newPW = generatePW();break;
  case 1: newPW = enterPW();break;
  }
  db_editPW(ctx.selected_pw, newPW);
  return DISPLAY_PW;
}
int editMPW(){
  Serial.print("Edit MPW\n");
  char* newMPW;
  newMPW = enterPW();
  db_editMPW(newMPW);
  return MAIN_MENU;
}


char* enterPW(){
  Serial.print("Enter PW\n");
  char headline[] = "Passwort eingeben";
  char* pw = userinput(headline, 64);
  return pw;
}
char* generatePW(){
  Serial.print("Generate PW\n");
  char pw[] = "123456789012345";
  return pw;
}
