#include "main_h.h"


//void out(valarray<double> M, int n) {
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n + 1; j++)
//			printf("%15.5f", M[i*(n + 1) + j]);
//		printf("\n");
//	}
//	printf("\n");
//}


double func(double x) { return 2 * exp(sin(x) / 2) * cos(5 * x); } // [0,5]


double f(double t, int k1, int k2, int n, double a, double b) {
	double x = (2 * t - a - b) / (b - a);

	if (k2 == n)
		return func(t) * legendre(k1, x);
	else
		return legendre(k1, x) * legendre(k2, x);
}


double simpson(double a, double b, int n, int k1, int k2, int N) {
	double h;
	double sig1 = 0.0;
	double sig2 = 0.0;
	h = (b - a) / n;

	for (int i = 1; i < n; i++)
	{
		if (i % 2 == 0)
			sig2 += f(a + i*h, k1, k2, N, a, b);
		else
			sig1 += f(a + i*h, k1, k2, N, a, b);
	}
	return (h / 3) * (f(a, k1, k2, N, a, b) + f(b, k1, k2, N, a, b) + 4 * sig1 + 2 * sig2);
}


double double_count(double a, double b, int k1, int k2, int N) {
	double R, I1, I2;
	double eps = 1e-5;
	int n = (int)ceil((b-a) / pow(eps, 0.25));
	if (n % 2 == 1)
		n++;

	do {
		I1 = simpson(a, b, n, k1, k2, N);
		I2 = simpson(a, b, 2 * n, k1, k2, N);
		R = fabs((I1 - I2)) / 15;
		n *= 2;
	} while (R > eps);

	return I2;
}


double legendre(int n, double x) {
	double Ln_prev = 1, Ln = x, Ln_next;

	if (n == 0) return 1;
	if (n == 1) return x;

	int i = 1;
	while (i < n) {
		Ln_next = ((double)(2 * i + 1) / (i + 1)) *	x * Ln - ((double)i / (i + 1)) * Ln_prev;
		Ln_prev = Ln;
		Ln = Ln_next;
		i++;
	}
	return Ln;
}


valarray<double> make_a(double a, double b, int n) {
	valarray<double> A(n * (n + 1));

	for (int i = 0; i < n; i++)
		for (int j = i; j < n + 1; j++) {
			A[(n + 1) * i + j] = double_count(a, b, i, j, n);
			if (j < n)
				A[(n + 1) * j + i] = A[(n + 1) * i + j];
		}

	return gaussianElimination(A, n);
}


valarray<double> gaussianElimination(valarray<double> M, int n) {
	valarray<double> buff(n + 1);
	
	//printf("n = %d\n", n);
	//out(M, n);//

	for (int i = 0; i < n; i++) {
		if (M[i * (n + 1) + i] == 0) {
			cout << "Error";
			exit(0);
		}

		buff = M[i * (n + 1) + i];
		M[slice(i * (n + 1), n + 1, 1)] /= buff;		
		
		for (int j = i + 1; j < n; j++) {
			buff = M[(n + 1) * j + i];
			buff *= M[slice((n + 1) * i, n + 1, 1)];
			M[slice((n + 1) * j, n + 1, 1)] -= buff;
		}
		//out(M, n);//
	}

	for (int i = n - 2; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			M[i * (n + 1) + n] -= M[i * (n + 1) + j] * M[j * (n + 1) + n];
		}
	}
	
	//printf("Result:\n");//
	//out(M, n);//
	//printf("\n\n");//
	return M[slice(n, n, n + 1)];
}


double Pm(double x, int n, double a, double b) {
	double P = 0;
	double  t = (2 * x - b - a) / (b - a);
	valarray<double> M = make_a(a, b, n);
	for (int i = 0; i < n; i++)
		P += M[i] * legendre(i, t);
	return P;
}


int main() {
	double a = 0;
	double b = 5;
	double delta;
	
	int n = 2, 
		m = 25;
	double In, step = (b - a) / m;
	double x;
	do {
		n++;
		delta = 0;
		x = a;
		for (int i = 0; i <= m; i++){
			In = func(x) - Pm(x, n, a, b);
			delta += In*In;
			x += step;
		}
		delta = sqrt(delta * step / (b - a));
		printf("[%2d]%10.5f\n", n, delta);
	} while (delta > 0.1);

	printf("\n");
	for (int i = 0; i <= m; i++)
		printf("%2.1f%10.5f\n", a + step * i, Pm(a + step * i, n, a, b));

	system("Pause");
	return 0;
}
