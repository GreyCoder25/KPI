#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

using namespace std;

struct Task1 {
	Task1(double e, int n, long double a_e, long double r_t) {
		eps = e;
		num_iter = n;
		abs_err = a_e;
		rem_term = r_t;
	}
	
	double eps;
	int num_iter;
	long double abs_err;
	long double rem_term;
};

struct Task2 {
	Task2(double x, long double a_e, long double r_t) {
		x_i = x;
		abs_err = a_e;
		rem_term = r_t;
	}
	double x_i;
	long double abs_err;
	long double rem_term;
};

void print_table1(const vector<Task1> &t) {
	
	cout << "eps    n   Absolute error  Reminder term" << endl;
	
	for (size_t i = 0; i < t.size(); ++i)
		cout << setw(7) << setiosflags(ios::left) << t[i].eps << setw(4) << t[i].num_iter 
			 << setw(16) << t[i].abs_err << setw(12) << t[i].rem_term << "\n";	
}

void print_table2(const vector<Task2> &t) {
	
	cout << "x(i)   Absolute error  Reminder term" << endl;
	
	for (size_t i = 0; i < t.size(); ++i)
		cout << setw(7) << setiosflags(ios::left) << t[i].x_i 
			 << setw(16) << t[i].abs_err << setw(12) << t[i].rem_term << "\n";	
}


int main() {
	
	const double a = 1.4;
	const double b = 11.7;
	const double START_EPS = 0.01;
	const double FINAL_EPS = 0.00000000000001;
	const double STEP_EPS = 0.001; 
	
/* first table-------------------------------------*/

	double x = (a + b) / 2.0;
	long double eps = START_EPS;
	long double S = 1;
	int k = 1, n = 0;
	vector<Task1> table1;
	
	long double curr_abs_err = exp(x) - S;
	long double U_n = 1;
	
	int n2 = 0;
	
	long double integral_power_series = pow(M_E, (int)x);
	long double x_fract = x - (int)x; //дробная часть
	
	while (eps >= FINAL_EPS) {
		long double preset_eps = eps;
		eps /= integral_power_series; //корректировка точности для правильного 
									  //вычисления экспоненты	
		while (abs(U_n) >= eps) {
			U_n *= (x_fract / k);
			S += U_n;
			++n;
			++k;
			//curr_abs_err = (long double)abs(exp(x_fract) - S);
			curr_abs_err = (long double)abs(exp(x) - S * integral_power_series);
		}
		eps = preset_eps;
		
		if (abs(eps - 0.00000001) <=1e-20) {
			n2 = n;
		}

		table1.push_back(*(new Task1(eps, n, curr_abs_err, U_n)));
		eps *= STEP_EPS;
	}
	
	print_table1(table1);
	cout << "\n";
/*--------------------------------------------------------*/


/* second table ------------------------------------------- */
	double h = (b - a) / 10;
	vector<Task2> table2;
	
	for (int i = 0; i <= 10; ++i) {
		double x_i = a + h * i;
		double int_part = pow(M_E, (int)x_i);
		double x_i_fract = x_i - (int)x_i;
		S = 1;
		U_n = 1;
		k = 1;
		
		for (int j = 0; j < n2; ++j) {
			U_n *= (x_i_fract / k);
			S += U_n;
			++k;
		}
		table2.push_back(*(new Task2(x_i, abs(exp(x_i) - S * int_part), U_n)));
	}
	
	print_table2(table2);

}
