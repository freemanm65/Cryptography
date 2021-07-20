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

char jacobi(int a, int n)
{
	if (!(a % n))
		return 0;

	char result = 1;

	if (a < 0) {
		a = -a;
		result *= n % 4 == 3 ? -1 : 1;
	}

	while (!(a % 2)) {
		a >>= 1;
		result *= n % 8 == 3 || n % 8 == 5 ? -1 : 1;
	}

	if (a == 1)
		return result;

	if (a % 4 == 3 && n % 4 == 3)
		return -1 * result * jacobi(n % a, a);

	return result * jacobi(n % a, a);
}