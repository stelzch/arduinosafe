#include "userinterfaces/windows.h"

int main() {
	WindowsUserInterface ui;
	string entry[2];
	entry[0] = "Entry 1";
	entry[1] = "Entry 2";
	entry[2] = "Entry 3";
	int sel = ui.selectFromList("Select please", entry, 3);
	cout << entry[sel] << " was selected";
	return 0;
}