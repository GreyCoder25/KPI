#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef long double (*myFunc) (long double x);

struct Solution {
	Solution(long double r, int n_i, long double err) {
		root = r;
		num_iter = n_i;
		error = err;
	}
	long double root;
	long double error;
	int num_iter;
};

long double func(long double x) {
	
	return 0.6 * x * x * x * x + 3 * log(x + 3) - 3.7; 
	
}

long double func_1der(long double x) {
		
	return 2.4 * x * x * x + 3 / (x + 3);
	
}

long double func_2der(long double x) {
	
	return 7.2 * x * x - 3 / ((x + 3) * (x + 3));
	
}

Solution fixedPointIteration(long double a, long double b, long double eps, myFunc f, myFunc f_1der) {
	
	/*returns root of equation on given interval
	 * using fixed point iteration method
	 * a - starting point of segment
	 * b - end point of segment
	 * f - function in equation you want to solve (f(x) = 0)
	 * f_1der - first derivative of f
	 * eps - allowable error
	 * 
	 * function expexts that first derivative of the given function is 
	 * monotonous at the given segment
	 */
	 
	 long double m1 = min(abs(f_1der(a)), abs(f_1der(b)));
	 long double M1 = max(abs(f_1der(a)), abs(f_1der(b)));
	 long double lambda = 1 / M1;
	 long double q = 1 - m1 / M1;
	 int num_iter = 0;
	 long double prec_estimate = 0;
	 
	 if (f_1der(a) < 0) lambda *= -1;
	 
	 long double x0 = (a + b) / 2;
	 
	 long double x_next = x0, x_cur;
	 do {
		 x_cur = x_next;	 
		 x_next -= lambda * f(x_next);
		 ++num_iter;
	 } while (abs(x_next - x_cur) > (1 - q) / q * eps);
	 prec_estimate = (1 - q) / q * eps;
	
	 return *(new Solution(x_next, num_iter, prec_estimate));
}

Solution newtonsMethod(long double a, long double b, long double eps, myFunc f, myFunc f_1der, myFunc f_2der) {
	
	/*returns root of equation on given interval
	 * using Newton's method
	 * a - starting point of segment
	 * b - end point of segment
	 * f - function in equation you want to solve (f(x) = 0)
	 * f_1der - first derivative of f
	 * f_2der - second derivative of f
	 * eps - allowable error
	 * 
	 * function expexts that first derivative of the given function is 
	 * monotonous at the given segment
	 */
	
	long double m1 = min(abs(f_1der(a)), abs(f_1der(b)));
	int num_iter = 0;
	long double prec_estimate = 0;
	
	long double x_n = 0;
	if (f(a) * f_2der(a) > 0)
		x_n = a;
	else if (f(b) * f_2der(b) > 0)
		x_n = b;
	
	
	while (abs(f(x_n)) / m1 > eps) {
		x_n -= f(x_n) / f_1der(x_n);
		++num_iter;
	}
	prec_estimate = abs(f(x_n)) / m1;
	
	return *(new Solution(x_n, num_iter, prec_estimate));
}


int main() {
	const int a1 = -2, b1 = -1;
	const int a2 = 0, b2 = 1;
	
	vector<Solution> fPIM;
	vector<Solution> nM;	
	double eps = 1e-2;
	for (int i = 0; i < 5; ++i) {
		fPIM.push_back(fixedPointIteration(a1, b1, eps, func, func_1der));
		fPIM.push_back(fixedPointIteration(a2, b2, eps, func, func_1der));
		nM.push_back(newtonsMethod(a1, b1, eps, func, func_1der, func_2der));
		nM.push_back(newtonsMethod(a2, b2, eps, func, func_1der, func_2der));
		eps *= 1e-3;
	}
	
	cout << "Table 1 --------- fixed point iteration method" << endl;
	cout << "eps    root value  		error estimation" << endl << endl;
	
	eps = 1e-2;
	for (size_t i = 0; i < fPIM.size(); ++i) {
		cout << setw(7) << setiosflags(ios::left) << eps
			 << setprecision(14) << setw(24) << fPIM[i].root << setw(12) << fPIM[i].error << "\n";
		if (i % 2 == 1)
			eps *= 1e-3;
	}
	
	cout << endl << "Table 2 --------- newton's method" << endl;
	cout << "eps    root value  		error estimation" << endl << endl;
	
	eps = 1e-2;
	for (size_t i = 0; i < nM.size(); ++i) {
		cout << setw(7) << setiosflags(ios::left) << eps
			 << setw(24) << nM[i].root << setw(12) << nM[i].error << "\n";
		if (i % 2 == 1)
			eps *= 1e-3;
	}
	
	cout << endl << "Table 3 --------- comparison the rate of convergence" << endl;
	cout << "eps    num iter(Iter)  num iter(Newton)" << endl << endl;
	
	eps = 1e-2;
	for (size_t i = 0; i < nM.size(); i += 2, eps *= 1e-3) 
		cout << setw(7) << setiosflags(ios::left) << eps
			 << setw(16) << fPIM[i].num_iter << setw(12) << nM[i].num_iter << "\n";
	
}

