class UserInterface {
	public:
		virtual int selectFromList(string caption, string entries[], int numEntries) = 0;
		virtual char[] readString() = 0;
	private:
};
