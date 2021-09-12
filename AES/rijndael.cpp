// rijndael.cpp

#include "rijndael.h"

Rijndael::Rijndael(char init) {
	coefs.ch = init;
}

Rijndael::Rijndael() {
	new (this) Rijndael(0);
}

void Rijndael::set_coefs(const unsigned char ch) {
	coefs.ch = ch;
}

bool Rijndael::operator==(const Rijndael& rhs) {
	return coefs.ch == rhs.coefs.ch;
}

bool Rijndael::operator!=(const Rijndael& rhs) {
	return !(*(this) == rhs);
}

bool Rijndael::operator<(const Rijndael& rhs) {
	return coefs.ch < rhs.coefs.ch;
}

bool Rijndael::operator<=(const Rijndael& rhs) {
	return !(coefs.ch > rhs.coefs.ch);
}

bool Rijndael::operator>(const Rijndael& rhs) {
	return coefs.ch > rhs.coefs.ch;
}

bool Rijndael::operator>=(const Rijndael& rhs) {
	return !(coefs.ch < rhs.coefs.ch);
}

void Rijndael::operator=(const Rijndael& rhs) {
	coefs = rhs.coefs;
}

Rijndael Rijndael::operator+(const Rijndael& rhs) {
	Rijndael total;
	total.coefs.ch = coefs.ch ^ rhs.coefs.ch;
	return total;
}

Rijndael Rijndael::operator-(const Rijndael& rhs) {
	return *this + rhs;
}

Rijndael& Rijndael::operator+=(const Rijndael& rhs) {
	coefs.ch ^= rhs.coefs.ch;
	return *this;
}

Rijndael& Rijndael::operator-=(const Rijndael& rhs) {
	return *this += rhs;
}

Rijndael& Rijndael::operator^=(const unsigned char rhs) {
	coefs.ch ^= rhs;
	return *this;
}

unsigned char* Rijndael::remDiv(const Rijndael& divisor) {
	static unsigned char out[2];
	unsigned char temp = divisor.coefs.ch;
	unsigned char q = 0;
	int i, j;

	if (0 != coefs.ch && *this < divisor) {
		out[0] = 0;
		out[1] = coefs.ch;
		return out;
	}

	if (*this == 0)
		i = 9;
	else
		for (i = 0; temp >> i != 0; i++);

	temp = coefs.ch;
	for (j = 0; temp >> j != 0; j++);

	while (j - i >= 0) {
		temp ^= divisor.coefs.ch << (j - i);
		q ^= (unsigned char)(1 << (j - i));

		for (j = 0; temp >> j != 0; j++);
	}
	out[0] = q;
	out[1] = temp;
	return out;
}

// unsigned char *Rijndael::remDiv(unsigned char, unsigned char){
// }

Rijndael* Rijndael::inv() const {
	Rijndael* inverse = new Rijndael();
	Rijndael q;
	Rijndael r_2;
	Rijndael r_1(coefs.ch);
	Rijndael t_2;
	Rijndael t_1(1);
	unsigned char temp;
	unsigned char* qr;

	while (r_1.coefs.ch != 1) {
		temp = r_1.coefs.ch;
		qr = r_2.remDiv(r_1);
		q.set_coefs(qr[0]);
		r_1.set_coefs(qr[1]);
		r_2.set_coefs(temp);
		temp = t_1.coefs.ch;
		t_1 = t_2 + (q * t_1);
		t_2.set_coefs(temp);
	}

	inverse->set_coefs(t_1.coefs.ch);
	return inverse;
}

Rijndael Rijndael::operator<<(const unsigned char shift) {
	Rijndael total;
	int deg;
	for (deg = 0; coefs.ch >> deg != 0; deg++);

	if (deg + shift < 9)
		total.set_coefs(coefs.ch << shift);

	else {
		total.set_coefs(coefs.ch);

		unsigned char i = shift;
		while (i > 0) {
			total.set_coefs(total.coefs.ch << (9 - deg));
			total ^= 27;
			i -= 9 - deg;
			for (deg = 0; total.coefs.ch >> deg != 0; deg++);
		}
	}

	return total;
}

Rijndael Rijndael::operator*(const Rijndael& rhs) {
	Rijndael total;
	for (int i = 0; i < 8; i++) {
		if ((rhs.coefs.ch >> i) % 2)
			total += *this << i;
	}

	return total;
}

Rijndael& Rijndael::operator*=(const Rijndael& rhs) {
	*this = *this * rhs;
	return *this;
}

Rijndael Rijndael::operator/(const Rijndael& rhs) {
	return *this * *(rhs.inv());
}

Rijndael& Rijndael::operator/=(const Rijndael& rhs) {
	*this = *this / rhs;
	return *this;
}