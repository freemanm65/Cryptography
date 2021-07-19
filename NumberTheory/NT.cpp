#include "NT.h"

int* eea(int x, int y) {
	int ret[3] = { y, 0, 1 };
	int s_1 = 1;
	int t_1 = 0;
	int q, temp;

	while (!(x % ret[0])) {
		q = (int)(x / ret[0]);
		temp = ret[0];
		ret[0] = x % ret[0];
		x = temp;
		temp = ret[1];
		ret[1] = s_1 - q * ret[1];
		s_1 = temp;
		temp = ret[2];
		ret[2] = t_1 - q * ret[2];
		t_1 = temp;
	}

	return ret;
}