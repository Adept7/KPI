#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double f(double x) {
	//return tan(x) + x / (cos(x) * cos(x));
	return (5 * x*x - 2) / 3;
}


double f4(double x) {
	return  16*tan(x)* pow(cos(x), 4) + 8* pow(tan(x), 3)*pow(cos(x), 2)+4*(16* pow(cos(x), 4)*tan(x)+8* pow(tan(x), 3)*pow(cos(x), 2))+x*(16* pow(cos(x), 6)+88* pow(tan(x), 2)*pow(cos(x), 4)+16* pow(tan(x), 4)*pow(cos(x), 2));
}//16*tan(x)*cos(x)^4+8*tan(x)^3*cos(x)^2+4*(16*cos(x)^4*tan(x)+8*tan(x)^3*cos(x)^2)+x*(16*cos(x)^6+88*tan(x)^2*cos(x)^4+16*tan(x)^4*cos(x)^2)


double Newton_Leibniz(double a, double b) {
	return b * tan(b) - a * tan(a);
}


std::vector<double> simpson(double a, double b, int n) {//
	vector<double> ret;//
	if (n % 2 == 1)	n++;
	double h;
	double sig1 = 0.0;
	double sig2 = 0.0;
	h = (b - a) / n;
	ret.push_back(h);//

	for (int i = 1; i < n; i++)
	{
		if (i % 2 == 0)
			sig2 += f(a + i*h);
		else
			sig1 += f(a + i*h);
	}
	ret.push_back((h / 3) * (f(a) + f(b) + 4*sig1 + 2*sig2));//
	ret.push_back(ret.back() - Newton_Leibniz(a, b));	//
	return ret;//
}


std::vector<double> func1(double a, double b, double eps) {//
	double h;
	int n;
	double M = 813.701;
	h = pow(180 * eps / (M * (b - a)), 0.25);
	n = round((b - a) / h);
	return simpson(a, b, n);
}


std::vector<double> double_count(double a, double b, double eps) {//
	double R, I1, I2;
	int n = (int)(1 / pow(eps, 0.25));
	if (n % 2 == 1)
		n++;
	vector<double> ret(3);//
	
	do {
		I1 = simpson(a, b, n)[1];
		I2 = simpson(a, b, 2 * n)[1];
		ret = simpson(a, b, 2 * n);//
		R = fabs((I1 - I2) / I2) / 15;
		n *= 2;
	} while (R > eps);	
	
	return ret;//
}


void main() {
	double eps = 1e-2;
	//double a = 2, b = 4;
	double a = 0, b = 5;
	double i = eps;
	vector<double> r;
	vector<double> buf;
	printf("%5.10f\n", simpson(2, 4, 1000)[1]);
	printf("%5.10f\n", double_count(2, 4, 0.0000001)[1]);
	printf("%5.10f\n", Newton_Leibniz(2,4));

	printf("TASK 1\n");
	printf(" eps\t      h\t\t   value\t    delta\n");
	while (i > 1e-12) {
		r = func1(a, b, i);
		printf("%0.e\t%10.10f\t%10.10f\t%10.10f\n", i, r[0], r[1], fabs(r[2]));
		buf.push_back(fabs(r[2]));
		i /= 100;
	}
	
	int j = 0;
	printf("\nTASK 2\n");
	printf("\n delta\t\t      h\t\t    delta'\n");
	while (1) {
		r = double_count(a, b, buf[j]);
		printf("%10.10f\t%10.10f\t\t%10.10f\n", buf[j], r[0], fabs(r[2]));
		i /= 100;
		j++;
		if (j == buf.size())
			break;
		
	}

	system("Pause");
}