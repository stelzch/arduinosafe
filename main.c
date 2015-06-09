#include <stdio.h>
/* DEBUG */
char EEPROM_read(int pos) {
  char *mpw = "Masterpasswort";
  return mpw[pos];
}
char *userinput() {
  char *text;
  scanf("%s",text);
}
/*   PROTOTYPES   */
int callState(int);
int enterMasterPassword();
int mainMenu();
int selectPW();
int displayPW();
int newPW();
int enterPW();
int generatePW();
int editPW();
int editMPW();

const int MAX_MPW_LENGTH = 31;

enum STATE {
  ENTER_MASTER_PASSWORD,
  MAIN_MENU,
  SELECT_PW,
  DISPLAY_PW,
  NEW_PW,
  ENTER_PW,
  GENERATE_PW,
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
  &enterPW,
  &generatePW,
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
  char *mpw = userinput();
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
  return ENTER_MASTER_PASSWORD;
}
/*
int selectPW() {}
int displayPW() {}
int newPW(){}
int enterPW(){}
int generatePW(){}
int editPW();
int editMPW(); */