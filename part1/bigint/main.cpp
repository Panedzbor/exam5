#include "bigint.hpp"
#include <iostream>

int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d), f("12345678901234567890123456789012345678901234567890");

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    c = d;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "f = " << f << std::endl;

    std::cout << "a + f = " << a + f << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;
    std::cout << "(b += b) = " << (b += b) << std::endl;
    std::cout << "(d += e += a) = " << (d += e += a) << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;
    std::cout << "b = " << b << std::endl;
    c = 0;
    std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
    std::cout << "a + ++b + c++ = " << a + ++b + c++ << std::endl;
    std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;

	bigint x = ((b << 10) + 42);
    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "x = " << x << std::endl;
    std::cout << "(x >> 11) = " << (x >> 11) << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;
	d = bigint(43);
    std::cout << "a = " << a << std::endl;
    std::cout << "d = " << d << std::endl;

    std::cout << "d(=" << d << ") < a(=" << a << ") = " << (d < a) << std::endl;
    std::cout << "a(=" << a << ") < d(=" << d << ") = " << (a < d) << std::endl;
    std::cout << "d(=" << d << ") <= a(=" << a << ") = " << (d <= a) << std::endl;
    std::cout << "a(=" << a << ") <= a(=" << a << ") = " << (a <= a) << std::endl;
    std::cout << "d(=" << d << ") > a(=" << a << ") = " << (d > a) << std::endl;
    std::cout << "d(=" << d << ") >= a(=" << a << ") = " << (d >= a) << std::endl;
    std::cout << "d(=" << d << ") == a(=" << a << ") = " << (d == a) << std::endl;
    std::cout << "d(=" << d << ") != a(=" << a << ") = " << (d != a) << std::endl;
}

