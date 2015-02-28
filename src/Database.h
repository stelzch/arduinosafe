#ifndef DATABASE_H_
#define DATABASE_H_

#include "DatabaseEntry.h"

class Database {
	public:
		DatabaseEntry readEntry(char[]);
		DatabaseEntry[] readAll();
};
#endif