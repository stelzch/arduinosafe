#include <SD.h>
#define SD_CS 4
#define MAX_ENTRIES 3
#define MAX_TITLE_LENGTH 30
#define MAX_PW_LENGTH 30
#define MAX_SERVICE_LENGTH 15
#define MAX_USERNAME_LENGTH 15
#define MAX_FILENAME_LENGTH 3
/* ========================GLOBAL VARS & STRUCTS ================== */
struct DBEntry {
  int id;
  char pw[MAX_PW_LENGTH];
  char service[MAX_SERVICE_LENGTH];
  char username[MAX_USERNAME_LENGTH];
};
/* ========================= PROTOTYPES =========================== */
void db_setup();

void db_editMPW(char *newMPW);
struct DBEntry db_getEntry(int id);
File root;


void setup() {
  delay(3000);
  Serial.begin(9600);
  db_setup();
  Serial.println("Writing file...");
  struct DBEntry e = { 143, "testPW2", "Github", "fooUser" };
  db_newPW(e);
  Serial.println("Finished!");
}

void db_setup() {
  if( !SD.begin(SD_CS) ) {
    Serial.println("Initializing SD Card failed :(");
    return;
  }
  Serial.println("SD Card Initialized");
  // Make subdir if not it doesn't exist already
  if(SD.exists("/pwdsafe") ) {
    SD.mkdir("/pwdsafe");
  }
  root = SD.open("/pwdsafe"); 
    
}
void db_listTitles(char destination[MAX_ENTRIES][MAX_TITLE_LENGTH]) {
    int counter = 0;
    File file;
    while(true) {
      file = root.openNextFile();
//      Serial.print("Processing file "); Serial.println(file.name());
      if(!file) {
//        Serial.println("Last file");
        break;
      }
//      Serial.println(counter); 
      
      char c;
      int i = 0;
      do {
        
        c = file.read();
//        Serial.print(c);
        destination[counter][i] = c;
        i++;
      } while(c != 10);
      counter++;
    }
    root.rewindDirectory();
}
struct DBEntry db_getEntry(int id) {
  struct DBEntry entry;
  entry.id = id;
  String fileName = "/pwdsafe/";
  fileName += id;
  char filename[9+MAX_FILENAME_LENGTH];
  fileName.toCharArray(filename, 9+MAX_FILENAME_LENGTH);
  File file = SD.open(filename);
  Serial.print("Processing file ");Serial.println(file.name());
  // ===========READ USERNAME==================
  int counter = 0;
  char c;
  do {
    c = file.read();
    entry.username[counter] = c;
    counter ++;
  } while((c != 10) && (counter < MAX_USERNAME_LENGTH));
  
  // ===========READ SERVICE==================
  counter = 0;
  do {
    c = file.read();
    entry.service[counter] = c;
    counter ++;
  } while((c != 10) && (counter < MAX_SERVICE_LENGTH));
  // ===========READ PASSWORD==================
  counter = 0;
  do {
    c = file.read();
    entry.pw[counter] = c;
    counter ++;
  } while((c != -1) && (counter < MAX_PW_LENGTH));
  
  return entry;
}
/**
* Warning: the id given in the DBEntry struct doesn't matter
*
*/
char db_newPW(struct DBEntry entry) {
  int lastFile = 0;
  while(true) {
    File f = root.openNextFile();
    
    if(!f) {
      break;
    } else {
      lastFile++;
    }
  }
  
  entry.id = lastFile + 1;
  String fileName = "/pwdsafe/";
  fileName += entry.id;
  Serial.print("Writing to: ");Serial.println(fileName);
  char filename[9+MAX_FILENAME_LENGTH];
  fileName.toCharArray(filename, 9+MAX_FILENAME_LENGTH);
  File file = SD.open(filename, FILE_WRITE);
  
  file.println(entry.username);
  file.println(entry.service);
  file.println(entry.pw);
  
  file.flush();
  file.close();
  root.rewindDirectory();
} 
void loop() {
  delay(5000);
  

  
}
