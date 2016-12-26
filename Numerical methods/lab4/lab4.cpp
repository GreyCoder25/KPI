#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double (*myFunc) (const long double x);

struct Task1 {
	Task1(double e, double h, double v, double err) {
		eps = e;
		step = h;
		value = v;
		error = err;
	}
	
	double eps;
	double step;
	double value;
	double error;
};

struct Task2 {
	Task2(double e, double h, double err) {
		eps = e;
		step = h;
		error = err;
	}
	double eps;
	double step;
	double error;
};

void print_table1(const vector<Task1> &t) {
	
	cout << "eps    h             I_value       abs_err" << endl;
	
	for (size_t i = 0; i < t.size(); ++i)
		cout << setw(7) << setiosflags(ios::left) << t[i].eps << setw(14) << t[i].step 
			 << setw(14) << t[i].value << setw(14) << t[i].error << "\n";	
	cout << endl;
}

void print_table2(const vector<Task2> &t) {
	
	cout << "eps           h             abs_err" << endl;
	
	for (size_t i = 0; i < t.size(); ++i)
		cout << setw(14) << setiosflags(ios::left) << t[i].eps
			 << setw(14) << t[i].step << setw(12) << t[i].error << "\n";	
	cout << endl;
}

long double func(const long double x) { return x * x * x / 6 - sin(x) + x; }
long double func_2der(const long double x) { return x + sin(x); }
long double prim(const long double x) { return x * x * x * x / 24 + cos(x) + x * x / 2; }

long double calculate_h(const long double a, const long double b, const long double eps) {
	
	return pow(12 * eps / ((b - a) * max(abs(func_2der(a)), abs(func_2der(b)))), 0.5);
	
}

Task1 integrate(myFunc f, const long double a, const long double b, const long double eps, const long double exact_val) {
	
	long double I = 0;
	I += (f(a) + f(b)) / 2;
	long double x = a;
	long double h = calculate_h(a, b, eps);
	int n = (int)ceil(((b - a) / h));
	h = (b - a) / n;
	for (int i = 1; i <= n - 1; ++i) {
		x += h;
		I += f(x);
	}
	I *= h;
	
	return (*new Task1(eps, h, exact_val, abs(exact_val - I)));
}

Task2 integrate_runge(myFunc f, const long double a, const long double b, const long double eps, const long double exact_val) {
	
	int r = 2;
	int n = (int)ceil(pow(eps, -1 / (double)r));
	
	long double I_n = 0, I_2n = 0;
	I_n += (f(a) + f(b)) / 2;
	long double h = (b - a) / n;
	long double x = a;
	for (int i = 1; i <= n - 1; ++i) {
		x += h;
		I_n += f(x);
	}
	I_n *= h;
	I_2n = I_n;
	
	do {
		n *= 2;
		I_n = I_2n;
		I_2n = (f(a) + f(b)) / 2;
		h = (b - a) / n;
		long double x = a;
		for (int i = 1; i <= n - 1; ++i) {
			x += h;
			I_2n += f(x);
		}
		I_2n *= h;
	} while (abs(I_n - I_2n) > 3 * eps);
	
	return (*new Task2(eps, h, abs(exact_val - I_2n)));
}

int main() {
	const long double a = -1;
	const long double b = 16;
	const long double EXACT_VAL = prim(b) - prim(a);
	
	vector<Task1> table1;
	vector<Task2> table2;
	
	double eps = 0.01;
	while (eps - 1e-8 >= 1e-20) {
		table1.push_back(integrate(func, a, b, eps, EXACT_VAL));
		eps *= 1e-2;
	}
	print_table1(table1);
	
	for (size_t i = 0; i < table1.size(); ++i)
		table2.push_back(integrate_runge(func, a, b, table1[i].error, EXACT_VAL));
		
	print_table2(table2);
	
	cout << setprecision(18);
	
	
	
}
