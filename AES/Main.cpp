#include "rijndael.h"


int main() {
	Rijndael a(13);
	cout << +(a.coefs.ch) << endl;
	Rijndael b = *(a.inv());
	cout << +(b.coefs.ch) << endl;
	cin.get();
}