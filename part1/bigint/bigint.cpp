#include "bigint.hpp"

bigint::bigint(const bigint& original) : v_bigint(original.v_bigint) {}

bigint::bigint(string s_bigint)
{
    bool start = false;
    for (size_t i = 0; i < s_bigint.length(); i++)
    {
        if (!start && s_bigint.c_str()[i] != '0')
            start = true;
        if (start)
            v_bigint.push_back(s_bigint.c_str()[i] - '0');
    }
    if (s_bigint == "0")
        v_bigint.push_back(0);
}

bigint::bigint(unsigned long long num)
{
    separateDigits(num);
}

void bigint::separateDigits(unsigned long long num)
{
    unsigned long long result;
    unsigned long long rest;

    result = num / 10;
    rest = num % 10;
    if (result)
        separateDigits(result);
    v_bigint.push_back(rest);
}

ostream& operator<<(ostream& out, const bigint& value)
{
    for (size_t i = 0; i < value.getSize(); i++)
        out << value.getDigit(i);
    return out;
}

bigint& bigint::operator=(const bigint& original)
{
    v_bigint = original.v_bigint;
    return *this;
}

bigint bigint::operator+(const bigint& r_operand) const
{
    bigint temp;
    bigint Arev;
    bigint Brev;

    if (!getSize() && !r_operand.getSize())
        return temp;
    if (!getSize())
    {
        temp = r_operand;
        return temp;
    }
    if (!r_operand.getSize())
    {
        temp = *this;
        return temp;
    }

    Arev = *this;
    Arev.reverseVector();
    Brev = r_operand;
    Brev.reverseVector();

    int left = 0;
    for (size_t i = 0; i < Arev.getSize() || i < Brev.getSize(); i++)
    {
        int a, b;
        if (i < Arev.getSize())
            a = Arev.getDigit(i);
        else
            a = 0;
        if (i < Brev.getSize())
            b = Brev.getDigit(i);
        else
            b = 0;
        int tmp = left + a + b;
        left = 0;
        if (tmp > 9)
            left = 1;
        int rest = tmp % 10;
        temp.setDigitToBack(rest);
    }
    if (left)
        temp.setDigitToBack(left);
    temp.reverseVector();
    return temp;
}

bigint& bigint::operator+=(const bigint& r_operand)
{
    *this = *this + r_operand;
    return *this;
}

bigint& bigint::operator++()
{
    return *this += 1;
}

bigint bigint::operator++(int)
{
    bigint old(*this);
    *this += 1;
    return old;
}

bool bigint::operator<(const bigint& r_operand) const
{
    if (getSize() == r_operand.getSize())
        return v_bigint < r_operand.v_bigint;
    bool result = getSize() < r_operand.getSize() ? true : false;
    return result;
}

bool bigint::operator<=(const bigint& r_operand) const
{
    if (getSize() == r_operand.getSize())
        return v_bigint <= r_operand.v_bigint;
    bool result = getSize() < r_operand.getSize() ? true : false;
    return result;
}

bool bigint::operator>(const bigint& r_operand) const
{
    if (getSize() == r_operand.getSize())
        return v_bigint > r_operand.v_bigint;
    bool result = getSize() > r_operand.getSize() ? true : false;
    return result;
}

bool bigint::operator>=(const bigint& r_operand) const
{
    if (getSize() == r_operand.getSize())
        return v_bigint > r_operand.v_bigint;
    bool result = getSize() > r_operand.getSize() ? true : false;
    return result;
}

bool bigint::operator==(const bigint& r_operand) const
{
    if (getSize() == r_operand.getSize())
        return v_bigint == r_operand.v_bigint;
    return false;
}

bool bigint::operator!=(const bigint& r_operand) const
{
    if (getSize() == r_operand.getSize())
        return v_bigint != r_operand.v_bigint;
    return true;
}

bigint bigint::operator<<(bigint times) const
{
    bigint temp(*this);

    for (bigint i(0); i < times; i++)
        temp.v_bigint.push_back(0);
    return temp;
}

bigint& bigint::operator<<=(bigint times)
{
    for (bigint i(0); i < times; i++)
        v_bigint.push_back(0);
    return *this;
}

bigint bigint::operator>>(bigint times) const
{
    bigint temp(*this);

    if (times >= (bigint)temp.getSize())
    {
        temp.v_bigint.clear();
        temp.v_bigint.push_back(0);
        return temp;
    }
    for (bigint count(0); count < times; count++)
        temp.v_bigint.pop_back();
    return temp;
}

bigint& bigint::operator>>=(bigint times)
{
    if (times >= (bigint)getSize())
    {
        v_bigint.clear();
        v_bigint.push_back(0);
        return *this;
    }
    for (bigint i(0); i < times; i++)
        v_bigint.pop_back();
    return *this;
}
