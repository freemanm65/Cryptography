#include "cipher.h"

void SubBytes(Rijndael& in)
{
	if (in.coefs.ch) {
		in = *(in.inv());

		union poly coefs = in.coefs;

		coefs.bits.b0 = in.coefs.bits.b0 ^ in.coefs.bits.b4 ^ in.coefs.bits.b5 ^ in.coefs.bits.b6 ^ in.coefs.bits.b7;
		coefs.bits.b1 = in.coefs.bits.b1 ^ in.coefs.bits.b5 ^ in.coefs.bits.b6 ^ in.coefs.bits.b7 ^ in.coefs.bits.b0;
		coefs.bits.b2 = in.coefs.bits.b2 ^ in.coefs.bits.b6 ^ in.coefs.bits.b7 ^ in.coefs.bits.b0 ^ in.coefs.bits.b1;
		coefs.bits.b3 = in.coefs.bits.b3 ^ in.coefs.bits.b7 ^ in.coefs.bits.b0 ^ in.coefs.bits.b1 ^ in.coefs.bits.b2;
		coefs.bits.b4 = in.coefs.bits.b4 ^ in.coefs.bits.b0 ^ in.coefs.bits.b1 ^ in.coefs.bits.b2 ^ in.coefs.bits.b3;
		coefs.bits.b5 = in.coefs.bits.b5 ^ in.coefs.bits.b1 ^ in.coefs.bits.b2 ^ in.coefs.bits.b3 ^ in.coefs.bits.b4;
		coefs.bits.b6 = in.coefs.bits.b6 ^ in.coefs.bits.b2 ^ in.coefs.bits.b3 ^ in.coefs.bits.b4 ^ in.coefs.bits.b5;
		coefs.bits.b7 = in.coefs.bits.b7 ^ in.coefs.bits.b3 ^ in.coefs.bits.b4 ^ in.coefs.bits.b5 ^ in.coefs.bits.b6;

		in.set_coefs(coefs.ch);
	}

	in ^= (unsigned char)99;
}
