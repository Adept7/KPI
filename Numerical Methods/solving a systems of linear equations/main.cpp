#include <iostream>
#include <Math.h>
#include <valarray>
#include <iomanip>
using namespace std;

valarray<double> GaussJordan(valarray<double> A, valarray<double> B, double EPS);
valarray<double> SimpleIteration(valarray<double> A, valarray<double> B, valarray<double> X, double EPS);

const int n = 4;

void out(valarray<double> m) {
	for (int i = 0; i < m.size(); i++) {
		printf("%4.10f  ", m[i]);
		if (i % n == 3) cout << endl;
	}
	cout << endl;
}



void main() {
	valarray<double> A = { //для первого способа
		19, 15, 7, 1,
		0,  13, 1, 11,
		16, 13, 31, 1,
		12, 17, 15, 1
	};
	valarray<double> A1 = { //модифицировання, для второго
		19, 2, 6, -10,
		0,  13, 1, 11,
		16, 13, 31, 1,
		1, -3, 5, -21
	};
	
	valarray<double> B = {95, 133, 83, 107};
	valarray<double> B1 = { -38, 133, 83, -123 };
	valarray<double> X(n);

	X = GaussJordan(A, B, 1e-7);
	cout << "Result GaussJordan:" << endl;
	out(X);

	X = SimpleIteration(A1, B1, X, 1e-7);
	cout << "Result iteration:" << endl;
	out(X);

	system("Pause");
}



valarray<double> GaussJordan(valarray<double> A, valarray<double> B, double EPS) {
	valarray<double> buff(n);

	for (int i = 0; i < n; i++) {

		//cout << endl << endl;
		//cout << "___________ a __________" << endl << endl; out(A);
		//cout << "___________ b __________" << endl << endl; out(B);

		// a(ii) = 1
		buff = A[n*i + i];
		B[i] /= A[n*i + i];
		A[slice(n*i, n, 1)] /= buff; 
		// обнуляем столбцы
		for (int j = 0; j < n; j++) {
			if ((j != i) && (A[n*j + i] != 0)) {

				if (B[i] != 0) {
 					B[j] -= B[i] * A[n*j + i];
				}
				
				buff = A[n*j + i];
				buff *= A[slice(n*i, n, 1)];
				A[slice(n*j, n, 1)] -= buff;

				//cout << endl << endl;
				//cout << "___________ A __________" << endl << endl; out(A);
				//cout << "___________ B __________" << endl << endl; out(B);
			}
		}		
	}
	return B;
}


valarray<double> SimpleIteration(valarray<double> A, valarray<double> B, valarray<double> X, double EPS) {
	//преведение матрицы к нужному виду
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
			if ((A[i*n + j] != 0) && (i != j)) {
				A[i*n + j] = (A[i*n + j] * (-1)) / A[i*n + i];
			}
		}
		
		B[i] = B[i] / A[i*n + i];
		X[i] = B[i]; 
		A[i*n + i] = 0;
	}
	
	valarray<double> buff(n);
	double pX;
	bool fl = false;
	double q = 0;

	//норма матрицы
	for (int i = 0; i < n; i++) {
		buff = A[slice(i*n, n, 1)];
		
		for (int j = 0; j < n; j++) {
			buff[j] = abs(buff[j]);
		}
		if (buff.sum() > q)
			q = buff.sum();
	}
	q = (1 - q) / q * EPS;

	//процесс итерации
	while (fl != true) {
		pX = X[n - 1];

		buff = 0;
		for (int i = 0; i < n; i++) {		
			for (int j = 0; j < n; j++) {		
				buff[i] += A[i*n + j] * X[j];		
			}
			buff[i] += B[i];			
		}
		X = buff;

		//проверка для окончания итерации
		if (abs(X[n - 1] - pX) <= q) fl = true;
	}
	return X;
}
