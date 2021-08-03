#include "NT.h"

int* eea(int x, int y) {
	int* ret = new int[3];
	ret[0] = y < 0 ? x + y : y;
	ret[1] = 0;
	ret[2] = 1;

	int s_1 = 1;
	int t_1 = 0;
	int q, temp;

	while (x % ret[0]) {
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

int sqrtmodp(int a, int p)
{
	a %= p;
	if (p % 8 == 3 || p % 8 == 7)
		return expmod(a, (p + 1) >> 2, p);
	if (p % 8 == 5) {
		int x = expmod(a, (p + 3) >> 3, p);
		int c = (x * x) % p;
		if (c != a)
			x = x * expmod(2, (p + 1) >> 2, p);
		return x;
	}
	srand(time(0));
	int d = 2;
	while (jacobi(d, p) != 1)
		d = rand() % (p - 2) + 2;
	int k = 0;
	int q = p - 1;
	while (!(q % 2)) {
		q >>= 1;
		k++;
	}
	int A = expmod(a, q, p);
	int D = expmod(d, q, p);
	int m = 0;
	for (int i = 0; i < k; i++) {
		if (expmod(A * expmod(D, m, p), (int)pow(2, k - 1 - i), p) == p - 1)
			m += (int)pow(2, i);
	}
	return expmod(a, (q + 1) >> 1, p) * expmod(D, m >> 1, p) % p;
}

int expmod(int b, int e, int m)
{
	int r = 1;
	while (e > 0) {
		if (e % 2)
			r = (r * b) % m;
		b = (b * b) % m;
		e >>= 1;
	}

	return r;
}