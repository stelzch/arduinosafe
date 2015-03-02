#ifndef SAFEDRIVER_H_
#define SAFEDRIVER_H_

#include "../Driver.h"

class SafeDriver : public Driver {
	public:
		enum States {
			EnterMPW,
			MPWEmpty,
			DisplayKeyword,
			MainMenu,
			SelectPW,
			DisplayPW,
			NewPW,
			EnterPW,
			GeneratePW,
			EditPW,
			EditMPW,
		}
	Driver();
	virtual ~Driver();
	

};
#endif