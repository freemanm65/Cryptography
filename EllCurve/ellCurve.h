#pragma once

#include <iostream>
#include <typeinfo>

using namespace std;

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


	// Operator overloading
	bool operator==(const Point&);
	void operator=(const Point&);
	Point operator+(const Point&);
	Point operator-(const Point&);
	Point& operator+=(const Point&);
	Point& operator-=(const Point&);

	Point inv() const;
};

class NeutralPoint : Point {


public:
	NeutralPoint(EllCurve);

};