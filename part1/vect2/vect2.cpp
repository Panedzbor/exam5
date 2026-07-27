#include "vect2.hpp"

vect2::vect2() : x(0), y(0), sqlen(0) {}
vect2::vect2(int x, int y) : x(x), y(y), sqlen(x + y) {}
vect2::vect2(const vect2 & orig): x(orig.x), y(orig.y), sqlen(orig.sqlen) {}
vect2 & vect2::operator=(const vect2 & orig)
{
    x = orig.x;
    y = orig.y;
    sqlen = orig.sqlen;
    return *this;
}
vect2::~vect2() {}

vect2 & vect2::operator+=(const vect2 &plus)
{
    x += plus.x;
    y += plus.y;
    sqlen = x * x + y * y;
    return *this;
}

vect2 vect2::operator+(const vect2 &plus) const
{
    vect2 temp(this->x + plus.x, this->y + plus.y);
    return temp;
}

vect2 vect2::operator-(const vect2 &plus) const
{
    vect2 temp(this->x - plus.x, this->y - plus.y);
    return temp;
}

vect2 & vect2::operator-=(const vect2 &minus)
{
    x -= minus.x;
    y -= minus.y;
    sqlen = x * x + y * y;
    return *this;
}

vect2 & vect2::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;
    sqlen = x * x + y * y;
    return *this;
}

vect2 vect2::operator*(int scalar) const
{
    vect2 temp(this->x * scalar, this->y * scalar);
    return temp;
}

vect2 & vect2::operator++()
{
    x += 1;
    y += 1;
    sqlen = x * x + y * y;
    return *this;
}

vect2 vect2::operator++(int)
{
    vect2 temp(*this);
    x += 1;
    y += 1;
    sqlen = x * x + y * y;
    return temp;
}

vect2 & vect2::operator--()
{
    x -= 1;
    y -= 1;
    sqlen = x * x + y * y;
    return *this;
}

vect2 vect2::operator--(int)
{
    vect2 temp(*this);
    x -= 1;
    y -= 1;
    sqlen = x * x + y * y;
    return temp;
}

vect2 vect2::operator-() const
{
    return *this * (-1);
}

bool vect2::operator==(const vect2 & v) const
{
    if (x == v.x && y == v.y)
        return true;
    return false;
}

bool vect2::operator!=(const vect2 & v) const
{
    return !(*this == v);
}

bool vect2::operator<(const vect2 & v) const
{ 
    return sqlen < v.sqlen;
}

bool vect2::operator<=(const vect2 & v) const
{
    return sqlen <= v.sqlen;
}

bool vect2::operator>(const vect2 & v) const
{
    return sqlen > v.sqlen;
}

bool vect2::operator>=(const vect2 & v) const
{
    return sqlen >= v.sqlen;
}

int & vect2::operator[](int i)
{
    if (!i)
        return x;
    return y;
}

int vect2::operator[](int i) const
{
    vect2 temp(x, y);
    if (!i)
        return temp.x;
    return temp.y;
}

std::ostream & operator<<(std::ostream &out, vect2 &v)
{
    return out << "{" << v[0] << ", " << v[1] << "}" << std::endl;
}

std::ostream & operator<<(std::ostream &out, const vect2 &v)
{
    return out << "{" << v.x << ", " << v.y << "}" << std::endl;
}

vect2 operator*(int i, const vect2 &v)
{
    vect2 temp(v.x * i, v.y * i);
    return temp;
}