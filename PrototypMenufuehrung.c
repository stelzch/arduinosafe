#include <stdio.h>

char nutzlos[] = "";
char tempRueckgabe[] = "";


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

/*
 * So könnte das aussehen, dass die Implementierungen der hardwareabhängigen
 * Programmteile in verschiedene Dateien ausgelagert werden:
 * 
#ifdef ARDUINO
#include ui-arduino.c
#else
#include ui-konsole.c
#endif

* Noch besser wäre möglicherweise, das erst den Linker entscheiden zu lassen.
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

void clearScreen()
{
	system("cls");
}

//--------------------------------
int hauptmenu()
{
	char* dasHauptMenu[] = { "Wo willst du hin?", "Obstmenu", "Musikmenu", "Sportmenu","SSSMenu", "" };
	int auswahl = showMenu(dasHauptMenu);
	return auswahl;
}

int obstMenu(){
	char* dasMenuHeute[] = { "Was willst du essen?", "Apfel", "Birne", "Banane", "Mango", "Kiwi", "Zurueck", "" };
	int auswahl = showMenu(dasMenuHeute);
	ausgabe(dasMenuHeute[auswahl],"");
	return 0;
}



int MusikMenu(){
	char* dieMusikAuswahl[] = { "Was willst du hoeren?", "Musik", "Stille", "Nichts", "Zurueck", "Kiwi", ""};
	int auswahl = showMenu(dieMusikAuswahl);
	if (auswahl=5){
		printf("%s","Kiwi is keine Musik");
	}
	ausgabe(dieMusikAuswahl[auswahl], "");
	return 0;
}

int SportMenu(){
	clearScreen();
	char* SportAuswahl[] = { "Was willst du spielen", "Nichts", "Schach", "Hau den ..", "Zurueck", "Kiwi", "" };
	int auswahl = showMenu(SportAuswahl);
	if (auswahl == 5){
		printf("%s","Kiwi is ne geile Sportart")  ;
	}
	ausgabe(SportAuswahl[auswahl], "");
	return 0;
}

int SSSMenu(){
	clearScreen();
	char* SSSMenu[] = { "Aktion", "Passwoerter", "MasterPW", "aluxa", "AFK", "Kiwi", "" };
	int auswahl = showMenu(SSSMenu);
	if (auswahl == 5){
		printf("%s","Der Edeka is nur fuenf min entfernt");
	}
	ausgabe(SSSMenu[auswahl], "");
	return 0;
}

int aufrufen(int auswahl){
	
	switch (auswahl)
	{
	case 0:
		return hauptmenu();
		break;
	case 1:
		return obstMenu();
		break;
	case 3:
		return SportMenu();
		break;
	case 2:
		return MusikMenu();
		break;
	case 4:
		return SSSMenu();
		break;
	}
}


#ifdef ARDUINO

int naechster;
void setup() {
    naechster = 0;
}

void loop() {
  
    naechster = aufrufen(naechster);
  
}

#else

int main(){
	int naechster = aufrufen(0);
	while (naechster != 10)
	{
		naechster = aufrufen(naechster);
	}
	return 0;
}

#ifdef ARDUINO

