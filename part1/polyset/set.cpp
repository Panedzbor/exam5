#include "set.hpp"
#include "searchable_bag.hpp"
#include <iostream>

set::set(const searchable_bag & bag) : size(0), data(NULL)
{
    this->bag = &bag;
    int* temp = bag.export_to();
	int bag_size = bag.get_size();
	insert(temp, bag_size);
	delete[] temp;
}

set::set(const set & original) : size(original.size), bag(original.bag)
{
	insert(original.data, size);
}

set & set::operator=(const set & original)
{
	bag = original.bag;
	size = original.size;
	insert(original.data, size);
	return *this;
}

set::~set() {}

void set::insert(int item) {
	if (has(item))
        return;
    int *new_data = new int[size + 1];
	for (int i = 0; i < size; i++) {
		new_data[i] = data[i];
	}
	new_data[size] = item;
	if (data != NULL) {
		delete[] data;
	}
	data = new_data;
	size++;
}

void set::insert(int *items, int count) {
    for (int i = 0; i < count; i++)
        insert(items[i]);
}

void set::print() const {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

void set::clear() {
	if (data != NULL) {
		delete[] data;
		data = NULL;
	}
	size = 0;
}

bool set::has(int dig) const
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == dig)
            return true;
    }
    return false;
}

const searchable_bag & set::get_bag() const
{
	return *bag;
}