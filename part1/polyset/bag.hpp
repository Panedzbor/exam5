#pragma once

#include <cstdlib>

class bag {
public:
	virtual void insert (int) = 0;
	virtual void insert (int *, int) = 0;
	virtual void print() const = 0;
	virtual void clear() = 0;
	virtual int* export_to() const = 0;
};
