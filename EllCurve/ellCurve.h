#pragma once

#include <iostream>
#include <typeinfo>
#include "NT.h"

class EllCurve {
	int A, B, P;

	bool validCurve(void);

public:
	EllCurve(int, int, int);

	int get_a(void) const;
	int get_b(void) const;
	int get_p(void) const;

	int f(int);

	// Operator overloading
	bool operator==(const EllCurve&);
	void operator=(const EllCurve&);

	unsigned int order(void);
};

class Point {
	int x, y;
	EllCurve curve;
	bool onCurve();

protected:
	Point(bool, EllCurve);
	bool isNeutral;

public:
	Point(int, int, EllCurve);

	int get_x(void) const;
	int get_y(void) const;
	EllCurve get_curve(void) const;
	bool get_isNeutral(void) const;

	// Operator overloading
	virtual bool operator==(const Point&);
	void operator=(const Point&);
	virtual Point operator+(const Point&);
	virtual Point operator-(const Point&);
	virtual Point operator-(void) const;
	Point operator*(int);
	Point& operator+=(const Point&);
	Point& operator-=(const Point&);
	Point& operator*=(int);

	Point inv(void) const;
	Point dbl(void) const;

	virtual void Print(void);
};

class NeutralPoint : public Point {
public:
	NeutralPoint(EllCurve);

	bool operator==(const Point&) override;
	Point operator+(const Point&) override;
	Point operator-(const Point&) override;
	Point operator-(void) const override;

	void Print(void) override;
};