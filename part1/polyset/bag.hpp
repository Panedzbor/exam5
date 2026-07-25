#pragma once

class bag {
public:
	virtual void insert (int) = 0;
	virtual void insert (int *, int) = 0;
	virtual void print() const = 0;
	virtual void clear() = 0;
	virtual void export_to(int * array, int * size) const = 0;
};
