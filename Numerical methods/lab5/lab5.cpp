#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

typedef double (*myFunc) (const double, const int);

const double a = 0;
const double b = 12;
const int m = 30;
const double eps = 1e-7;
vector<double> alphas(m + 1, 0);

double repl(const double t) { return (b + a) / 2 + t * (b - a) / 2;	}

double return_to_repl(const double x) { return (2 * x - b - a) / (b - a); }

double f(const double x) { return x - 1.5 * x * x * x * sin(x); }

double legendre_polynomial(const double x, const int n) {
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	
	double P_prev = 1, P_curr = x, P_next = 0;
	
	for (int i = 1; i <= n - 1; ++i) {
		P_next = ((2 * i + 1) / (double)(i + 1)) * x * P_curr - (i / (double)(i + 1)) * P_prev;
		P_prev = P_curr;
		P_curr = P_next;
	}
	
	return P_next;
}

double product_f(const double x, const int n) {

	return legendre_polynomial(x, n) * f(repl(x));
	
}

double P(const double x, const vector<double> &alphas) {
	
	double res = 0;
	for (int i = 0; i < (int)alphas.size(); ++i)
		res += alphas[i] * legendre_polynomial(x, i);
		
	return res;
}

double dev_square(const double x, const int n = -1) {
	
	double dif = f(repl(x)) - P(x, alphas);
	return dif * dif;
	
}

double integrate_legendre(const double a, const double b, const double eps, const int n_leg, myFunc func) {
	
	int r = 2;
	int n = (int)ceil(pow(eps, -1 / (double)r));
	
	double I_n = 0, I_2n = 0;
	I_n += (func(a, n_leg) + func(b, n_leg)) / 2;
	double h = (b - a) / n;
	double x = a;
	for (int i = 1; i <= n - 1; ++i) {
		x += h;
		I_n += func(x, n_leg);
	}
	I_n *= h;
	I_2n = I_n;
	
	do {
		n *= 2;
		I_n = I_2n;
		I_2n = func(a, n_leg) + func(b, n_leg) / 2;
		h = (b - a) / n;
		double x = a;
		for (int i = 1; i <= n - 1; ++i) {
			x += h;
			I_2n += func(x, n_leg);
		}
		I_2n *= h;
		
	} while (abs(I_n - I_2n) > 3 * eps);
	
	return I_2n;
}
/*
 * questions:
 * - would it better to store results that will be calculated more then once
 * - about solving system of equations
 * */


int main() {

	const double t0 = -1, t1 = 1;
	
	double m_curr = 10, error = 100;
	while (error > 0.01) {
		for (int n = 0; n <= m_curr; ++n)
			alphas[n] = integrate_legendre(t0, t1, eps, n, product_f) / (2 / (double)(2 * n + 1));
			error = sqrt(integrate_legendre(t0, t1, 0.001, -1, dev_square) / (double)(b - a));
		++m_curr;
		cout << "m = " << m_curr - 1 << " error = " << error << endl;
	}
	
	/*for (double i = 0; i <= 12; i += 0.05) {
		cout << i << "\t" << P(return_to_repl(i), alphas) << endl;
		cout << i << "\t" << f(i) << endl;
    }
	*/
}
