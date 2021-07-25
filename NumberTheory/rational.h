#pragma once

#include <iostream>
#include "NT.h"

class Rational {
	int a, b;

	void simplify(void);

public:
	Rational(int, int);
	Rational(void);

	int get_a(void) const;
	int get_b(void) const;

	Rational& operator+=(const Rational&);
	Rational& operator-=(const Rational&);
	Rational& operator*=(const Rational&);
	Rational& operator/=(const Rational&);
	Rational operator+(const Rational&);
	Rational operator-(const Rational&);
	Rational operator*(const Rational&);
	Rational operator/(const Rational&);
	void operator=(const Rational&);
	bool operator==(const Rational&);
	bool operator!=(const Rational&);
	bool operator<(const Rational&);
	bool operator>(const Rational&);
	bool operator<=(const Rational&);
	bool operator>=(const Rational&);

	operator int() const;
	operator double() const;
	operator float() const;

	Rational inv(void) const;
	void Print(void) const;
};
