#include "ellCurve.h"

int main() {

	EllCurve curve(-2, 2, 7);
	Point P(1, 1, curve);
	Point Q(1, -1, curve);
	P += P;
	P.Print();

}