#include "cipher.h"

int main() {
	Rijndael a(83);
	SubBytes(a);
	cout << +(a.coefs.ch) << endl;
	cin.get();
}