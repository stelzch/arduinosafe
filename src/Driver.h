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
