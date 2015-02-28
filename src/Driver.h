#ifndef DRIVER_H_
#define DRIVER_H_

class Driver {
	public:
		enum States {
			MainMenu,
			ViewPWs
		};
		UserInterface userInterface;
		Database db;
		virtual void callState(States) = 0;
	private:
		State& lastState;
};

#endif