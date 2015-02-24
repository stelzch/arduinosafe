class State {
	public:
		State();
		virtual ~State();
		void start(Driver&);
		int getId();
	private:
		int id;
};
