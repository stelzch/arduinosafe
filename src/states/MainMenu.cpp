class MainMenu : public State {
public:
	void start(Driver& driver) {
		int selected = driver.userInterface.selectFromList(
			[
				"View PWs",
				"New PW",
				"Edit MPW",
				"Edit Keyword"
			]
		);
		switch(selected) {
			case 0:
				
		}
	}
}
