#include <stdio.h>

char nutzlos[] = "";
char tempRueckgabe[] = "";


//immer erst Acc Name, Passwort, Username
char usernames[] = {"robert.robertorobertonet.robert", "ichbin.keine@spam.de", "Robertosondeespaiono@gockelmail.com", "Fruchtig, Saftik, plüschick", ""};
char passwoerter[] = {"klautnichtmeineDateeen", "PIN:3416", "0000", "Vogelsang", ""};
char konto[] = {"Facebook", "Amazon", "GooglePLUS", "Kiwi", ""};

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
	tempRueckgabe = "";
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
	
int pwdAuswahl()
{
	clearScreen();
	char* ausgabe[] = {"Usernames:"} + konto;
}

int aufrufen(int auswahl){
	
	switch (auswahl)
	{
	case 0:
		return hauptmenu();
		break;
	case 1:
		return MasterPWEingabe();
		break;
	case 2:
		return pwdAuswahl();
		break;
	}
}



int main(){
	int naechster = aufrufen(1);
	while (naechster != 10)
	{
		naechster = aufrufen(naechster);
	}
	return 0;
}

