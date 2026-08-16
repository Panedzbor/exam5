#include "bigint.hpp"
#include <iostream>

int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d), f("12345678901234567890123456789012345678901234567890"), g(999), h(1);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    c = d;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "f = " << f << std::endl;

    std::cout << "a + f = " << a + f << std::endl;
    std::cout << "g + h = " << g + h << std::endl;
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

    // Генерируем ту самую гигантскую строку из 217 девяток (из твоего примера)
    std::string str_999(217, '9');
    
    bigint nines(str_999);
    bigint one(1);
    bigint zero(0);

    std::cout << "=========================================" << std::endl;
    std::cout << " ТЕСТ 1: Переполнение (потеря нулей)" << std::endl;
    std::cout << "=========================================" << std::endl;
    // Без фикса внутри цикла operator+ этот код выдаст просто "1"
    
    bigint test1_result = nines + one;
    
    std::cout << "Ожидается: 1" << std::string(217, '0') << std::endl;
    std::cout << "Твой код : " << test1_result << std::endl;
    std::cout << std::endl;


    std::cout << "=========================================" << std::endl;
    std::cout << " ТЕСТ 2: Ведущие нули от сдвига" << std::endl;
    std::cout << "=========================================" << std::endl;
    // Без фикса в operator<< здесь появится лишний ведущий ноль: "0999...999"
    
    // Сдвигаем ноль на 1 длину нашего огромного числа (как если бы сработала логика теста)
    bigint shifted_zero = zero << bigint(217); 
    bigint test2_result = shifted_zero + nines;
    
    std::cout << "Ожидается: " << str_999 << std::endl;
    std::cout << "Твой код : " << test2_result << std::endl;
    std::cout << std::endl;


    std::cout << "=========================================" << std::endl;
    std::cout << " ТЕСТ 3: Каскадные операции" << std::endl;
    std::cout << "=========================================" << std::endl;
    // Проверка, что после исправления ничего не сломалось в базовой логике
    
    bigint ab = 0;
    ab = (ab << 50) + 99 + 1;
    
    std::cout << "Ожидается: 100" << std::endl;
    std::cout << "Твой код : " << ab << std::endl;
    std::cout << "=========================================" << std::endl;
}

