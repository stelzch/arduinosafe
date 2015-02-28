#ifndef STATE_H_
#define STATE_H_

class State {
	public:
		State();
		virtual ~State();
		virtual void start(Driver&) = 0;
		virtual int getId() = 0;
	private:
		int id;
};

#endif