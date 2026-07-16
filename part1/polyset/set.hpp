#pragma once

#include "searchable_bag.hpp"

class set {
    public:
        set(const searchable_bag & bag);
        set(const set & original);
        set & operator=(const set & original);
        ~set();

        void insert(int);
        void insert(int *array, int size);
        void print() const;
        void clear();
        bool has(int) const;
        const searchable_bag & get_bag() const;
    private:
        set();
        searchable_bag * bag;
};
