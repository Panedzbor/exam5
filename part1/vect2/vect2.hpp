#pragma once

#include <iostream>

class vect2 {
    
    public:
        vect2();
        vect2(int x, int y);
        vect2(const vect2 &);
        vect2 & operator=(const vect2 &);
        ~vect2();

        vect2 operator+(const vect2 &) const;
        vect2 operator-(const vect2 &) const;
        vect2 operator*(int) const;

        vect2 & operator+=(const vect2 &);
        vect2 & operator-=(const vect2 &);
        vect2 & operator*=(int);

        vect2 & operator++();
        vect2 operator++(int);
        vect2 & operator--();
        vect2 operator--(int);

        vect2 operator-() const;

        bool operator==(const vect2 &) const;
        bool operator!=(const vect2 &) const;
        bool operator<(const vect2 &) const;
        bool operator<=(const vect2 &) const;
        bool operator>(const vect2 &) const;
        bool operator>=(const vect2 &) const;

        int & operator[](int);
        int operator[](int) const;

        int x;
        int y;
        int len;
};

std::ostream & operator<<(std::ostream &, vect2 &);
std::ostream & operator<<(std::ostream &, const vect2 &);
vect2 operator*(int, const vect2 &);