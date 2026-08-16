#include "bigint.hpp"

bigint::bigint(unsigned long long num)
{
    separateDigits(num);
}

void bigint::separateDigits(unsigned long long num)
{
    unsigned long long result = num / 10;
    int rest = num % 10;
    if (result)
        separateDigits(result);
    v_bigint.push_back(rest);
}

bigint::bigint(string s_bigint)
{
    size_t slen = s_bigint.length();
    bool start = false;
    for (size_t i = 0; i < slen; i++)
    {
        if (!start && s_bigint.c_str()[i] != '0')
            start = true;
        if (start)
            v_bigint.push_back(s_bigint.c_str()[i] - '0');
    }
    if (!start)
        v_bigint.push_back(0);
}

bigint::bigint(const bigint& original) 
{
    v_bigint = original.v_bigint;
}

bigint& bigint::operator=(const bigint& original)
{
    v_bigint.clear();
    v_bigint = original.v_bigint;
    return *this;
}

ostream& operator<<(ostream& out, const bigint& value)
{
    for (size_t i = 0; i < value.v_bigint.size(); i++)
        out << value.v_bigint[i];
    if (!value.v_bigint.size())
        out << 0;
    return out;
}

bigint bigint::operator+(const bigint& r_operand) const
{
    bigint temp;
    // !!!
    temp.v_bigint.clear();
    // !!!
    bigint Arev;
    bigint Brev;

    /* if (!getSize() && !r_operand.getSize())
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
    } */

    Arev = *this;
    reverse(Arev.v_bigint.begin(), Arev.v_bigint.end());
    Brev = r_operand;
    reverse(Brev.v_bigint.begin(), Brev.v_bigint.end());
    int left = 0;
    for (size_t i = 0; i < Arev.v_bigint.size() || i < Brev.v_bigint.size(); i++)
    {
        int a = (i < Arev.v_bigint.size()) ? Arev.v_bigint[i] : 0;
        int b = (i < Brev.v_bigint.size()) ? Brev.v_bigint[i] : 0;

        int tmp = left + a + b;
        int rest = tmp % 10;
        left = tmp / 10;
        temp.v_bigint.push_back(rest);
    }
    if (left)
        temp.v_bigint.push_back(left);
    /* while (temp.v_bigint.size() > 1 && temp.v_bigint.back() == 0)
    {
        temp.v_bigint.pop_back();
    } */
    reverse(temp.v_bigint.begin(), temp.v_bigint.end());
    return temp;
}

bigint& bigint::operator+=(const bigint& r_operand)
{
    bigint temp = *this + r_operand;
    this->v_bigint.clear();
    *this = temp;
    return *this;
}

bigint& bigint::operator++()
{
    *this += 1;
    return *this;
}

bigint bigint::operator++(int)
{
    bigint old;
    old = *this;
    *this += 1;
    return old;
}

bool bigint::operator==(const bigint& r_operand) const
{
    return this->v_bigint == r_operand.v_bigint;
}

bool bigint::operator!=(const bigint& r_operand) const
{
    return !(*this == r_operand);
}

bool bigint::operator<(const bigint& r_operand) const
{
    if (this->v_bigint.size() < r_operand.v_bigint.size())
        return true;
    else if (this->v_bigint.size() > r_operand.v_bigint.size())
        return false;
    return this->v_bigint < r_operand.v_bigint;
}

bool bigint::operator<=(const bigint& r_operand) const
{
    return (*this < r_operand) || (*this == r_operand);
}

bool bigint::operator>(const bigint& r_operand) const
{
    if (this->v_bigint.size() > r_operand.v_bigint.size())
        return true;
    else if (this->v_bigint.size() < r_operand.v_bigint.size())
        return false;
    return this->v_bigint > r_operand.v_bigint;
}

bool bigint::operator>=(const bigint& r_operand) const
{
    return (*this > r_operand) || (*this == r_operand);
}

bigint bigint::operator<<(bigint times) const
{
    bigint temp(*this);

    // !!!
    if (temp == 0)
        return temp;
    // !!!
    for (size_t i = 0; (bigint)i < times; i++)
        temp.v_bigint.push_back(0);
    return temp;
}

bigint bigint::operator>>(bigint times) const
{
    bigint temp(*this);

    if (times >= temp.v_bigint.size())
    {
        temp.v_bigint.clear();
        temp = 0;
        return temp;
    }
    for (size_t count = 0; (bigint)count < times; count++)
        temp.v_bigint.pop_back();
    return temp;
}

bigint& bigint::operator<<=(bigint times)
{
    bigint temp = *this << times;
    this->v_bigint.clear();
    *this = temp;
    return *this;
}

bigint& bigint::operator>>=(bigint times)
{
    bigint temp = *this >> times;
    this->v_bigint.clear();
    *this = temp;
    return *this;
}
