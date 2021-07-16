#include "rijndael.h"


int main() {
	Rijndael a(27);
	cout << +(a.coefs.ch) << endl;
	unsigned char deg;
	for (deg = 0; a.coefs.ch >> deg != 0; deg++);
	cout << +deg << endl;
	/*Rijndael b = *(a.inv());
	cout << +(b.coefs.ch) << endl;*/
	cin.get();
}