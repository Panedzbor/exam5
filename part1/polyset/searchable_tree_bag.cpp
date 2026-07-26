#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag & original) : tree_bag(original) {}

searchable_tree_bag & searchable_tree_bag::operator=(const searchable_tree_bag & original)
{
    tree_bag::operator=(original);
    return *this;
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int dig) const
{
    node * cur = tree;

    while (cur != NULL)
    {
        if (dig == cur->value)
            return true;
        if (dig < cur->value)
            cur = cur->l;
        else if (dig > cur->value)
            cur = cur->r;
    }
    return false;
}

int searchable_tree_bag::get_size() const
{
    return count_nodes(tree);
}
