#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class bigint {
	public:
		bigint() {};
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
		bigint operator>>(size_t times) const;
		bigint operator<<(bigint times) const;
		bigint operator<<(size_t times) const;
		bigint& operator>>=(bigint times);
		bigint& operator>>=(size_t times);
		bigint& operator<<=(bigint times);
		bigint& operator<<=(size_t times);

		int getDigit(size_t index) const {return v_bigint[index];};
		size_t getSize() const {return v_bigint.size();};
		void setDigitToBack(int num) {v_bigint.push_back(num);};
		void reverseVector() {reverse(v_bigint.begin(), v_bigint.end());};

	private:
		vector<unsigned int> v_bigint;
		void separateDigits(unsigned long long num);
};

ostream& operator<<(ostream& out, const bigint& value);

#endif
