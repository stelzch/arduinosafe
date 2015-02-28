class UserInterface {
	public:
		virtual void setCaption(char[] caption) = 0;
		virtual int selectFromList(char entries[][]) = 0;
		virtual char[] readString() = 0;
	private:
};
