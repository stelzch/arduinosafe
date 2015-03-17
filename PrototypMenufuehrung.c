#include <stdio.h>

char nutzlos[] = "";
char tempRueckgabe[] = "";
char mpw[] = "8";
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

//--------------------------------
int mpwinput(){
 
  ausgabe("Gib das MasterPW ein:","");
  eingabe();
  if (strcmp(tempRueckgabe,mpw)==1){
    printf("%s","r");
    return 4;
  }
  if (strcmp(tempRueckgabe,mpw)==0){
   printf("%s","f");
    return 0; 
  }
  
}


int SSSMenu(){
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
		return mpwinput();
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

