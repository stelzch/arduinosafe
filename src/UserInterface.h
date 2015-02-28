class UserInterface {
	public:
		virtual int selectFromList(char caption[], char entries[][]) = 0;
		virtual char[] readString() = 0;
	private:
};
