#include <stdio.h>

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
  &mainMenu
};
struct Context {
  int selected_pw;
  int last_interaction;
  /*
   * TODO: Reference Password Database, User Interface
   */
  
};

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
  printf("ENTER_MASTER_PASSWORD\n");
  return MAIN_MENU;
}
int mainMenu() {
  printf("MAIN_MENU\n");
  return ENTER_MASTER_PASSWORD;
}