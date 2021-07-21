#include "ellCurve.h"

bool EllCurve::validCurve(void)
{
	return ((4 * A * A * A + 27 * B * B) % P);
}

EllCurve::EllCurve(int a, int b, int p) : A(a), B(b), P(p)
{
	if (!(validCurve()))
		cout << "Invalid elliptic curve" << endl;
}

int EllCurve::get_a() const
{
	return A;
}

int EllCurve::get_b() const
{
	return B;
}

int EllCurve::get_p() const
{
	return P;
}

int EllCurve::f(int x)
{
	return (x * x * x + A * x + B) % P;
}

bool EllCurve::operator==(const EllCurve& rhs)
{
	return (A == rhs.get_a()) && (B == rhs.get_b()) && (P == rhs.get_p());
}

void EllCurve::operator=(const EllCurve& rhs)
{
	A = rhs.get_a();
	B = rhs.get_b();
	P = rhs.get_p();
}

unsigned int EllCurve::order(void)
{
	unsigned int total = 1;
	for (int i = 0; i < get_p(); i++)
		total += jacobi(i, get_p()) + 1;
	return total;
}

Point::Point(int X, int Y, EllCurve Curve) :x(X), y(Y), curve(Curve), isNeutral(false)
{
	if (!onCurve())
		cout << "This point is not on the curve" << endl;
}

int Point::get_x(void) const
{
	return x;
}

int Point::get_y(void) const
{
	return y;
}

EllCurve Point::get_curve(void) const
{
	return curve;
}

bool Point::onCurve()
{
	return curve.f(x) == ((y * y) % curve.get_p());
}

Point::Point(bool IsNeutral, EllCurve Curve) : curve(Curve), isNeutral(IsNeutral)
{
}

bool Point::operator==(const Point& rhs)
{
	return (x == rhs.get_x()) && (y == rhs.get_y()) && (curve == rhs.get_curve());
}

void Point::operator=(const Point& rhs)
{
	x = rhs.get_x();
	y = rhs.get_y();
	curve = rhs.get_curve();
}

Point Point::operator+(const Point& rhs)
{
	if (isNeutral)
		return rhs;
	if (rhs.isNeutral)
		return *this;

	if (get_x() == rhs.get_x() && !((get_y() + rhs.get_y()) % curve.get_p()))
		return NeutralPoint(curve);

	int m;
	int a = curve.get_a();
	int p = curve.get_p();

	if (get_x() == rhs.get_x()) {
		m = (3 * x * x + a) % p;
		m *= eea(p, 2 * get_y())[2];
	}
	else {
		m = y - rhs.get_y();
		m *= eea(p, x - rhs.get_x())[2];
	}

	m %= p;

	int x3 = (-x - rhs.get_x() + m * m) % p;
	int y3 = (-m * (x3 - rhs.get_x()) - rhs.get_y()) % p;

	return Point(x3, y3, curve);
}

Point Point::operator-(const Point& rhs)
{
	return *this + rhs.inv();
}

Point Point::operator*(int n)
{
	Point Q = NeutralPoint(curve);
	Point R = *this;

	while (n > 0) {
		if (n % 2) {
			Q += R;
			n--;
		}
		n >>= 1;
		if (n > 0)
			R = R.dbl();
	}

	return Q;
}

Point& Point::operator+=(const Point& rhs)
{
	*this = *this + rhs;
	return *this;
}

Point& Point::operator-=(const Point& rhs)
{
	*this = *this - rhs;
	return *this;
}

Point& Point::operator*=(int n)
{
	*this = *this * n;
	return *this;
}

Point Point::inv() const
{
	return Point(x, -y, curve);
}

Point Point::dbl() const
{
	if (isNeutral)
		return *this;

	int m;
	int a = curve.get_a();
	int p = curve.get_p();

	m = (3 * x * x + a) % p;
	m *= eea(p, 2 * y)[2];
	m %= p;

	int x3 = (-x - x + m * m) % p;
	int y3 = (-m * (x3 - x) - y) % p;

	return Point(x3, y3, curve);
}

NeutralPoint::NeutralPoint(EllCurve Curve) : Point(true, Curve)
{
}