#ifndef WINDOWSUSERINTERFACE_H_
#define WINDOWSUSERINTERFACE_H_

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class WindowsUserInterface {
public:
	int selectFromList(string caption, string entries[], int numberOfEntries) {
		
		clearScreen(); // Clear previous output

		// ==First, set caption==
		cout << caption << endl; // Print the caption
		for(int i=0;i<caption.size();i++) {
			cout << "="; // Underline it
		}
		cout << endl; // Flush the output
		
		for(int i=0;i<numberOfEntries;i++) {
			// Step through the array
			cout << i+1 << ". " << entries[i] << endl;
		}
		int selected;
		cin >> selected;
		return selected - 1;
	}
	string readString(string caption) {
		clearScreen(); // Clear previous output

		// ==First, set caption==
		cout << caption << endl; // Print the caption
		for(int i=0;i<caption.size();i++) {
			cout << "="; // Underline it
		}
		cout << endl; // Flush the output
		
		string response;
		cin >> response;
		return response;
	}
private:
	void println(char text[]) {
		cout << text << endl;
	}
	void clearScreen() {
		cout << "\033c" << endl;
	}
	
};

#endif