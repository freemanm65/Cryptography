#include "rijndael.h"

int main() {
	Rijndael a(30);
	cout << +(a.coefs.ch) << endl;
	/*unsigned char deg;
	for (deg = 0; a.coefs.ch >> deg != 0; deg++);
	cout << +deg << endl;*/
	Rijndael b(9);
	cout << +(b.coefs.ch) << endl;

	a = a * b;
	cout << +(a.coefs.ch) << endl;
	cin.get();
}