
#include <stdio.h>
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

char *userinput(char* headline, int inputLength) {
  char *text;
  scanf("%s",text);
}
int showMenu(char title[], char *entries[]) {
  return 0;
}
void keyboard_send(char text[]) {
  printf("%s\n", text);
}
void display(char text[]) {
  printf("%s\n", text);
}
char** db_listTitles() {
  // TODO: IDs
  char* titleList[] = {"facebook user", "google user", "mac user"};
  return titleList;
}
void db_newPW(char* newServiceName, char* newUsername, char* newPW){

}

db_editPW(int id, char* newPW) {

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

/*   MAIN         */
int main() {
  int nextState = ENTER_MASTER_PASSWORD;
  while(1) {
   nextState = callState(nextState);
  }
  
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
  if (strcmp(mpw, actual_mpw) == 0) {
    return MAIN_MENU; 
  }
  return ENTER_MASTER_PASSWORD;
}
int mainMenu() {
  printf("MAIN_MENU\n");
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
  char title[] = "PW Auswahl";
  int ret = showMenu(title, db_listTitles());
  if (ret < 0) {
    return MAIN_MENU;
  }
  ctx.selected_pw = ret;
  return DISPLAY_PW;
}
int displayPW() {
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
  case 0: keyboard_send(entry.pw);
  case 1: keyboard_send(entry.username);
  case 2: display(entry.pw);
  case 3: return EDIT_PW;
  }
  return DISPLAY_PW;
}
int newPW(){
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
  case 0: newPW = generatePW();
  case 1: newPW = enterPW();
  }
  db_newPW(newServiceName, newUsername, newPW);
  return MAIN_MENU;
}
int editPW(){
  char headline[] = "Eingabetyp waehlen";
  char* editPWEntries[] = {"PW generieren", 
			   "PW eingeben"};
  int ret = showMenu(headline, editPWEntries);
  if (ret < 0) {
    return DISPLAY_PW;
  }
  char* newPW;
  switch (ret){
  case 0: newPW = generatePW();
  case 1: newPW = enterPW();
  }
  db_editPW(ctx.selected_pw, newPW);
  return DISPLAY_PW;
}
int editMPW(){}


char* enterPW(){}
char* generatePW(){}



