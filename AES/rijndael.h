// rijndael.h

#pragma once

#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

struct bitField{

	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;

};

union poly{

	unsigned char ch;
	struct bitField;

};


class Rijndael{

private:
	Rijndael(void);
	unsigned char *remDiv(const Rijndael&);
	static unsigned char *remDiv(unsigned char, unsigned char);

public:
	poly coefs;


	Rijndael(char);
//	~Rijndael(void);
	
	// Operator overloading
	Rijndael& operator+=(const Rijndael&);
    Rijndael& operator-=(const Rijndael&);
	Rijndael& operator*=(const Rijndael&);
	Rijndael& operator/=(const Rijndael&);
	Rijndael& operator^=(const unsigned char);
	Rijndael operator+(const Rijndael&);
    Rijndael operator-(const Rijndael&);
	Rijndael operator*(const Rijndael&);
	Rijndael operator/(const Rijndael&);
	Rijndael operator<<(const unsigned char);
	Rijndael operator>>(const unsigned char);
	void operator=(const Rijndael&);
	void set_coefs(const unsigned char);
	bool operator==(const Rijndael&);
	bool operator!=(const Rijndael&);
	bool operator<(const Rijndael&);
	bool operator>(const Rijndael&);
	bool operator<=(const Rijndael&);
	bool operator>=(const Rijndael&);

	Rijndael* inv(void) const;

};
