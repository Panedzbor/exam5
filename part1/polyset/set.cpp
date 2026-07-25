#include "set.hpp"
#include "searchable_bag.hpp"

set::set(const searchable_bag & bag)
{
    this->bag = &bag;
    wrap_to_set();
}

void set::wrap_to_set()
{
    
}
