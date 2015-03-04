#include <stdio.h>
#include <windows.h>
//#include <string>

char nutzlos[] = "";
char tempRueckgabe[] = "";

void ausgabe(char zeile1[], char zeile2[])
{
	printf(zeile1);
	printf("\n");
	printf(zeile2);
}

void eingabe()
{
	//char rueckgabe[] = "";
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

	printf("Your choice: ");
	int choice;
	scanf_s("%d", &choice);
	//choice -= 48;
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
int hauptmenue()
{
	char* dasHauptMenu[] = { "Wo willst du hin?", "Obstmenu", "Musikmenu", "Sportmenu","SSSMenu", "" };
	int auswahl = showMenu(dasHauptMenu);
	return auswahl;
}
//--------------------------------

int obstMenu(){
	char* dasMenuHeute[] = { "Was willst du essen?", "Apfel", "Birne", "Banane", "Mango", "Kiwi", "Zurueck", "" };
	int auswahl = showMenu(dasMenuHeute);
	ausgabe(dasMenuHeute[auswahl],"");
	return 0;
}

int (*musikMenuZeiger)() = & MusikMenu;

int MusikMenu(){
	char* dieMusikAuswahl[] = { "Was willst du hoeren?", "Musik", "Stille", "Nichts", "Zurueck", "Kiwi", ""};
	int auswahl = showMenu(dieMusikAuswahl);
	if (auswahl=5){
		printf("Kiwi is keine Musik");
	}
	ausgabe(dieMusikAuswahl[auswahl], "");
	return 0;
}

int SportMenu(){
	clearScreen();
	char* SportAuswahl[] = { "Was willst du spielen", "Nichts", "Schach", "Hau den ..", "Zurueck", "Kiwi", "" };
	int auswahl = showMenu(SportAuswahl);
	if (auswahl == 5){
		printf("Kiwi is ne geile Sportart")  ;
	}
	ausgabe(SportAuswahl[auswahl], "");
	return 0;
}

int SSSMenu(){
	clearScreen();
	char* SSSMenu[] = { "Aktion", "Passwoerter", "MasterPW", "aluxa", "AFK", "Kiwi", "" };
	int auswahl = showMenu(SSSMenu);
	if (auswahl == 5){
		printf("Der Edeka is nur fuenf min entfernt");
	}
	ausgabe(SSSMenu[auswahl], "");
	return 0;
}

int aufrufen(int auswahl){
	{
	switch (auswahl)
	{
	case 0:
		return hauptmenue();
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

int main(){
	int naechster = aufrufen(0);
	while (naechster != 10)
	{
		naechster = aufrufen(naechster);
	}
	return 0;
}

// char* dasMenuHeute[] = { "Was willst du essen?", "Apfel", "Birne", "Banane", "Mango", "Kiwi" };
// int auswahl = showMenu(dasMenuHeute);
// printf("Auswahl war %d\n", auswahl);
