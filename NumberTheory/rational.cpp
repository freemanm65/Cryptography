#include "rational.h"

Rational::Rational(int x, int y): a(x), b(1)
{
	if (y) {
		b = y;
		simplify();
	}
	else
		std::cout << "Cannot have a denominator of 0" << std::endl;
}

Rational::Rational(void): a(0), b(1)
{
}

int Rational::get_a(void) const
{
	return a;
}

int Rational::get_b(void) const
{
	return b;
}

void Rational::simplify(void)
{
	if (a == 0) {
		b = 1;
		return;
	}

	if (b < 0) {
		a *= -1;
		b *= -1;
	}

	int d;
	if (a < 0)
		d = gcd(-a, b);
	else
		d = gcd(a, b);
	a /= d;
	b /= d;
}

Rational& Rational::operator+=(const Rational& rhs)
{
	int x = rhs.get_a();
	int y = rhs.get_b();

	int temp = a * y + b * x;
	b = b * y;
	a = temp;

	simplify();

	return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
	int x = rhs.get_a();
	int y = rhs.get_b();

	int temp = a * y - b * x;
	b = b * y;
	a = temp;

	simplify();

	return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
	int x = rhs.get_a();
	int y = rhs.get_b();

	a *= x;
	b *= y;

	simplify();

	return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
	int x = rhs.get_a();
	int y = rhs.get_b();

	if (!x) {
		std::cout << "Invalid division. Can't divide by 0" << std::endl;
		return *this;
	}

	a *= y;
	b *= x;

	simplify();

	return *this;
}

Rational Rational::operator+(const Rational& rhs)
{
	Rational total = *this;
	total += rhs;
	return total;
}

Rational Rational::operator-(const Rational& rhs)
{
	Rational total = *this;
	total -= rhs;
	return total;
}

Rational Rational::operator*(const Rational& rhs)
{
	Rational total = *this;
	total *= rhs;
	return total;
}

Rational Rational::operator/(const Rational& rhs)
{
	Rational total = *this;
	total /= rhs;
	return total;
}

void Rational::operator=(const Rational& rhs)
{
	a = rhs.get_a();
	b = rhs.get_b();
}

bool Rational::operator==(const Rational& rhs)
{
	return (a == rhs.get_a()) && (b == rhs.get_b());
}

bool Rational::operator!=(const Rational& rhs)
{
	return !(*this == rhs);
}

bool Rational::operator<(const Rational& rhs)
{
	if (a / b == rhs.get_a() / rhs.get_b())
		return (a % b) < (rhs.get_a() % rhs.get_b());
	return (a / b) < (rhs.get_a() / rhs.get_b());
}

bool Rational::operator>(const Rational& rhs)
{
	if (a / b == rhs.get_a() / rhs.get_b())
		return (a % b) > (rhs.get_a() % rhs.get_b());
	return (a / b) > (rhs.get_a() / rhs.get_b());
}

bool Rational::operator<=(const Rational& rhs)
{
	return !(*this > rhs);
}

bool Rational::operator>=(const Rational& rhs)
{
	return !(*this < rhs);
}

Rational::operator int() const
{
	return (int)(a / b);
}

Rational::operator double() const
{
	return (double)(a / b);
}

Rational::operator float() const
{
	return (float)(a / b);
}

Rational Rational::inv() const
{
	if (a == 0) {
		std::cout << "0 has no inverse" << std::endl;
		return *this;
	}
	return Rational(b, a);
}

void Rational::Print(void) const
{
	if (a == 0)
		std::cout << "0" << std::endl;
	else
		std::cout << a << "/" << b << std::endl;
}
