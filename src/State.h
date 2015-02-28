class State {
	public:
		State();
		virtual ~State();
		virtual void start(Driver&) = 0;
		virtual int getId() = 0;
	private:
		int id;
};
