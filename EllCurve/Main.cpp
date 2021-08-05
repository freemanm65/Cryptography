#include "ellCurve.h"

int main() {

	EllCurve curve(1, 44, 251);
	Point P(244, 237, curve);
	Point Q = 121*P;
	Q.Print();

}