#include <stdio.h>
char nutzlos[] = "";
char tempRueckgabe[] = "";
   FILE *pwd;
  int tl=30;
  char pwchiffred[30+1];
  char pwcleartext[30+1];


//immer erst Acc Name, Passwort, Username
//char* usernames[] = {"robert.robertorobertonet.robert", "ichbin.keine@spam.de", "Robertosondeespaiono@gockelmail.com", "Fruchtig, Saftik, plüschick", ""};
//char* passwoerter[] = {"klautnichtmeineDateeen", "PIN:3416", "0000", "Vogelsang", ""};
//char* konto[] = {"Facebook", "Amazon", "GooglePLUS", "Kiwi", ""};

char masterPW[] = "1";




/*
int hauptmenu();
int obstMenu();
int MusikMenu();
int SportMenu();
int SSSMenu();
*/
/*
typedef  void (*zfp)(void);
 zfp hm=&hauptmenu;
 zfp om=&obstMenu;
 zfp mm=&MusikMenu;
 zfp sm=&SportMenu;
 zfp sssm=&SSSMenu;
*/
/*
 int (*hm)()=&hauptmenu;
 int (*om)()=&obstMenu;
 int (*mm)()=&MusikMenu;
 int (*sm)()=&SportMenu;
 int (*sssm)()=&SSSMenu;
*/

void ausgabe(char zeile1[], char zeile2[])
{
	printf("%s",zeile1);
	printf("\n");
	printf("%s",zeile2);
}

void eingabe()
{
	fgets(tempRueckgabe, 50, stdin);
}

int showMenu(char* entries[])
{
	printf("%s\n", entries[0]);
	int i = 1;
	while ( *(entries[i]) != 0)
	{
		printf("%d. %s", i, entries[i]);
		printf("\n");
		i++;
	}
	i--;
	printf("%s","Your choice: ");

	int choice;
	scanf("%d", &choice);
	if ((choice < 1) || (choice > i))
	{
		choice = 0;
	}
	return choice;
}

void showMenuOhneEingabe(char* entries[])
{
	printf("%s\n", entries[0]);
	int i = 1;
	while ( *(entries[i]) != 0)
	{
		printf("%d. %s", i, entries[i]);
		printf("\n");
		i++;
	}
}

void clearScreen()
{
	system("clear");
}

//--------------------------------
int MasterPWEingabe()
{
	char* PasswortMenu[] = { "Gib das MasterPasswort ein!", "" };
	showMenuOhneEingabe(PasswortMenu);
	//tempRueckgabe = "";
	eingabe();
	if(strcmp(tempRueckgabe, masterPW))
	{
	    return 0;
	}
	else {
	    return 1;
	}
}

int hauptmenu(){
	clearScreen();
	char* SSSMenu[] = { "Hauptmenue", "Passwort-Auswahl", "Neues Konto", "Masterpasswort ändern", "Konto bearbeiten", "Prüfwort einstellen","Kiwi", "" };
	
	return (showMenu(SSSMenu)+1);
	}
/*	
int pwdAuswahl()
{
	clearScreen();
} */

int aufrufen(int auswahl){
	
	switch (auswahl)
	{
	case 0:
		return kc(); //4fkingdebugging
		//return hauptmenu();
		break;
	case 1:
		return MasterPWEingabe();
		break;
	/* case 2:
		return pwdAuswahl();
		break; */
	case 3:
		return kc(); 
		break;
	}
}
 //einlesen des pws
int readpwchiffred(){

  pwd = fopen ("Nutzlos", "r");
  if (pwd != NULL){
    fscanf (pwd, "%1000c", pwchiffred);
    pwchiffred[1000] = '\0';
    printf ("%s\n", pwchiffred);
    fclose(pwd);
  }
  
}
//neues pw mit acc erstellen
int kc(){
   pwd=fopen("Nutzlos","W"); 
  if (pwd != NULL){
  char s[100];
  char u[100];
  char pw[100];
  int x;
  ausgabe("Service","");
  eingabe();
  fprintf(pwd,"\n%s",tempRueckgabe);
  /*
  while(x != 49){
  s[x] = tempRueckgabe[x];
  x++;
  }*/
  
  ausgabe("Username","");
  eingabe();
  fprintf(pwd,"\n%s",tempRueckgabe);
  
  ausgabe("Password","");
  eingabe();
  fprintf(pwd,"\n%s",tempRueckgabe);
  
  // readpwchiffred();

   
  }else{
    printf("Fehler beim Datein einlesen");
  }
}
/* 
int unchiffer(char* catounchiffre[], char* destca){
int i;
int useless;
for(i=0; i < sizeof catounchiffre; ++i)  
 useless=ascii[catounchiffre[i]+4];	
sprintf(destca,"%c",useless);
}
*/

int main(){
  readpwchiffred();
 
//
//unchiffer(pwchiffred,pwcleartext);

int i=0;
int useless;
//for(i=0; i < sizeof pwchiffred; ++i){ 

/*  while(i < sizeof pwchiffred){
    
 useless=pwchiffred[i]-4;
 pwcleartext[i]= useless;
 i++;
} */

printf("%s\n", pwcleartext);
int naechster = aufrufen(0); //zum debugging o statt 1
while (naechster != 10)
	{
		naechster = aufrufen(naechster);
	}
	return 0;
}

