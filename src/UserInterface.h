#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

class UserInterface {
	public:
		virtual string selectFromList(string caption, string entries[], int numEntries) = 0;
		virtual string readString(string caption) = 0;
	private:
};
#endif
