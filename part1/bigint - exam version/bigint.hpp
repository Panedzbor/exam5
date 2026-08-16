#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class bigint {
	public:
		bigint() {v_bigint.push_back(0);};
		bigint(string s_bigint);
		bigint(unsigned long long num);
		bigint(const bigint& original);
		bigint& operator=(const bigint& original);
		~bigint() {};

		bigint operator+(const bigint& r_operand) const;
		bigint& operator+=(const bigint& r_operand);
		bigint& operator++();
		bigint operator++(int);
		bool operator==(const bigint& r_operand) const;
		bool operator<(const bigint& r_operand) const;
		bool operator<=(const bigint& r_operand) const;
		bool operator>(const bigint& r_operand) const;
		bool operator>=(const bigint& r_operand) const;
		bool operator!=(const bigint& r_operand) const;
		bigint operator>>(bigint times) const;
		bigint operator<<(bigint times) const;
		bigint& operator>>=(bigint times);
		bigint& operator<<=(bigint times);

		vector<unsigned int> v_bigint;
	private:
		void separateDigits(unsigned long long num);
};

ostream& operator<<(ostream& out, const bigint& value);

#endif
