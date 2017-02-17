#pragma once
#include <math.h>
#include <iostream>
#include <valarray>

using namespace std;

double func(double x);
double f(double x, int k1, int k2, int n, double a, double b);
double simpson(double a, double b, int n, int k1, int k2, int N);
double double_count(double a, double b, int k1, int k2, int n);
double legendre(int n, double x);
valarray<double> make_a(double a, double b, int n);
valarray<double> gaussianElimination(valarray<double> M, int n);
double Pm(double x, int n, double a, double b);