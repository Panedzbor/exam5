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
        //int* set_arr;
        set();
        const searchable_bag * bag;
        void wrap_to_set();
};
