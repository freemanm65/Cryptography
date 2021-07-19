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

Point::Point(int X, int Y, EllCurve Curve):x(X), y(Y), curve(Curve), isNeutral(false)
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

Point::Point(bool IsNeutral, EllCurve Curve): curve(Curve), isNeutral(IsNeutral)
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

	if (get_x() == rhs.get_x() && get_y() == rhs.get_y())
		return NeutralPoint(curve);

	if (get_x() == rhs.get_x()) {

	}
	
}

Point Point::operator-(const Point& rhs)
{
	return *this + rhs.inv();
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

Point Point::inv() const
{
	return Point(x, -y, curve);
}

NeutralPoint::NeutralPoint(EllCurve Curve): Point(true, Curve)
{
}
