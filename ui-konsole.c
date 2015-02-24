#include<stdio.h>


/* diese Funktion zeigt ein Menu an, das vom Aufrufer
*  übergeben werden muss. Der Nutzer muss die angezeigte
* Ziffer tippen, die dem Aufrufer als Menuauswahl 
* zurückgemeldet wird.
* 
*/
int showMenu(char** entries)
{
  printf("%s\n", entries[0]);
  int i = 1;
  while(entries[i] != 0)
  {
    printf("%d. %s", i, entries[i]);
    printf("\n");
    i ++ ;
  }
  
  i -- ;
  
  printf("Your choice: ");
  int choice;
  scanf("%d", &choice);
  //choice -= 48;
  if((choice < 1) || (choice > i))
  {
    choice = 0;
  }
  return choice ;
}

/*
 * 
 * 
 */
int main()
{
  char* dasMenuHeute[] = {"Was willst du essen?", "Apfel", "Birne", "Banane", "Mango", "Kiwi"};
  int auswahl = showMenu (dasMenuHeute);
  printf("Auswahl war %d\n", auswahl);
  
}

