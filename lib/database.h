struct DBEntry {
  int id;
  char *pw;
  char *service;
  char *username;
}

char **db_listTitles();
char db_newPW(char *, char *, char *);
void db_editPW(int id, char *);
void db_editMPW(char *newMPW);
struct DBEntry db_getEntry(int id);

/*
 * STORAGE FORMAT ON SD
 * 
 * 
 * 
 * 
 */