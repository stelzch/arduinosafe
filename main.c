
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
}

typedef STATE (*StateFunction)(void);

struct Context {
  int selected_pw;
  int last_interaction;
  /*
   * TODO: Reference Password Database
   */
  
}

STATE callState(STATE);


int main() {
  while(1) {
   
  }
  
}
STATE callState(STATE s) {
  
}