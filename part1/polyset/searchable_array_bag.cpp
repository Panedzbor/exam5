#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() {}

searchable_array_bag::searchable_array_bag(const searchable_array_bag & original) : array_bag(original) {}

searchable_array_bag & searchable_array_bag::operator=(const searchable_array_bag & original)
{
    array_bag::operator=(original);
    return *this;
}

searchable_array_bag::~searchable_array_bag() {}

bool searchable_array_bag::has(int dig) const
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == dig)
            return true;
    }
    return false;
}

int searchable_array_bag::get_size() const
{
    return size;
}